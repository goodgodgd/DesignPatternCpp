
#include <iostream>
using namespace std;


class Ticket
{
public:
	void print()
	{
		cout << "���� ����ȸ - 2016.12.25" << endl;
	}
};

// Ƽ�Ͽ� ���� ����� �߰��ϰ� �ʹ�.
class Ad1 : public Ticket
{
public:
	void print()
	{
		Ticket::print();	// ������ ����� �̿�
		cout << "�ڵ��� ����" << endl;
	}
};

class Ad2 : public Ad1
{
public:
	void print()
	{
		Ad1::print();	// ������ ����� �̿�
		cout << "TV ����" << endl;
	}
};

// ����� ���� ����� �߰�
// - ���� ������ ������� �Ŀ�, �䱸 ������ ���濡 �����ϱ� ��ƴ�.
// - ����� ����ð��� �����ϴ� ���� �Ұ����ϴ�.
//		: ������ ����� �߰�
// - ��ü�� ���� ���� �ƴ϶� Ÿ�Կ� ���� ����, ���� ��ȭ

int main()
{
	Ticket t;
	t.print();

	Ad1 a1;
	a1.print();

	Ad2 a2;
	a2.print();
}