// 핸들러 방식의 이벤트 처리
//	=> 함수 포인터
//	=> IPhone target-action
//		C# delegate
//		MFC message map
//		Qt signal slot

// 문제점: C++에는 범용 함수 포인터라는 개념이 존재하지 않는다.
// 범용 함수 포인터: 클래스 멤버 함수 포인터, 일반 함수 포인터
// 이제 범용 함수 포인터를 만들어 보자.
// 방법: 일반 함수 포인터를 다룰수 있는 클래스를 만들고, 멤버 함수 포인터를 다룰 수 있는 클래스를 만드는데 같은 부모에서 상속 받게 만든다.

#include <iostream>
using namespace std;

class Dialog;

// 이 코드의 문제: 이벤트핸들러가 Dialog 클래스에 의존한다.
class MenuItem
{
	void(Dialog::*handler)();
	Dialog* object;
public:
	void setHandler(void(Dialog::*h)(), Dialog* o)
	{
		handler = h;
		object = o;
	}

	virtual void command()
	{
		(object->*handler)();
	}
};

class Dialog
{
public:
	void open() { cout << "Dialog open" << endl; }
	void close() {cout << "Dialog close" << endl;}
};

// 그런데 만약 이벤트 핸들러로 일반 함수를 쓰고 싶다면??
int main()
{
	MenuItem m1;
	MenuItem m2;

	Dialog dlg;
	m1.setHandler(&Dialog::open, &dlg);
	m2.setHandler(&Dialog::close, &dlg);

	m1.command();
	m2.command();
}
