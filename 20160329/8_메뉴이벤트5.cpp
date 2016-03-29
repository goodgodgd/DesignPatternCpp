
// �Ϲ� �Լ��� ��� Ŭ������ ��� �Լ��� �����ϴ� ������ �Լ� ������ Ÿ���� ����� ����.
// ��� �Լ� ������ Ŭ������ �Ϲ� �Լ� ������ Ŭ������ ���� �θ�κ��� ��ӹް� �����.

#include <iostream>
using namespace std;

#if 0
// 1. �Լ� ������ ������ Ŭ������ ������ ���ô�.
// ����: �Լ������Ϳ� ���� ����� ���� �Ѵ�.
class FunctionCommand
{
	typedef void(*HANDLER)();	// �Լ� ������
	HANDLER handler;

public:
	FunctionCommand(HANDLER h) : handler(h) {}

	void excute() { handler(); }
};

// ��� Ŭ������ ��� �Լ��� �ּҸ� ���� �� �ִ� Ŭ������ �����غ���.
template <typename T>
class MemberCommand
{
	typedef void(T::*HANDLER)();	// ��� �Լ� ������
	HANDLER handler;
	T* object;
public:
	MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}

	void excute() { (object->*handler)(); }
};

class Dialog
{
public:
	void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

// ������� �Լ� �����Ϳ� ��� �Լ� �����͸� ���� ���
int main()
{
	Dialog dialog;
	MemberCommand<Dialog> mc(&Dialog::close, &dialog);
	mc.excute();

	FunctionCommand fc(&foo);
	fc.excute();
}
#endif

// C++������ �Լ� ���ø��� �Ͻ��� �߷��� ����������, Ŭ���� ���ø��� �Ͻ��� �߷��� �Ұ����մϴ�.
#if 0
template <typename T>	// �Լ� ���ø� - ����� �߷�, �Ͻ��� �߷�
void hoo(T a) {}

template <typename T>	// Ŭ���� ���ø� - ����� �߷�
class AAA
{};

int main()
{
	hoo(10);
	hoo(3.14);
	// Ŭ���� ���ø��� ��������� ��������� �Ѵ�.
	AAA<int> aaa;
}
#endif

// 3. A�� B�� ���� ���ؼ��� ������ �θ� �����ؾ� �Ѵ�.

struct ICommand
{
	virtual void excute() = 0;
	virtual ~ICommand() {}
};

class FunctionCommand : public ICommand
{
	typedef void(*HANDLER)();	// �Լ� ������
	HANDLER handler;

public:
	FunctionCommand(HANDLER h) : handler(h) {}

	void excute() { handler(); }
};

// ��� Ŭ������ ��� �Լ��� �ּҸ� ���� �� �ִ� Ŭ������ �����غ���.
template <typename T>
class MemberCommand : public ICommand
{
	typedef void(T::*HANDLER)();	// ��� �Լ� ������
	HANDLER handler;
	T* object;
public:
	MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}

	void excute() { (object->*handler)(); }
};

class Dialog
{
public:
	void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

// 4. Ŭ���� ���ø��� �Ͻ��� �߷��� �Ұ����ϱ� ������ �׻� ������ ���Դϴ�.
//		�Ͻ��� �߷��� ������ �Լ� ���ø����� ���۸� �����մϴ�.
template <typename T>
MemberCommand<T>* cmd(void(T::*f)(), T* o)
{
	return new MemberCommand<T>(f, o);
}

// 5. ���̺귯���� �ϰ����� ���ؼ� FunctionCommand�� ����� cmd�� �����մϴ�.
FunctionCommand* cmd(void(*f)())
{
	return new FunctionCommand(f);
}

// ICommand* p �ϳ��� �� ���� �����͸� ��� ����Ѵ�.
int main()
{
//	ICommand* p = new FunctionCommand(&foo);
	ICommand* p = cmd(&foo);
	p->excute();

	Dialog dialog;
	// ��� �Լ� �����͸� ���� ���� ������ ������ ���δ�.
//	p = new MemberCommand<Dialog>(&Dialog::close, &dialog);
	// �ξ� �����ϴ�. �׷��� FunctionCommand �� �̷��� �ϰ� �ʹ�.
	p = cmd(&Dialog::close, &dialog);
	p->excute();

	p->excute();
}
