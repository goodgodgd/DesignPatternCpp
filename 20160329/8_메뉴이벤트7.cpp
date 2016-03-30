
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
// �̹� ǥ�ؿ� ������ �Լ� �����Ͱ� �ֽ��ϴ�. C++11
// TR1 - 2008�⵵�� �߰��Ǿ����ϴ�.
// function, bind �� ���� ��Ȯ�� ����� document�� ���� �ʹٸ� boost�� �����϶�.
// boost���� ���� ���� ��ɵ��� ������ �̷��� ��������� ���� ����� ������ �ϸ� ȥ�� ���ϰ� �ȴ�.

#if 0
int main()
{
	function<void()> f = &foo;
	f();

	Dialog dialog;
	f = bind(&Dialog::close, &dialog);
	f();

	// ������ ���ڵ� �Է� ����
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

	f = bind(&hoo, 10, _1);	// �ι�° ���ڴ� ���� �Է��ϴµ� �װ��� _1�� �����Ѵ�.
	f(300);		// hoo(100, 300)

	f = bind(&koo, 10, _1, 30, _1);
	f(20);		// koo(10, 20, 30, 20)

	function<void(int, int)> h;
	h = bind(&koo, _2, _1, _1, _2);
	h(10, 20);
}
