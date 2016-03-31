// 윈도우는 Composite Pattern으로 구현되어 있다. 윈도우 안에 윈도우 넣을 수 있어.
// A윈도우 안에 B윈도우 있을 때 B윈도우를 클릭했을때 A에도 책임을 전가할 수도 있어야 한다.

// MVC 모델
// View: 화면, Model: 데이터, App(control): 어플객체따로
// view에서 이벤트를 받지만 app으로도 책임이 전가되어야 한다. (종료누르면 app 종료되어야)

// 책임의 전가 패턴
// - 이벤트 발생시 처리되지 않을 경우 다음 객체에 전달한다.
// - 처리할 수 있을 때 까지 고리에 따라 이벤트를 전달한다.

// 사용
// 1) 맥킨토시 계열 - 코코아, 코코아 터치: Reponder Chain
//		: View -> ViewController -> AppDelegate
// 2) MFC에서 메뉴 메시지 - 책임의 고리
//		: View -> Document -> Frame(최상위 윈도우) -> App

// 한번에 모든 객체에 이벤트 발생하면 안되나? 자식에서 책임을 처리할 수 있으면 거기서 끝내야

#include <iostream>
using namespace std;

#include <map>
#include <vector>
#include "ioacademy.h"
using namespace ioacademy;

class Window
{
	static map<int, Window*> this_map;

	int handle;					// C함수를 통해 윈도우를 실제로 조작하기 위해서는 반드시 저장해야 한다.
	Window* parent;				// 부모 윈도우는 1개이다.
	vector<Window*> children;	// 자식은 여러개이다.
	// composit 아냐?
public:
	Window() : parent(0) {}

	void addChild(Window* p)
	{
		p->parent = this;
		children.push_back(p);
		
		// C 함수로 자식 윈도우를 붙인다.
		IoAddChild(this->handle, p->handle);
	}

	void create()
	{
		// 일반 멤버 함수 못 받는다.
		handle = IoMakeWindow(foo);
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
};

class ImageView : public Window
{
public:
	virtual void onLButtonDown()
	{
		cout << "Image" << endl;
	}
};

int main()
{
	MyWindow w;
	w.create();		// 이 순간 윈도우가 만들어져야 합니다.

	ImageView imageView;
	imageView.create();

	w.addChild(&imageView);

	IoProcessMessage();
}
