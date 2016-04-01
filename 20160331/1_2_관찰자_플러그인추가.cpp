// ���� ���̺귯���� �����Ǵ� �Ϳ� ���ο� ����� �߰��ϴ� plug-in�� �����غ���
// �׷��� - DLL�� ������!

// �÷������� ����
// BarGraph�� ����ִ� ����� �������� �ʰ�
// SampleGraph(plugin)�� ����ִ� DLL�� �ε��ؼ� ����߰� ����

#include <iostream>
#include <vector>
using namespace std;

#include "IObserver.h"
#include "ioacademy.h"
using namespace ioacademy;

// 1. ������ ���� ����: �ϳ��� �̺�Ʈ�� ���� ��ü�� �����ϴ� ����.

// IObserver.h �� �̵��ؾ� �մϴ�.
#if 0
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};
#endif

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

class Subject
{
	vector<IObserver*> v;
public:
	//------------------------------
	Subject()
	{
		// 1. ��ӵ� ������ ��� DLL�� �����Ѵ�.
		IoEnumFiles("D:\\plugin", "*.dll", LoadModule, this);	// LoadModule�� param���� this ����
	}

	// static ��� �Լ��� this�� �����Ƿ� �Ϲ� �Լ� �����Ϳ� �ñ״�ó�� �����ϴ�.
	static int LoadModule(string name, void* param)
	{
		cout << name << endl;

		// 2. DLL�� �ε��Ѵ�.
		void* addr = IoLoadModule(name);	// gcc������ dlopen()�� so ������ �����ε� ����

		// 3. ��ӵ� �Լ��� ã�´�.
		typedef IObserver* (*FP)();
		FP f = (FP)IoGetFunctionAddress(addr, "CreateGraph");	// void* �����ϹǷ� ĳ����

		// 4. ��ü ����
		IObserver* p = f();

		// 5. SampleGraph�� �����ڷ� ����Ѵ�.
		Subject* self = static_cast<Subject*>(param);	// this�� ���޹޾� ��ü�� �޼ҵ� ȣ��
		self->attach(p);

		return 1;	// 0: �ϳ��� �ҷ���. 1:��� ������ ��� �����ش޶�.
	}

	//------------------------------

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

	BarGraph bg;
	table.attach(&bg);

	table.edit();
}
