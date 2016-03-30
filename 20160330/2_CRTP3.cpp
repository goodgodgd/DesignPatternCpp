
#include <iostream>
using namespace std;

// �̷��� �ϸ� Base�� �Ҹ��� ȣ�� -> �ϰ͵� �ȳ��´�.
#if 0
class Base {};

class Derived : public Base
{
public:
	~Derived() { cout << "�Ҹ��� ȣ��" << endl; }
};

int main()
{
	Base* p = new Derived;
	delete p;
}
#endif

// �׷��� �׻� �θ� �����Լ� �Ҹ��ڷ� ������ش�.
#if 0
class Base 
{
public:
	virtual ~Base() {}
};

class Derived : public Base
{
public:
	virtual ~Derived() { cout << "�Ҹ��� ȣ��" << endl; }
};

int main()
{
	Base* p = new Derived;
	delete p;
}
#endif

// �׷��� �����Լ��� ���� �����Լ� ���̺��̶� ����� �ִ�.
// �����Լ� ���̺� ����� ���ֱ� ���� template���� Ÿ���� ���ؼ� �ı��Ѵ�.
template <typename T>
class Base
{
	// �ڽ��� ���ؼ��� ȣ���ϰڴ�.
protected:
	~Base() {}
public:
	void finalize()
	{
		// �ڽ��� Ÿ������ ��ü�� �ı��Ѵ�.
		delete static_cast<T*>(this);
	}
};

class Derived : public Base<Derived>
{
public:
	~Derived() { cout << "�Ҹ��� ȣ��" << endl; }
};

int main()
{
	Base<Derived>* p = new Derived;
	p->finalize();
}
