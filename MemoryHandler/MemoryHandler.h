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
	DWORD getProcID();

	void write(void* ptr, DWORD to, size_t size);

private:
	char*  procName;
	DWORD  procID;
	HANDLE hProc;
	byte*  buffer;
	size_t bufferSize;

	void fingProcID();
};

