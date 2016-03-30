
#include <iostream>
using namespace std;
#include <algorithm>		// 이미 정책 변경 가능한 sort() 여기 있습니다.
#include <functional>		// less, greater 함수 객체가 이 안에 있습니다.

inline bool cmp1(int a, int b)	{ return a > b; }
inline bool cmp2(int a, int b)	{ return a < b; }

// 이렇게 함수 객체를 만드는 것이 귀찮아서 Lambda 나왔다.
struct abs_less
{
	// 앞에 inline 없어도 선언을 하면 inline?
	bool operator()(int a, int b) { return abs(a) < abs(b); }
};

int main()
{
	int x[10] = { 1, 3, 5, 7, 8, 2, 4, 6, 8, 10 };

	// 1. 정책으로 함수를 사용할 때
	// 장점: 정책을 여러번 교환해도 sort()의 기계어는 한개이다.
	// 단점: 정책이 인라인 치환이 안되므로 성능 저하가 있다. 
	sort(x, x + 10, cmp1);		// sort(int*, int*, bool(*)(int,int))
	sort(x, x + 10, cmp2);		// 위의 구현을 사용 -> 코드가 한번만 생성됨
	for (int i = 0; i < 10; ++i)
		cout << x[i] << " ";
	cout << endl;

	// 2. 정책으로 함수 객체를 사용할 때
	// 장점: 정책이 인라인 치환되므로 빠르게 동작한다.
	// 단점: 정책을 교환한 횟수 만큼의 sort() 기계어 코드 생성
	//		개발자에게 함수 객체 클래스 이름과 함수 객체 객체 이름을 또 지어야 하는 부담. 코드도 길어진다.
	less<int> f1;
	greater<int> f2;
	sort(x, x + 10, f1);		// sort(int*, int*, less<int>)
	sort(x, x + 10, f2);		// sort(int*, int*, greater<int>)	-> 새 코드 생성
	for (int i = 0; i < 10; ++i)
		cout << x[i] << " ";
	cout << endl;

	// lambda: 함수 객체를 쉽게 만드는 문법 - 익명의 함수 객체(클로져)
	// 자동으로 inline이다!!
	// 2008년부터 컴파일러에서 이미 지원하였습니다.
	// - Visual studio 2010, gcc 4.5 부터
	// 1980: C++ 탄생
	// 1998: 1차 표준 확정, 2003년 수정판: C++98/08
	// 2011: 2차 표준 확정, 2014년 수정판: C++11/14 - Modern C++
	// 2017: 3차 표준 확정 예정
	// 람다는 현대 객체 지향 언어에서 모두 지원하는 기술
	// C#: 익명의 델리게이트
	// java: 함수형 인터페이스
	// ObjC: 블록 프로그래밍

	sort(x, x + 10, [](int a, int b){ return abs(a) > abs(b); });
	int n = 20;
	sort(x, x + 10, [n](int a, int b){ return abs(a) > abs(b) + n; });

}
