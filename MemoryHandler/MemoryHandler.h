/*******************************************************************/

/* Original File Name: MemoryHandler.h                             */

/* Date: 07-07-2018                                                */

/* Developer: Dionysus Benstein                                    */

/* Copyright © 2018 Dionysus Benstein. All rights reserved.        */

/* Description: A class representing the basic functional.         */

/*******************************************************************/

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

	void write(void* ptr, DWORD to, size_t size);
	void write(void* ptr, DWORD to, size_t size, DWORD memProtect);
	
	MemoryHandler& read(DWORD from, size_t size);
	MemoryHandler& read(DWORD from, size_t size, DWORD memProtect);

	template <typename T>
	T toNum();
	char* toStringA();
	wchar_t* toStringU();

	DWORD getProcID();

private:
	char*  procName;
	DWORD  procID;
	HANDLE hProc;
	byte*  buffer;
	size_t bufferSize;

	void fingProcID();
};

template<typename T>
inline T MemoryHandler::toNum()
{
	T temp = 0;
	memcpy(&temp, this->buffer, sizeof(T));
	return temp;
}
