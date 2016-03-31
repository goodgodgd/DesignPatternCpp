// GoF의 디자인 패턴에서는 이벤트 처리에 관련된 패턴이 2가지 있습니다.
// 1. 관찰자			: 이벤트 발생시 등록된 객체에게 이벤트를 전파
// 2. 책임의 전가	: 이벤트 발생시 다음 객체에게 전달

// 패턴 3가지 종류: 생성, 구조, 행위

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

	virtual bool onLButtonDown() { return false; }
	virtual void onKeyDown() {}

	// 내생각: fireLButtonDown은 상속될 필요가 없는 "설계"이므로 private 해준다. foo도 내부에서만 사용
private:
	// 아래 함수가 책임의 전가(Chain of Responsibility) 패턴의 핵심입니다.
	void fireLButtonDown()
	{
		// 1. 먼저 자신(자식)이 처리를 시도합니다.
		if (onLButtonDown() == true)	// 자신이 처리해서 끝날 수 있으면 여기서 끝내
			return;
		
		// 2. 자신이 처리하지 않은 경우 부모에게 전달
		if (parent != 0)
			parent->fireLButtonDown();
	}

	// static 이어야만 IoMakeWindow에 전달될 수 있다.
	// 그럼 this를 받을 수 있게 map을 써야 한다.
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			// 비 가상함수를 호출해서 무조건 부모의 함수가 호출되게 한다. -> 책임의 전가
			self->fireLButtonDown();
			//self->onLButtonDown();
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
	virtual bool onLButtonDown() {
		cout << "LButton" << endl;
		return false;
	}
};

class ImageView : public Window
{
public:
	virtual bool onLButtonDown()
	{
		cout << "Image" << endl;
		return false;
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
