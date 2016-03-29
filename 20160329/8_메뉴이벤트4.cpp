// �ڵ鷯 ����� �̺�Ʈ ó��
//	=> �Լ� ������
//	=> IPhone target-action
//		C# delegate
//		MFC message map
//		Qt signal slot

// ������: C++���� ���� �Լ� �����Ͷ�� ������ �������� �ʴ´�.
// ���� �Լ� ������: Ŭ���� ��� �Լ� ������, �Ϲ� �Լ� ������
// ���� ���� �Լ� �����͸� ����� ����.
// ���: �Ϲ� �Լ� �����͸� �ٷ�� �ִ� Ŭ������ �����, ��� �Լ� �����͸� �ٷ� �� �ִ� Ŭ������ ����µ� ���� �θ𿡼� ��� �ް� �����.

#include <iostream>
using namespace std;

class Dialog;

// �� �ڵ��� ����: �̺�Ʈ�ڵ鷯�� Dialog Ŭ������ �����Ѵ�.
class MenuItem
{
	void(Dialog::*handler)();
	Dialog* object;
public:
	void setHandler(void(Dialog::*h)(), Dialog* o)
	{
		handler = h;
		object = o;
	}

	virtual void command()
	{
		(object->*handler)();
	}
};

class Dialog
{
public:
	void open() { cout << "Dialog open" << endl; }
	void close() {cout << "Dialog close" << endl;}
};

// �׷��� ���� �̺�Ʈ �ڵ鷯�� �Ϲ� �Լ��� ���� �ʹٸ�??
int main()
{
	MenuItem m1;
	MenuItem m2;

	Dialog dlg;
	m1.setHandler(&Dialog::open, &dlg);
	m2.setHandler(&Dialog::close, &dlg);

	m1.command();
	m2.command();
}
