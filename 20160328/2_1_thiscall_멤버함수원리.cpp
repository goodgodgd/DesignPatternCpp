// 목표: 객체의 함수 동작 원리 이해
// http://d.pr/n/1kzQ7

#include <iostream>
using namespace std;

class Point
{
	// field, member variable
	int x, y;
public:
	// member function, method
	void set(int a, int b)	// function signature: void set(Point* const this, int a, int b)
	{
		x = a;	// this->x = a;
		y = b;	// this->y = b;
	}

	// static method, class method
	static void foo(int a)	// function signature: void foo(int a)
	{
//		x = a;	// this->x = a; 가 되어야 하는 this가 없다!
	}
};

int main()
{
	Point p1, p2;
	// p1의 멤버 함수인 것처럼 보이지만 set 함수는 모든 객체에 공유되고
	// set(&p1, 10, 20) 이라고 컴파일 됨, 객체 내부에서 부르는게 아니라 객체의 메모리를 함수 인자로 보냄
	// push 20
	// push 10
	// mov ecx (&p1 전달)
	// call set
	p1.set(10, 20);

	Point::foo(10);	// 정적 멤버 함수는 객체 없이 호출 가능하다. -> this가 전달되지 않는다.
}
