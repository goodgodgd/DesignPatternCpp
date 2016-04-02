// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생하면 소멸자가 호출되지 않는다.

// 방법 1. 생성자에서 자원을 할당하지 말고 자원할당 전용함수를 제공하자.
//		Two Phase Constructor - 2단 생성자 호출

// 문제점: 객체의 상태가 불완전한 상태가 될 수 있다.
//		생성만 하면 객체를 사용할 준비가 안돼 있다. 생성자 한 줄에 준비가 안된다.

#include <iostream>
using namespace std;

class Test
{
	int* p1;
	int* p2;
public:
	// 생성자에서는 절대 예외가능성이 있는 자원할당을 하지말자.
	Test() : p1(0), p2(0) {}
	// 대신 생성 함수를 만들자. -> 여기서는 예외발생해도 소멸자 호출된다.
	void Construct()
	{
		// new는 예외를 던질 수 있다.
		p1 = new int;
		throw std::bad_alloc();	// 강제 예외 발생
		p2 = new int;
	}

	~Test()
	{
		cout << "소멸자 호출" << endl;
		delete p1;
		delete p2;
	}
};

int main()
{
	try
	{
		Test t;
		t.Construct();
	}
	catch (...)
	{

	}
}