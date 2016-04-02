// ���Ͻ��� ����ü�� �����ϱ� ���ٴ� �������̽��� ��������
// ������ ������ �޶����� Ŭ���̾�Ʈ ����� �ٽ� �����ϵ� �ʿ� ���� DLL�� �ٲٸ� �ǰ� ����.
// ���� ���� �����ڿ��� 2���� ������ �޾ƾ� �մϴ�.
// 1. ICalc.h : �������̽� ��� - ������ �ʴ� ��
// 2. CalcProxy.dll: Proxy Class �� �ִ� DLL - ���ϴ� ������

// ���� �����ڿ��Լ� ICalc.h�� CalcProxy.dll�� �޾ƾ� �մϴ�.
// ICalc ��� �������̽��� ���� ���� ����� �����ϰ� ����.

// �̰��� �����ϱ� �� ���� ������ �����ؾ� �մϴ�.

#include <iostream>
#include "ICalc.h"
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// �������̽� ICalc ����
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
#endif	// ����: ���Ͻ� ��ü ������ �����ϴ�.

// ���Ͻ� ��ü ���� CreateInstance()��� �Լ� ������ ĸ��ȭ
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
#endif	// ����: ������ ��ü�� �޸𸮸� ������ �� ����.

// ����Ʈ �����ͷ� ���Ͻ� ��ü ����
// CalcProxy.cpp: Calc��� ��ü Ŭ���� ���� -> CalcProxy.dll
// ICalc.h: �������̽� �� dll�ҷ��� ��ü �����ϴ� CreateInstance() ����
int main()
{
	// ���� ��� ��� Calc ��ü ����
	// sp<> - ����� ������ �����ϱ� ���ؼ� �Դϴ�.
	Ptr<ICalc> pCalc = CreateInstance();

	// ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
