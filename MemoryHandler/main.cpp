#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	char* processName = (char*)"devnev.exe";

	MemoryHandler memHandler(processName);
	memHandler.open();
	cout << "Process name: " << processName << "\tProcces ID: " << memHandler.getProcID() << endl;
	cout << "Read string: " << memHandler.read(0xECB3EFA, 6).toStringU() << endl;
	memHandler.close();
	
	return 0;
}