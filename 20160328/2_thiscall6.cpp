// Window를 캡슐화 해봅시다.
// Window를 사용한다는 것은 event-driven method 구현, 클릭, 키보드에 대한 message handler 연결

// http://d.pr/n/mDpc

#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

// 기본적인 message handler를 사용하기 위해 인자도 많고 알아야 할 것이 많다.
#if 0
int foo(int handle, int msg, int param1, int param2)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		cout << "left button down" << endl;
		break;
	case WM_KEYDOWN:
		cout << "key down" << endl;
		break;

	}
	// 에러 발생하지 않음
	return 0;
}

int main()
{
	int h1 = IoMakeWindow(foo);	// window 만들고 이벤트 핸들러 지정
	IoProcessMessage();	// message loop 돌려줌
}
#endif

#include <map>

class Window
{
	static map<int, Window*> this_map;
public:
	void create()
	{
		// 일반 멤버 함수 못 받는다.
		int handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	virtual void onLButtonDown() {}
	virtual void onKeyDown() {}

	// static 이어야만 IoMakeWindow에 전달될 수 있다.
	// 그럼 this를 받을 수 있게 map을 써야 한다.
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			self->onLButtonDown();
			break;
		case WM_KEYDOWN:
			self->onKeyDown();
			break;

		}
		// 에러 발생하지 않음
		return 0;
	}
};

// static은 외부 선언 필요
map<int, Window*> Window::this_map;

class MyWindow : public Window
{
public:
	// Window 메시지 핸들러 중에서 자신이 필요한 부분의 가상함수만 구현
	virtual void onLButtonDown() {
		cout << "LButton" << endl;
	}
	virtual void onKeyDown() {
		cout << "Key Down" << endl;
	}

};

int main()
{
	MyWindow w;
	w.create();		// 이 순간 윈도우가 만들어져야 합니다.
					// 왼쪽 버튼을 누르면 "LButton" 이라고 출력되어야 합니다.
	IoProcessMessage();
}
