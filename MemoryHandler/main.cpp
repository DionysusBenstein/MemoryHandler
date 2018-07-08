#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	char* processName = (char*)"StoneShard.exe";

	MemoryHandler memHandler(processName);
	memHandler.open();
	cout << "Process name: " << processName << "\tProcces ID: " << memHandler.getProcID() << endl;
	cout << "Read string: " << memHandler.read(0x2FF16104, 4).toNum<int>() << endl;
	memHandler.close();
	
	return 0;
}