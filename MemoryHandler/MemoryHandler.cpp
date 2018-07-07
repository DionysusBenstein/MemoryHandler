#include "MemoryHandler.h"

MemoryHandler::MemoryHandler(char* procName, size_t bufferSize)
{
	int len = strlen(procName) + 1;
	this->pName = new char[len];
	strcpy_s(pName, len, procName);

	this->buffer = new byte[bufferSize];
}

MemoryHandler::~MemoryHandler()
{
	delete[] this->pName;
	delete[] this->buffer;
}

void MemoryHandler::open(DWORD accessRights)
{

}

void MemoryHandler::close()
{

}