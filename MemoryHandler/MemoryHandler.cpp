#include "MemoryHandler.h"

MemoryHandler::MemoryHandler(char* procName, size_t bufferSize) /*: procID(NULL)*/
{
	procID = 0;
	int len = strlen(procName) + 1;
	this->procName = new char[len];
	strcpy_s(procName, len, procName);

	this->buffer = new byte[bufferSize];
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
			if (_stricmp(procName, procInfo.szExeFile) == 0)
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