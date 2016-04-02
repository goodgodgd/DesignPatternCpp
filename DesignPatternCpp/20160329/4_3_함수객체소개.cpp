
// 함수 객체 => 함수처럼 사용 가능한 객체
// 함수 vs 함수 객체
// 1) 함수는 자신만의 타입이 없다.
//		시그니처가 동일한 모든 함수는 같은 타입이다.
// 2) 함수 객체는 자신만의 타입이 있다.
//		시그니처가 동일하더라도 모든 함수 객체는 다른 타입이다.

// java에서는 연산자 오버로딩의 악영향을 우려해 제공하지 않는다.

#include <iostream>
using namespace std;

struct Plus
{
	// 연산자 오버로딩
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main()
{
	Plus p;
	// 클래스를 함수처럼 사용하고 싶다.
	int n = p(10, 20);
	cout << n << endl;
}
