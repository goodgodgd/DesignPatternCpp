// Proxy Pattern
// Remove Proxy: IPC, Network ���� ������ ����ϴ� Ŭ����
// Smart Proxy: ���� ��ҿ� �߰����� �۾��� �ϴ� Ŭ����, ����Ʈ ������, RAII

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// ����: �������� ���������� �˾ƾ߸� �� �� �ִ�.
// ������ ����� ����ó�� �� �� �ְ� ������.


int main()
{
	// 1. ������ ��ȣ�� ���´�.
	int handle = IoFindServer("CalcServer");
	cout << "���� ��ȣ: " << handle << endl;

	cout << IoSendServer(handle, 1, 1, 2) << endl;	// 3 = 1 + 2
	cout << IoSendServer(handle, 2, 1, 2) << endl;	// -1 = 1 - 2;
}

