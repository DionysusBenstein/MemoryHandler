#pragma once

#include <windows.h>
#include <TlHelp32.h>

class MemoryHandler
{
public:
	MemoryHandler(char* procName, size_t bufferSize = 32);
	~MemoryHandler();

	void open(DWORD accessRights = PROCESS_ALL_ACCESS);
	void close();

private:
	char* pName;
	DWORD pID;
	HANDLE hProc;
	byte* buffer;
	size_t bufferSize;
};

