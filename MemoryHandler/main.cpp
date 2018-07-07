#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	MemoryHandler *memHandler = new MemoryHandler("notepad.exe");
	memHandler->open();

	return 0;
}