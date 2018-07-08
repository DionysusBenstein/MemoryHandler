#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	char* processName = (char*)"chrome.exe";
	MemoryHandler memHandler(processName);
	memHandler.open();
	cout << "Process name" << "\tProcces ID" << endl;
	cout << processName << "\t" << memHandler.getProcID() << endl;
	memHandler.close();

	return 0;
}