// 멀티 스레드를 캡슐화 해봅시다.
// Java C#과 다르게 C++ 내부에는 기능이 적다. thread 없어
// OS가 제공하는 API 이용해야. Win32API, System call
// 그런데 API가 C언어로 되어있어서 하부 개념(동작 방식)을 이해해야 사용할 수 있다.
// C++ wrapper 필요
// http://d.pr/n/IpaL

#include <Windows.h>	// for thread
#include <iostream>
using namespace std;

#if 0
// __stdcall: 윈도우 call 방식
DWORD __stdcall foo(void* p)
{
	cout << "Thread start!!" << endl;
	return 0;
}

int main()
{
	// 0: use default value
	// 0으로 처리한 불필요한(알고싶지 않은, 귀찮은) 인자가 너무 많다. (C 언어)
	CreateThread(0, 0, foo, "A", 0, 0);
	getchar();
}
#endif

// MyThread를 구현하기 위해서는 run() 함수와 threadLoop() 함수가 필요
// thread 구현부는 Thread 클래스에서 상속
// run()에서는 threadLoop을 바로 CreateThread()와 연결할 수 없음
// => CreateThread()에 연결 가능한 static 함수 _threadLoop() 만들어 연결
// _threadLoop()에서는 실제 동작해야 하는 threadLoop() 호출 불가 (static 아님)
// => CreateThread()에서 this를 받아와 this->threadLoop()로 실행

class Thread
{
public:
	void run()
	{
		// 멤버 함수 이므로 일반 함수 포인터를 넘기면 안 된다. -> static 멤버 함수
//		CreateThread(0, 0, _threadLoop, 0, 0, 0);
		// static 함수에 this를 전달
		CreateThread(0, 0, _threadLoop, this, 0, 0);
	}

	// 1. 아래 함수가 static 멤버 함수 일 수 밖에 없는 이유: 일반 함수 포인터를 CreateThread()에 넣을 수 없기 때문
	// 2. this가 없으므로 스레드 함수 인자로 this를 전달하는 기술
	// 자바나 안드로이드 프레임워크에서 사용하는 방식
	static DWORD __stdcall _threadLoop(void* user)
	{
		Thread* self = static_cast<Thread*>(user);
		// 정적 함수에서는 (_threadLoop ) 일반 멤버 함수 호출 안됨
//		threadLoop();
		// this를 받아와서 일반 멤버 함수 호출
		self->threadLoop();
		return 0;
	}

	// 실제 스레드 동작이 구현될 함수는 일반적으로 static 아니다.
	virtual bool threadLoop() { return false; }
};

// 아래 클래스는 라이브러리의 사용자 입니다.
class MyThread : public Thread
{
public:
	virtual bool threadLoop()
	{
		cout << "My Thread threadLoop()" << endl;
		return true;
	}
};

int main()
{
	MyThread t;
	t.run();	// 이 순간 스레드가 생성되어서 가상함수인 threadLooop()를 수행해야 합니다.
	getchar();
}

// NEWS: 이제 C11, C++11/14 에서도 thread api 제공하고 있다.
// http://www.cplusplus.com/reference/thread/thread/
