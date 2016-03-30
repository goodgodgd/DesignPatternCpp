
#include <iostream>
using namespace std;

#if 0
class Car
{
public:
	Car() { cout << "자원 생성" << endl; }
	~Car() { cout << "자원 해지" << endl; }
	void go()	{ cout << "Car go" << endl; }
};

int main()
{
	Car* p = new Car;
	p->go();
	(*p).go();

	delete p;	// 반드시 자원을 해지해줘야 한다. 잊어버리는 경우 많아
	// 명시적 메모리 관리
	// 장점: 원할 때 파괴할 수 있다.
	//		java는 프로그래머가 파괴할 수 없어. garbage collection 기반 언어의 한계
	// 단점: 잊어버리면 메모리 누수

	// 스마트 포인터: 자원관리를 자동으로 해주자
}
#endif

class Car
{
public:
	Car() { cout << "자원 생성" << endl; }
	~Car() { cout << "자원 해지" << endl; }
	void go()	{ cout << "Car go" << endl; }
};

// 스마트 포인터
// 개념: 임의의 객체가 다른 객체의 포인터의 역할을 수행하는 것.
// 구현원리: -> 연산자와 * 연산자를 재정의해서 포인터처럼 보이게 만든다.
// 장점: 진짜 포인터가 아니라 객체이다.
//		생성/복사/대입/소멸의 모든 과정을 제어할 수 있다.
// 활용: 대표적 활용은 소멸자에서의 자동 삭제 기능이다.
// 단점: 문제가 생겼을 때 문제를 찾기 어렵다.

// C++ 표준에서도 이미 다양한 정책을 가지고 있는 스마트 포인터를 제공하고 있습니다.
//	C++99/03 - auto_ptr
//	C++11/14 - unique_ptr, share_ptr, weak_ptr, auto_ptr(deprecated, 쓰지마)
//	소유권이    독점	   공유		  아무도 안줘
// 포인터는 소유권이다. 대입 뿐만 아니라 "이동"이란 개념도 이해해야 한다.
// 최근 경향은 raw pointer 개념을 쓰지 않게 해야한다.
// C언어와 C++은 이제 서로 다른 길로 가고 있다.
// 스마트 포인터 써도 순환참조 쓰면 메모리 누수 발생할 수 있다.

#if 0
class Ptr
{
	Car* obj;
public:
	Ptr(Car* p = 0) : obj(p) {}
	~Ptr() { delete obj; }
};


int main()
{
	// p는 스택에 생성된다. main이 끝날 때 자동으로 소멸자가 실행된다.
	Ptr p = new Car;
	// 근데 지금은 함수는 실행 안되
	p->go();
	(*p).go();
}
#endif

// 모든 객체에서 동작하도록 template으로 만들자.
template <typename T>
class Ptr
{
	T* obj;
public:
	// 게다가 이것들을 inline화 하면 기본 포인터를 사용하는 것과 같은 성능 낸다. 기계어도 비슷해
	inline Ptr(T* p = 0) : obj(p) {}
	inline ~Ptr() { delete obj; }

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }
};


int main()
{
	// p는 스택에 생성된다. (객체로 생성된다.) main이 끝날 때 자동으로 소멸자가 실행된다.
	Ptr<Car> p = new Car;
	// operator 재정의로 이제 된다!!
	p->go();
	(*p).go();
}
