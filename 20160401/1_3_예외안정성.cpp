// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생하면 소멸자가 호출되지 않는다.

// 스마트 포인터 사용
// 예외 안전성 (Exception safety)
// 1. 완전 보장: 예외가 없다.
// 2. 강력 보장: 예외가 발생해도 잡을 경우(catch), 객체 상태는 예외 발생전으로 복구된다.
//				=> STL 에서는 모두 이걸 사용
// 3. 기본 보장: 예외가 발생해도 자원 누수는 없다. 단 객체 상태는 알 수 없기 때문에 사용이 불가능하다.

// 허브 셔터 - 예외 안정성
// -Exceptional C++
// -More Exceptional C++
// -Exceptional C++ Style

#include <iostream>
using namespace std;

#include <memory>		// unique_ptr


// uniqe ptr 아니면? - 소멸자 호출 안돼
// p1 생성하고 예외발생하면??

class Image
{
public:
	Image() { cout << "이미지 생성" << endl; }
	~Image() { cout << "이미지 파괴" << endl; }
};

#if 0
class Test
{
	unique_ptr<Image> p1;
	unique_ptr<Image> p2;
public:

	// 멤버 변수 타입이 객체 타입이라면, 생성자에서 예외가 발생하였을 경우
	// 멤버 변수의 소멸자의 호출을 표준에서는 보장하고 있다.
	Test() : p1(new Image), p2(new Image)
	{
		throw std::bad_alloc();	// 강제 예외 발생

	}

	// 생성자에서 예외가 해서 ~Test가 호출되지는 않지만
	// Image는 객체 타입이기 때문에 Image의 소멸자는 호출된다.
	~Test()
	{
		cout << "소멸자 호출" << endl;
	}
};
#endif

class Test
{
	Image* p1;
	Image* p2;
public:

	// 멤버 변수 타입이 객체 타입이라면, 생성자에서 예외가 발생하였을 경우
	// 멤버 변수의 소멸자의 호출을 표준에서는 보장하고 있다.
	Test() : p1(new Image), p2(new Image)
	{
		throw std::bad_alloc();	// 강제 예외 발생

	}

	// 생성자에서 예외가 해서 ~Test가 호출되지는 않지만
	// Image는 객체 타입이기 때문에 Image의 소멸자는 호출된다.
	~Test()
	{
		cout << "소멸자 호출" << endl;
	}
};


int main()
{
	try
	{
		Test t;
	}
	catch (...)
	{

	}
}