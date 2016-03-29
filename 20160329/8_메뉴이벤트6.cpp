
#include <iostream>
using namespace std;

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


//---------------------------------------------
class MenuItem
{
	ICommand* pCommand;
public:
	void setHandler(ICommand* p) { pCommand = p; }

	void command()
	{
		if (pCommand)
			pCommand->excute();
	}
};

int main()
{
	Dialog dialog;

	MenuItem m;
	m.setHandler(cmd(&Dialog::close, &dialog));
	m.command();

	m.setHandler(cmd(&foo));
	m.command();
}