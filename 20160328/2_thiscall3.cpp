// 멤버 함수와 함수 포인터
// http://d.pr/n/7Lpj

#include <iostream>
using namespace std;

class Dialog
{
public:
	void close()	// void close(Dialog* this)
	{ cout << "Dialog close" << endl; }

	static void goo()	// void goo()
	{ cout << "goo" << endl; }
};

void foo() { cout << "foo" << endl; }

// 1. 일반 함수 포인터에 멤버 함수의 주소를 담을 수 없다.
// 2. 멤버 함수 포인터를 만들고 사용하는 방법
// 3. 일반 함수 포인터에 정적 멤버 함수의 주소를 담을 수 있다.
int main()
{
	void(*f)() = &foo;
	f();	// 함수를 함수 포인터로 호출

	// C와는 다르게 C++에서는 멤버 함수 포인터도 지원
	// 1.에 의해 아래는 컴파일 안됨
//	void(*f1)() = &Dialog::close;

	Dialog dlg;
	// 아래와 같이 써야 맞다. Dialog* this 를 전달해주기 위해
	void(Dialog::*f2)() = &Dialog::close;
	// 그런데 멤버 함수를 호출하기 위해선 객체가 필요하다. 아래는 안돼
//	f2();
	// 아래도 안돼, f2는 멤버 함수 아니다.
//	dlg.f2();
	// 아래는 문법은 맞으나 결합이 안돼있다. 연산자 우선 순위
//	dlg.*f2();
	// 동작: 먼저 객체와 결합하고 실행
	(dlg.*f2)();

	void(*f3)() = &Dialog::goo;	// // 객체가 필요없는 정적 함수 -> 일반 함수 포인터
	f3();
}
