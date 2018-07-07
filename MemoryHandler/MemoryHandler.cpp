#include "MemoryHandler.h"

MemoryHandler::MemoryHandler(char* procName, size_t bufferSize) : procID(NULL)
{
	int len = strlen(procName) + 1;
	this->procName = new char[len];
	strcpy_s(this->procName, len, procName); 
	this->buffer = new byte[32];
}

MemoryHandler::~MemoryHandler()
{
	delete[] this->procName;
	delete[] this->buffer;
}

void MemoryHandler::fingProcID()
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 procInfo;
	procInfo.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &procInfo))
	{
		while (Process32Next(snapshot, &procInfo))
		{
			if (_stricmp(this->procName, procInfo.szExeFile) == 0)
			{
				this->procID = procInfo.th32ProcessID;
				CloseHandle(snapshot);
				return;
			}
		}
	}
	else
	{
		CloseHandle(snapshot);
		this->procID = NULL;
		return;
	}
}

void MemoryHandler::open(DWORD accessRights)
{
	fingProcID();
	this->hProc = OpenProcess(accessRights, false, this->procID);
}

void MemoryHandler::close()
{
	CloseHandle(this->hProc);
}

DWORD MemoryHandler::getProcID()
{
	return this->procID;
}

void MemoryHandler::write(void* ptr, DWORD to, size_t size)
{
	WriteProcessMemory(this->hProc, (LPVOID)to, ptr, size, NULL);
}

void MemoryHandler::write(void* ptr, DWORD to, size_t size, DWORD memProtect)
{
	//need check
	DWORD oldMemProtect = NULL;
	VirtualProtectEx(hProc, (LPVOID)to, size, memProtect, &oldMemProtect);
	WriteProcessMemory(this->hProc, (LPVOID)to, ptr, size, NULL);
	VirtualProtectEx(hProc, (LPVOID)to, size, oldMemProtect, &oldMemProtect);
}