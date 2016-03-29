// 1. �������̽� ����� ������ ����: Java, Android

//	�������̽�: �б⹮ �ʿ� => ��ü���� ���� �Լ� �����ϴ� �ڵ鷯�� ����.

#include <iostream>
using namespace std;

// �޴��� ó���ϰ� ���� ��� Ŭ������ �Ʒ� �������̽��� �����ؾ� �Ѵ�.
// ��� ����� �ʿ�
struct IMenuListener
{
	virtual void onCommand(int id) = 0;
	virtual ~IMenuListener() {}
};

// �������� �ܺ� �������̽� ��� Ŭ������ ������ �� => ���� ����
class MenuItem
{
	int id;
	IMenuListener* pListener;
public:
	MenuItem(int i) : pListener(0), id(i) {}

	void setListener(IMenuListener* p) { pListener = p; }
	// addListener

	// �̰��� ���̺귯�� �̹Ƿ� ����� ������ ���� ����.
	virtual void command()
	{
		// �޴��� ���õ� ����� �ٽ� �ܺο� �˷��� �Ѵ�.
		// "��ü�� �ܺη� �̺�Ʈ�� �߻��Ѵ�." ��� ǥ��
		if (pListener)
			pListener->onCommand(id);
	}
};

class Dialog : public IMenuListener
{
public:
	virtual void onCommand(int id)
	{
		// �������̽� ����: � ��ü�κ��� �̺�Ʈ�� �߻��ߴ��� ���θ� �ݵ�� �б��ϴ� �ڵ尡 �ʿ��ϴ�.
		// ���� �ڵ鷯�� �������̽��� �� ����.
		// Java8������ �ڵ鷯�� ó���ϱ��� method reference ��� ���� �����Ѵ�.
		switch (id)
		{
		case 11: open(); break;
		case 12: close(); break;
		}
	}

	void open() { cout << "Dialog open" << endl; }
	void close() { cout << "Dialog close" << endl; }
};

int main()
{
	Dialog dialog;

	MenuItem m1(11);
	MenuItem m2(12);
	m1.setListener(&dialog);
	m2.setListener(&dialog);
	m1.command();
	m2.command();
}
