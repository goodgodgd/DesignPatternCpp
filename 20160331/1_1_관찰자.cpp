// ����: �������� �����͸� ������� ǥ�� �׸��� �����Ͱ� ������ �� �ﰢ������ ǥ�� �����
// �������1: ������ �׷����� �ֱ������� ǥ�� Ȯ��
// �������2: ǥ�� �ٲ���� �� �׷����� �˷��� - poll, push
// SW ��Ű���Ŀ��� �߿��� ����
// MVC (Model - View - Controller) ��
//		------------   ----------
//		  ������			 �����

#include <iostream>
#include <vector>
using namespace std;

// 1. ������ ���� ����: �ϳ��� �̺�Ʈ�� ���� ��ü�� �����ϴ� ����.

// ������ �������̽�
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};

class PieGraph : public IObserver
{
public:
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Pie Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

class BarGraph : public IObserver
{
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Bar Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

#if 0
// ������ ���: ǥ - (���̶�� �θ��ϴ�)
class Table
{
	int data[5];
	vector<IObserver*> v;
public:
	Table() { memset(data, 0, sizeof(data)); }
	void attach(IObserver* p) { v.push_back(p); }
	void detach(IObserver* p) {}

	void notify(void* p)
	{
		// auto�� ���� ���: ������ �߿��� ��
		// vector<IObserver*>::iterator a = v.begin();
		// auto�� ���� �ʴ� ���: ��Ȥ int, long, double, float �� Ÿ���� �߿��� ����
		// built-in type�� ���ؼ� �� ���� �ʰ� ��ü�� ���ؼ� ���� ����.

		for (IObserver* e : v)	// for (auto e : v) �� ����
			e->onUpdate(p);
	}

	void edit()
	{
		while (1)
		{
			int index;
			cout << "index : ";
			cin >> index;
			cout << "data : ";
			cin >> data[index];

			// ��� �����ڿ� �˷��ش�.
			notify(data);
		}
	}
};
#endif


// ������: ���� (���̺���) ������ ����, ���� ���� �˰� �־�� �Ѵ�.
// ��� Table(������ ���)�� Ư¡�� �׻� �����ϴ�.
// -> �θ�� ��������.

// ����: �޶����� ���� �����Լ�ȭ �ؼ� �ڽ��� ����,
//		�������� ���� �θ� Ŭ������ ���� ����
// ó������ �������� ���踦 �ϱ� ���ٴ� ¥�鼭 �ߺ��Ǵ� �κ��� ���������� ����� ������.

class Subject
{
	vector<IObserver*> v;
public:
	void attach(IObserver* p) { v.push_back(p); }
	void detach(IObserver* p) {}

	void notify(void* dat)
	{
		for (IObserver* e : v)	// for (auto e : v) �� ����
			e->onUpdate(dat);
	}
};

// ������ ���: ǥ - (���̶�� �θ��ϴ�)
class Table : public Subject
{
	int data[5];
public:
	Table() { memset(data, 0, sizeof(data)); }

	void edit()
	{
		while (1)
		{
			int index;
			cout << "index : ";
			cin >> index;
			cout << "data : ";
			cin >> data[index];

			// ��� �����ڿ� �˷��ش�.
			notify(data);
		}
	}
};

int main()
{
	Table table;

	PieGraph pg;
	BarGraph bg;
	table.attach(&pg);
	table.attach(&bg);

	table.edit();
}
