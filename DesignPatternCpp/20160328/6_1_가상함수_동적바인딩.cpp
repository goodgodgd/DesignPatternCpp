// �����Լ��� ����
// virtual Ű���尡 ���� ���ε��� ���� ���ε����� �ٲ۴�.
#include <iostream>
using namespace std;

class Animal
{
public:
	//void cry()	{ cout << "Animal cry" << endl; }
	// virtual Ű����� ���� ���ε��� ���� ���ε����� �ٲ��ش�.
	virtual void cry()	{ cout << "Animal cry" << endl; }
};

class Dog : public Animal
{
public:
	// �������̵�
	void cry()	{ cout << "Dog cry" << endl; }
};

int main()
{
	Animal a;
	a.cry();	// Animal cry
	Dog d;
	d.cry();	// Dog cry

	Animal* p = &d;
	p->cry();	// Animal cry() �� �� ���� �Լ���: ���� ���ε� -> Animal cry ���
				// Animal cry() �� ���� �Լ���	 : ���� ���ε� -> Dog cry ���
}

// �Լ� ���ε�
// p->cry() �� � �Լ��� ������ ���ΰ�?

// 1. static binding:	������ �� �����Ϸ��� ����
//						p�� ������ Ÿ�����θ� �����Ѵ�.
//						C, C++, C# �⺻ ���ε� ���, ������, �����Ϸ� ����ȭ ����, �� �̼����̴�. virtual Ű���� ����

// 2. dynamic binding:	������ �� p�� �޸𸮸� �����ϴ� ���� �ڵ� ����
//						���� �ð����� �޸� ���� �� ȣ��
//						Java, Objective-C, "���������" ������, �̼����̴�.

// C++, Ư�� C# �� �ֽ� ������� ���������� �����ϰ� �ִ�. C++11/14�� ���� C++09�ʹ� ������ �ٸ���. C++09�� C���� Ŭ������ �߰��� ���� �߻�ȭ �� ��
// Java�� maintainer�� ���ο� ����� �޾Ƶ��̴� �Ϳ� ���� �������̾��µ� �ֱ� maintainer�� �ٲ� �ֽ� ��� ���� ���̴�.
