
#include <iostream>
using namespace std;

struct ICommand
{
	virtual void excute() = 0;
	virtual ~ICommand() {}
};

class FunctionCommand : public ICommand
{
	typedef void(*HANDLER)();	// 함수 포인터
	HANDLER handler;

public:
	FunctionCommand(HANDLER h) : handler(h) {}

	void excute() { handler(); }
};

// 모든 클래스의 멤버 함수의 주소를 담을 수 있는 클래스를 설계해보자.
template <typename T>
class MemberCommand : public ICommand
{
	typedef void(T::*HANDLER)();	// 멤버 함수 포인터
	HANDLER handler;
	T* object;
public:
	MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}

	void excute() { (object->*handler)(); }
};

// 4. 클래스 템플릿은 암시적 추론이 불가능하기 때문에 항상 복잡해 보입니다.
//		암시적 추론이 가능한 함수 템플릿으로 헬퍼를 제공합니다.
template <typename T>
MemberCommand<T>* cmd(void(T::*f)(), T* o)
{
	return new MemberCommand<T>(f, o);
}

// 5. 라이브러리의 일관성을 위해서 FunctionCommand를 만드는 cmd도 제공합니다.
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

class Dialog
{
public:
	void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

int main()
{
	Dialog dialog;

	MenuItem m;
	m.setHandler(cmd(&Dialog::close, &dialog));	// cmd가 Dialog::close를 ICommand 라는 범용함수포인터로 변환
	m.command();

	m.setHandler(cmd(&foo));	// cmd가 foo를 ICommand 라는 범용 함수 포인터로 변환
	m.command();
}
