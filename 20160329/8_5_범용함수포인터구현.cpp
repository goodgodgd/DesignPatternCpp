
// 일반 함수와 모든 클래스의 멤버 함수를 보관하는 범용적 함수 포인터 타입을 만들어 보자.
// 멤버 함수 포인터 클래스와 일반 함수 포인터 클래스를 같은 부모로부터 상속받게 만든다.

#include <iostream>
using namespace std;

#if 0
// 1. 함수 포인터 개념을 클래스로 래핑해 봅시다.
// 래핑: 함수포인터와 같은 용법을 갖게 한다.
class FunctionCommand
{
	typedef void(*HANDLER)();	// 함수 포인터
	HANDLER handler;

public:
	FunctionCommand(HANDLER h) : handler(h) {}

	void excute() { handler(); }
};

// 모든 클래스의 멤버 함수의 주소를 담을 수 있는 클래스를 설계해보자.
template <typename T>
class MemberCommand
{
	typedef void(T::*HANDLER)();	// 멤버 함수 포인터
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

// 여기까지 함수 포인터와 멤버 함수 포인터를 쓰는 방법
int main()
{
	Dialog dialog;
	MemberCommand<Dialog> mc(&Dialog::close, &dialog);
	mc.excute();

	FunctionCommand fc(&foo);
	fc.excute();
}
#endif

// C++에서는 함수 템플릿은 암시적 추론이 가능하지만, 클래스 템플릿은 암시적 추론이 불가능합니다.
#if 0
template <typename T>	// 함수 템플릿 - 명시적 추론, 암시적 추론
void hoo(T a) {}

template <typename T>	// 클래스 템플릿 - 명시적 추론
class AAA
{};

int main()
{
	hoo(10);
	hoo(3.14);
	// 클래스 템플릿은 명시적으로 정의해줘야 한다.
	AAA<int> aaa;
}
#endif

// 3. A와 B를 묶기 위해서는 공통의 부모를 제공해야 한다.

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

// 모든 클래스 멤버 함수의 주소를 담을 수 있는 클래스를 설계해보자.
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

class Dialog
{
public:
	void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

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

// ICommand* p 하나로 두 가지 포인터를 모두 사용한다.
int main()
{
//	ICommand* p = new FunctionCommand(&foo);
	ICommand* p = cmd(&foo);
	p->excute();

	Dialog dialog;
	// 멤버 함수 포인터를 쓰는 것이 여전히 복잡해 보인다.
//	p = new MemberCommand<Dialog>(&Dialog::close, &dialog);
	// 훨씬 간편하다. 그런데 FunctionCommand 도 이렇게 하고 싶다.
	p = cmd(&Dialog::close, &dialog);
	p->excute();
}
