/*******************************************************************/

/* Original File Name: MemoryHandler.cpp                           */

/* Date: 07-07-2018                                                */

/* Developer: Dionysus Benstein                                    */

/* Copyright © 2018 Dionysus Benstein. All rights reserved.        */

/* Description: A class implementation represents the basic 
				functional.                                        */

/*******************************************************************/


#include "MemoryHandler.h"

MemoryHandler::MemoryHandler(char* procName, size_t bufferSize) : procID(NULL), bufferSize(bufferSize)
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
	PROCESSENTRY32 procInfo; //Structure that stores data about process
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

void MemoryHandler::write(void* ptr, DWORD to, size_t size)
{
	WriteProcessMemory(hProc, (LPVOID)to, ptr, size, NULL);
}

void MemoryHandler::write(void* ptr, DWORD to, size_t size, DWORD memProtect)
{
	DWORD oldMemProtect = NULL;
	VirtualProtectEx(hProc, (LPVOID)to, size, memProtect, &oldMemProtect); //need check on size
	WriteProcessMemory(hProc, (LPVOID)to, ptr, size, NULL);
	VirtualProtectEx(hProc, (LPVOID)to, size, oldMemProtect, &oldMemProtect);
}

MemoryHandler& MemoryHandler::read(DWORD from, size_t size)
{
	memset(this->buffer, 0, this->bufferSize);
	ReadProcessMemory(hProc, (LPVOID)from, buffer, size, NULL);
	return *this;
}

MemoryHandler& MemoryHandler::read(DWORD from, size_t size, DWORD memProtect)
{
	DWORD oldMemProtect = NULL;
	memset(this->buffer, 0, this->bufferSize);
	VirtualProtectEx(hProc, (LPVOID)from, size, memProtect, &oldMemProtect); //need check on size
	ReadProcessMemory(hProc, (LPVOID)from, buffer, size, NULL);
	VirtualProtectEx(hProc, (LPVOID)from, size, oldMemProtect, &oldMemProtect);
	return *this;
}

char* MemoryHandler::toStringA()
{
	return (char*)buffer;
}

wchar_t* MemoryHandler::toStringU()
{
	return (wchar_t*)buffer;
}

DWORD MemoryHandler::getProcID()
{
	return this->procID;
}
