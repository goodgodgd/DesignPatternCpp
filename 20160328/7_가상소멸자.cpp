
// http://d.pr/n/1lDec

#include <iostream>
using namespace std;

// 1. 부모 클래스의 소멸자가 가상 ㅎ마수이면, 모든 자식의 소멸자도 가상함수이다.
// 2. 모든 부모 클래스의 소멸자는 반드시 가상함수이어야 한다.
// 원리 설명: Inside C++ Object - 스탠리 립만

class Base {
public:
	virtual ~Base() {}
};

class Derived : public Base
{
public:
	Derived() { cout << "자원 할당" << endl; }
	~Derived() { cout << "자원 해지" << endl; }
};

int main()
{
	Base* p = new Derived;	// 생성자 온전히 호출
							// 생성자는 Derived로 생성했기 때문에 의도한 대로 작동한다.

	delete p;				// 소멸자 호출 안됨
							// p의 타입이 Base이기 때문에 Base의 소멸자를 호출하려 한다.
							// 따라서 부모 클래스의 소멸자는 반드시 가상함수로 만들어줘야 한다.

//	Derived d;
}
