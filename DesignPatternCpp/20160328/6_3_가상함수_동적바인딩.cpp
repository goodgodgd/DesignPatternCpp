// http://d.pr/n/19UjG

#include <iostream>
using namespace std;

class A
{
	int a;
public:
	virtual void foo() { cout << "A foo" << endl; }
};

class B
{
	int b;
public:
	virtual void goo() { cout << "B goo" << endl; }
};

int main()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();	// ��� ���ñ�?
	// ���� ���ε��� ��� "B goo"
	// ���� ���ε��� ��� "A foo", foo()�� goo() ��� �����Լ��� ���, A::foo()�� ����� vfptr�� �����Ѵ�.

	// �Ѵ� �񰡻�: B goo
	// B�� ����: ���� ����
	// A�� ����: B goo
	// �Ѵ� ����: A foo

}
