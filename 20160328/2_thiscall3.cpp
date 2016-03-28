// ��� �Լ��� �Լ� ������
// http://d.pr/n/7Lpj

#include <iostream>
using namespace std;

class Dialog
{
public:
	void close()	// void close(Dialog* this)
	{ cout << "Dialog close" << endl; }

	static void goo()	// void goo()
	{ cout << "goo" << endl; }
};

void foo() { cout << "foo" << endl; }

// 1. �Ϲ� �Լ� �����Ϳ� ��� �Լ��� �ּҸ� ���� �� ����.
// 2. ��� �Լ� �����͸� ����� ����ϴ� ���
// 3. �Ϲ� �Լ� �����Ϳ� ���� ��� �Լ��� �ּҸ� ���� �� �ִ�.
int main()
{
	void(*f)() = &foo;
	f();	// �Լ��� �Լ� �����ͷ� ȣ��

	// C�ʹ� �ٸ��� C++������ ��� �Լ� �����͵� ����
	// 1.�� ���� �Ʒ��� ������ �ȵ�
//	void(*f1)() = &Dialog::close;

	Dialog dlg;
	// �Ʒ��� ���� ��� �´�. Dialog* this �� �������ֱ� ����
	void(Dialog::*f2)() = &Dialog::close;
	// �׷��� ��� �Լ��� ȣ���ϱ� ���ؼ� ��ü�� �ʿ��ϴ�. �Ʒ��� �ȵ�
//	f2();
	// �Ʒ��� �ȵ�, f2�� ��� �Լ� �ƴϴ�.
//	dlg.f2();
	// �Ʒ��� ������ ������ ������ �ȵ��ִ�. ������ �켱 ����
//	dlg.*f2();
	// ����: ���� ��ü�� �����ϰ� ����
	(dlg.*f2)();

	void(*f3)() = &Dialog::goo;	// // ��ü�� �ʿ���� ���� �Լ� -> �Ϲ� �Լ� ������
	f3();
}
