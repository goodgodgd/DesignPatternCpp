// �����Լ��� ����� ��������.
// �����Լ��� ����ϴ� Ŭ������ ������ Ŭ���� �ۿ� �����Լ� ���̺��� ����ؾ� �Ѵ�.
// �����Լ� �ϳ��� ���̺� ������ �ϳ��� �޸� ����� �þ�� ������ �����ؼ� ����Ѵ�.

// http://d.pr/n/1kdfb

#include <iostream>
using namespace std;

class Animal
{
	int age;
public:
	virtual void cry() { cout << "Animal cry" << endl; }
	virtual void foo() {}
	virtual void goo() {}
};

// Animal ��ü�� age�� ������ �Բ� vfptr�� ������ �ִ�.
// Animal ��ü�� �����Լ��� Animal�� �Լ��� ����Ű���� ��ӹ��� Dog�� �Լ��� ����Ű������ �� ��ü���� �ٸ��� ������
// �װ��� ������ ������ vfptr�� �ʿ��ϴ�.

class Dog : public Animal
{
	int color;
public:
	// virtual�� ���� �ʾƵ� ���������� virtual�� �ν������� �������� ���� virtual�� ���ִ� ���� ����.
	virtual void cry() { cout << "Dog cry" << endl; }
};

int main()
{
	Dog d;
	Animal* p = &d;
	p->cry();	// �� ������ ��Ȯ�� ������ ������ ���ô�.
	// (*p)[0](p);	// ���� �������, (*p)[0]==vfptr �����Լ� ���̺� ����� ������

	Animal a;
	cout << sizeof(a) << endl;	// 8 => age �ܿ��� vfptr �����ϱ� ����, 64 bit�� 
	cout << sizeof(d) << endl;	// 12 => age + color + vfptr
}
