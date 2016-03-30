
#include <iostream>
using namespace std;

class Dialog
{
public:
	void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

void goo(int n)			{ printf("goo: %d\n", n); }
void hoo(int a, int b)	{ printf("hoo: %d %d\n", a, b); }
void koo(int a, int b, int c, int d)
{
	printf("koo: %d %d %d %d\n", a, b, c, d);
}

#include <functional>
// 이미 표준에 범용적 함수 포인터가 있습니다. C++11
// TR1 - 2008년도에 추가되었습니다.
// function, bind 에 대한 정확한 용법과 document를 보고 싶다면 boost를 참고하라.
// boost에는 많은 좋은 기능들이 있지만 이러한 배경지식이 없는 사람과 협업을 하면 혼자 일하게 된다.

#if 0
int main()
{
	function<void()> f = &foo;
	f();

	Dialog dialog;
	f = bind(&Dialog::close, &dialog);
	f();

	// 결정된 인자도 입력 가능
	f = bind(&goo, 10);
	f();
	f = bind(&hoo, 10, 20);
	f();
	f = bind(&koo, 10, 20, 30, 40);
	f();
}
#endif

using namespace std::placeholders;

int main()
{
	function<void(int)> f = &goo;
	f(10);

	f = bind(&hoo, 10, _1);	// 두번째 인자는 직접 입력하는데 그것을 _1로 정의한다.
	f(300);		// hoo(100, 300)

	f = bind(&koo, 10, _1, 30, _1);
	f(20);		// koo(10, 20, 30, 20)

	function<void(int, int)> h;
	h = bind(&koo, _2, _1, _1, _2);
	h(10, 20);
}
