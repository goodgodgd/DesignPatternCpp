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
	Image* p1;
	Image* p2;
public:

	// 포인터 변수에 new로 객체를 생성하면 heap 영역에 생성되고 
	// heap에 생성된 것은 명시적으로 delete를 해줘야만 해지가 된다.
	// 즉 여기서는...
	// 1) 생성자에서 예외 발생
	// 2) 소멸자 호출 안됨
	// 3) p1, p2 메모리 해지 안됨
	Test() : p1(new Image), p2(new Image)
	{
		throw std::bad_alloc();	// 강제 예외 발생
	}
	~Test()
	{
		delete p1;
		delete p2;
		cout << "소멸자 호출" << endl;
	}
};
#endif

// 하지만 포인터가 아닌 객체 자체로 생성하면 stack에 메모리가 할당되고
// stack에 생성된 것은 명시적은 해지를 하지 않아도 객체가 쓰이지 않게 되면 
// 멤버 변수의 소멸자 호출이 보장된다.
// 그래서 객체를 raw pointer로 선언하지 않고 smart pointer로 선언하면
// 그것은 stack에 생성되는 객체이기 때문에 소멸자 호출이 보장된다.
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

	// 생성자 Test()에서 예외가 발생한 경우 소멸자 ~Test()가 호출되지는 않지만
	// p1, p2는 객체 타입이기 때문에 Image의 소멸자는 호출된다.
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