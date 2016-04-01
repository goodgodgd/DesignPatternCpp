// IPC ¼­¹ö
#include "ioacademy.h"
#include <iostream>
using namespace std;
using namespace ioacademy;

int foo( int code, int param1, int param2)
{
	switch( code )
	{
	case 1: cout << "+" << endl; return param1 + param2;
	case 2: cout << "-" << endl; return param1 - param2;
	}
	return 0;
}

int main()
{
	IoStartServer( "CalcServer", foo);
}
