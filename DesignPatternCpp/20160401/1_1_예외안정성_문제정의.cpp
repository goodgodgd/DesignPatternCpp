// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생하면 소멸자가 호출되지 않는다.

#include <iostream>
using namespace std;

class Test
{
	int* p1;
	int* p2;
public:
	Test()
	{
		// new는 예외를 던질 수 있다.
		p1 = new int;
		throw std::bad_alloc();	// 강제 예외 발생
		p2 = new int;	// 이 순간 메모리가 부족했습니다. 어떤 문제가 있을까요?
						// new는 메모리가 부족하면 bad_alloc 이라는 예외가 발생합니다.
						// 그럴때 p1은 할당이 됐는데 소멸자가 호출이 안된다. -> p1에 대한 메모리 누수
						// 해결방법? 다음 코드에...
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
	}
	catch (...)
	{

	}
}