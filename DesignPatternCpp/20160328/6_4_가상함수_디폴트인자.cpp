// C++을 이해할 때 컴파일 시간에 결정되는지 런타임에 동작하는지 알아야한다.
// 디폴트 인자: 컴파일 시간에 결정된다.
// 가상 함수: 실행 시간에 결정된다.
// 1. 가상함수에서는 되도록이면 디폴트 인자를 사용하지 말자. (컴파일 시간에 결정되는 것과 섞으면 안된다. 오버 로딩도 마찬가지?)
// 2. 사용했다면 재정의 할 때 절대 변경하지 말자.

// http://d.pr/n/1kmqW

#include <iostream>
using namespace std;

class A
{
public:
	virtual void foo(int a = 10)
	{
		cout << "A: " << a << endl;
	}
};

class B : public A
{
public:
	virtual void foo(int a = 20)
	{
		cout << "B: " << a << endl;
	}
};

int main()
{
	A* p = new B;	// 컴파일 시에 결정 => A의 타입에 의해 foo(a)의 디폴트 값 결정
	p->foo();		// 어떻게 나올까? => "B=10"
					// p의 타입은 A이기 때문에 디폴트인자는 컴파일 시간에 10으로 결정되지만
					// 실행 시간에 B의 foo와 동적 바인딩 되었기 때문에 B가 출력됨
}
