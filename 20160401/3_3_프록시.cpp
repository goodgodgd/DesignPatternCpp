// ���� �����ڿ��Լ� ICalc.h�� CalcProxy.dll�� �޾ƾ� �մϴ�.
// ICalc ��� �������̽��� ���� ���� ����� �����ϰ� ����.

#include <iostream>
#include "ICalc.h"
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

#if 0
int main()
{
	// 1. CalcProxy.dll�� �ε� �մϴ�.
	void* addr = IoLoadModule("CalcProxy.dll");

	// 2. ��ü�� �����ϴ� �Լ��� ã�ƾ� �մϴ�.
	typedef ICalc*(*F)();	// ��� �Լ� ������
	F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

	// 3. Calc ��ü ����
	ICalc* pCalc = f();

	// ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
#endif

#if 0
int main()
{
	// 3. Calc ��ü ����
	ICalc* pCalc = CreateInstance();

	// ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;

	// ����: CreateCalc ���� new�� ���� ������ �޸� ���� �߻� -> �ı� �ʿ�
	delete pCalc;	// ���� �ϸ� �ȵ˴ϴ�.

	// �� �ȵǳ�?
	// �������� new, delete ������ �����Ϸ� ������ ���� �ٸ��� ������
	// new�� ����ִ� ���̺귯�� ���ο� �ۿ��� ���� delete�� ������ �޶��� �� �ִ�.
	// ���̺귯�� ���ο��� �ڵ����� �ı��� ������� �Ѵ�.
	// �ش�: ��ü�� ������ ������� ������� �����ؾ� �Ѵ�.
}
#endif

int main()
{
	// ���� ��� ��� Calc ��ü ����
	// sp<> - ����� ������ �����ϱ� ���ؼ� �Դϴ�.
	Ptr<ICalc> pCalc = CreateInstance();

	// ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
