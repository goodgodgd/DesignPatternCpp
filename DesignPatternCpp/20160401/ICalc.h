	
#include <iostream>
using namespace std;

class RefCountedObject
{
	int mCount;
public:
	RefCountedObject() : mCount(0) { cout << "��ü ����" << endl; }
	virtual ~RefCountedObject() { cout << "��ü �ı�" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// ��������� 0�Ǹ� �ڽ� �ı�
			delete this;
	}

};

struct ICalc : RefCountedObject
{
	virtual int add(int a, int b) = 0;
	virtual int sub(int a, int b) = 0;

	virtual ~ICalc() {}
};

// ����Ʈ ������
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p) { ptr->addRef(); }	// ��Ģ 1.
	Ptr(const Ptr& p) : ptr(p.ptr)
	{
		ptr->addRef();
	}								// ��Ģ 2.
	~Ptr() { ptr->release(); }					// ��Ģ 3.

												// ��¥ ������ó�� ������ �Ѵ�. ->, * �����ڸ� �������ؾ� �Ѵ�.
												// => ����Ʈ ������ �⺻
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
};

#include "ioacademy.h"
using namespace ioacademy;

// ��ü�� �����ϴ� ����� ���� �����ڰ� ��������� �Ѵ�.
// �ȵ���̵�: asInterface, MS COM: CoCreateInstance
// Ptr<ICalc> ���� Ÿ���� �̷��� ���� ����ڰ� ����Ʈ�����͸� ���� ������ �� �ִ�.
static ICalc* CreateInstance()
{
	// 1. CalcProxy.dll�� �ε� �մϴ�.
	void* addr = IoLoadModule("CalcProxy.dll");

	// 2. ��ü�� �����ϴ� �Լ��� ã�ƾ� �մϴ�.
	typedef ICalc*(*F)();	// ��� �Լ� ������
	F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

	// 3. Calc ��ü ����
	return f();
}
