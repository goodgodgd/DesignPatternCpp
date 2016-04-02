// Proxy Pattern
// Remote Proxy: �������� ���������� �𸣴� ����ڵ� ������ ����� ����ó�� �� �� �ְ� ������.
// ������ �����ϴ� ����� Ŭ���� ����� ��������� - ���������� ���� �����ڰ� �˰� �ֱ� ����.

// �̰��� �����ϱ� �� ���� ������ �����ؾ� �մϴ�.

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// ���� �����ڰ� �Ʒ� Ŭ������ �����ؼ� Ŭ���̾�Ʈ �����ڿ��� �����ϴ� ���Դϴ�.
class Calc
{
	int handle;
public:
	Calc() { handle = IoFindServer("CalcServer"); }
	int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
	int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }
};

int main()
{
	// Remote Proxy: ����ڴ� �������� ���������� ���� IPC�� �̿��� �� �ִ�.
	Calc* pCalc = new Calc;
	cout << pCalc->add(1, 2) << endl;
	cout << pCalc->sub(1, 2) << endl;
}
