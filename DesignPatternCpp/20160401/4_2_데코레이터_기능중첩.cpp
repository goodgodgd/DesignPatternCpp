// ������ ����
// - ������ �����ؼ� �ذ��� �� �ֵ��� �Ѵ�.
// - Ŭ������ �� �ϳ����� å���� �������� ����ȭ �� �� �ִ�. (SRP)
// ���ڷ����� ����: ���� ���� �˰����� �̿��ؼ� ū ������ ������ �ذ�

#include <iostream>
using namespace std;

#if 0
class Ticket
{
public:
	void print() { cout << "���� ����ȸ - 2016.12.25" << endl; }
};

class Ad1
{
	// ��� �ƴ� �������� ��� �߰�
	Ticket& ticket;
public:
	Ad1(Ticket& t) : ticket(t) {}
	void print()
	{
		ticket.print();
		cout << "�ڵ��� ����" << endl;
	}
};

class Ad2
{
	// ��� �ƴ� �������� ��� �߰�
	Ticket& ticket;
public:
	Ad2(Ticket& t) : ticket(t) {}
	void print()
	{
		ticket.print();
		cout << "TV ����" << endl;
	}
};

int main()
{
	Ticket t;
	Ad1 ad1(t);
	ad1.print();

	Ad2 ad2(t);
	ad2.print();
}
#endif	// ����: Ticket, Ad1, Ad2 ������ ���� ���� �߻�

// ������ ���Ͽ��� ����� �ռ� ����� ����� ������ ���� 2����
// 1. ������Ʈ: ����� �ռ��� ���� ���� ��ü�� ����
// 2. ���ڷ�����: ����� �ս��� ���� ����� �߰�

// �ٽ� 2����
// 1. ������ ���� ����� �߰� - ������ ����� �߰�
// 2. ����� �ռ� - ����� �߰��ߴ� ��ü�� �ٽ� �߰��� �� �ִ�.

#if 0
// Item�̶� ������ �θ� �ּ� Ticket, Ad1, Ad2 �� ������ �������� ������.
class Item
{
public:
	virtual void print() = 0;
	virtual ~Item() {}
};

class Ticket : public Item
{
public:
	void print()
	{
		cout << "���� ����ȸ - 2016.12.25" << endl;
	}
};

class Ad1 : public Item
{
	// ��� �ƴ� �������� ��� �߰�
	Item& ticket;
public:
	Ad1(Item& t) : ticket(t) {}
	void print()
	{
		ticket.print();
		cout << "�ڵ��� ����" << endl;
	}
};

class Ad2 : public Item
{
	// ��� �ƴ� �������� ��� �߰�
	Item& ticket;
public:
	Ad2(Item& t) : ticket(t) {}
	void print()
	{
		ticket.print();
		cout << "TV ����" << endl;
	}
};

int main()
{
	Ticket t;
	Ad1 ad1(t);
	// �߰��� ��ɿ� �� �߰��ϰ� �ʹ�.
	Ad2 ad2(ad1);
	ad2.print();
}
#endif


class Item
{
public:
	virtual void print() = 0;
	virtual ~Item() {}
};

class Ticket : public Item
{
public:
	void print()
	{
		cout << "���� ����ȸ - 2016.12.25" << endl;
	}
};

// ��� ����(������)�� ������ Ư¡�� �θ�� ��������.
// Ad1, Ad2�� ������ �ѹ��� ����
class Decorator : public Item
{
	Item& item;
public:
	Decorator(Item& i) : item(i) {}
	void print()		// ���� �Լ� �ƴϴ�.
	{
		item.print();
	}
};

// ��� �ƴ� �������� ��� �߰�
class Ad1 : public Decorator
{
public:
	Ad1(Item& t) : Decorator(t) {}		// Decorator(t) �̰� ����??
	void print()
	{
		Decorator::print();				// �θ��� �񰡻� �Լ� �ҷ�����
		cout << "�ڵ��� ����" << endl;	// Ad1�� ��� �߰�
	}
};

class Ad2 : public Decorator
{
public:
	Ad2(Item& t) : Decorator(t) {}
	void print()
	{
		Decorator::print();
		cout << "TV ����" << endl;
	}
};

int main()
{
	Ticket t;
	Ad1 ad1(t);		// Ƽ�Ͽ� ����1 �߰�
	Ad2 ad2(ad1);	// Ƽ�Ͽ� ����1 �߰��� �Ϳ� ����2 �߰�

	ad2.print();	// ���� ����ȸ / �ڵ��� ���� / TV ����
}

//---------------------------
// Zip���� ����Ǿ� �ִ� ������ �о�� �Ѵ�. - NIO(New IO)
// FileInputStream fis = new FileInputStream("a.zip");		// ���� ����
// BufferedInputStream bis  = new BufferedInputStream(fis);	// ������ ���۷� �б�
// ZipInputStream zis = new ZipInputStream(bis);			// ���۸� ZIP�������� �б�
// zis.read();
