#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	char* processName = (char*)"Telegram.exe";
	int modifiedNumber = 13;

	MemoryHandler memHandler(processName);
	memHandler.open();
	memHandler.write(&modifiedNumber, 0x3A024B8, 4);
	cout << "Process name: " << processName << "\tProcces ID: " << memHandler.getProcID() << endl;
	cout << "Read string: " << memHandler.read(0x3A024B8, 4).toNum<int>() << endl;
	memHandler.close();
	
	return 0;
}