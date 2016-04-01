// Proxy Pattern
// Remove Proxy: IPC, Network ���� ������ ����ϴ� Ŭ����
// Smart Proxy: ���� ��ҿ� �߰����� �۾��� �ϴ� Ŭ����, ����Ʈ ������, RAII

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// ����: �������� ���������� �˾ƾ߸� �� �� �ִ�.
// ������ ����� ����ó�� �� �� �ְ� ������.

// ���� ��ſ� ����� Ŭ������ ����� ���ô�.
// ������ �����ϴ� ����� ����� ��������� - ���������� ���� �����ڰ� �˰� �ֱ� ����.

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
	// Remote Proxy: ����ڴ� �������� ���������� ���� IPC �̿��� �� �ִ�.
	Calc* pCalc = new Calc;
	cout << pCalc->add(1, 2) << endl;
	cout << pCalc->sub(1, 2) << endl;
}

// ����ü�� �����ϱ� ���ٴ� �������̽��� ��������
// ������ ������ �޶����� Ŭ���̾�Ʈ ����� �ٽ� �����ϵ� �ʿ� ���� DLL�� �ٲٸ� �ǰ� ����.
// ���� ���� �����ڿ��� 2���� ������ �޾ƾ� �մϴ�.
// 1. ICalc.h : �������̽� ���
// 2. CalcProxy.dll: Proxy Class �� �ִ� DLL
