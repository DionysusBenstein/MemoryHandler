#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	char* processName = (char*)"chrome.exe";

	MemoryHandler memHandler(processName);
	memHandler.open();
	cout << "Process name: " << processName << "\tProcces ID: " << memHandler.getProcID() << endl;
	memHandler.close();
	
	return 0;
}