
// http://d.pr/n/1lDec

#include <iostream>
using namespace std;

// 1. �θ� Ŭ������ �Ҹ��ڰ� ���� �������̸�, ��� �ڽ��� �Ҹ��ڵ� �����Լ��̴�.
// 2. ��� �θ� Ŭ������ �Ҹ��ڴ� �ݵ�� �����Լ��̾�� �Ѵ�.
// ���� ����: Inside C++ Object - ���ĸ� ����

class Base {
public:
	virtual ~Base() {}
};

class Derived : public Base
{
public:
	Derived() { cout << "�ڿ� �Ҵ�" << endl; }
	~Derived() { cout << "�ڿ� ����" << endl; }
};

int main()
{
	Base* p = new Derived;	// ������ ������ ȣ��
							// �����ڴ� Derived�� �����߱� ������ �ǵ��� ��� �۵��Ѵ�.

	delete p;				// �Ҹ��� ȣ�� �ȵ�
							// p�� Ÿ���� Base�̱� ������ Base�� �Ҹ��ڸ� ȣ���Ϸ� �Ѵ�.
							// ���� �θ� Ŭ������ �Ҹ��ڴ� �ݵ�� �����Լ��� �������� �Ѵ�.

//	Derived d;
}
