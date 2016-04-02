#include "IObserver.h"

#include <iostream>
using namespace std;

class SampleGraph : public IObserver
{
public:
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Sample Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

// DLL ���� ���� Ŭ���� �̸��� �˾ƾ� �Ѵ�.
// ���� Ŭ������ �ٲܷ��� �������� �ٽ� �ؾ���
// ����� �ִ� �θ� �����ϸ� ����߰� ����

// �ݵ�� ���� ��� �ȿ��� ��ü�� �����ϴ� ����� �������־�� �մϴ�. - �ٽ�!!
// - SampleGraph ��� �̸��� ���� DLL�� ����� ����� �˰� �ֽ��ϴ�.
// - ���α׷� ���ο����� ���� �̸��� ����ϸ� �ȵ˴ϴ�.
// Table Ŭ������ SampleGraph�� �����ϸ� (���� ����), SampleGraph�� ���ϸ� Table�� ���� ������
// Table�� IObserver�� �����ؾ� �Ѵ�.
// ���� �������� ������ ���յ� �߿�
// �׷��� IObserver ��ü�� ������ �� ����. ��ü Ŭ������ �����ؾ�..


// �ݵ�� DLL ���ο��� �ڽ��� ���� Ŭ������ ��ü�� �������־�� �մϴ�.
// - �Լ��� �ϳ��� ����մϴ�.
// ���ο��� ��ü Ŭ���� �����ϰ� �������̽��� ���� �޾ƿ���!

extern "C"					// C ��Ÿ�Ϸ� ¥��, �Լ� �����ε� ��������.
__declspec(dllexport)		// ���ο쿡�� DLL ���� �ɺ��� �����ϴ� ���
IObserver* CreateGraph()
{
	return new SampleGraph;
}

// C++������ �Լ� �����ε� ���� C��� �Ұ���
// ���������� �ٸ� �̸� �����
//void foo() {}			// foo
//void foo(double) {}		// foo@int
//void foo(int, int) {}	// foo@int@int

// developer command prompt: cl ��� == gcc
// cl SampleGraph.cpp /LD
// /LD : DLL�� ������ �ɼ�