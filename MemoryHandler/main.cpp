#include <iostream>
#include "MemoryHandler.h"

using namespace std;

int main()
{
	MemoryHandler memHandler((char*)"devenv.exe");
	memHandler.open();
	cout << "Procces ID:\t" << memHandler.getProcID() << endl;
	memHandler.close();

	return 0;
}