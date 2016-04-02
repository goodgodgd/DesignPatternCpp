// 동적 메모리 할당 후 캐스팅
// 캐스팅이 어떤 경우 안전하고 어떤 경우 그렇지 않은가?
// http://d.pr/n/16nTT
#include <iostream>
using namespace std;

// 1. C의 캐스팅은 비 이성적인다.
// 2. 그래서 C++ 4개의 캐스팅을 새로 제공합니다.
//	- static_cast: generic type 간의 캐스팅, 연관성 있는 generic pointer 사이의 캐스팅 void* 캐스팅 (모든 형 가능), 자식<->부모 캐스팅
//	- reinterpret_cast: 메모리 재해석, 거의 성공 but 주의 필요
//	- const_cast: 객체의 상수성, 휘발성 제거, const int* -> int*
//	- dynamic_cat: 상속에서 자식클래스의 포인터를 부모클래스의 포인터로 캐스팅 하는 것은 안전하므로 그냥 되지만 (부모 is a 자식)
//				반대로 부모클래스 포인터를 자식클래스 포인터로 다운 캐스팅할 때는 dynamic_cast 필요
//				RTTI 기술 필요, 다운 캐스팅 용도

#if 0
int main()
{
	// int*에 void* 넘기지 못 한다.
//	int *p1 = malloc(sizeof(100));
	// static_cast
	int *p1 = static_cast<int*>(malloc(sizeof(100)));

	int n = 0;
	// 비 이성적 캐스팅: 메모리 양도 구조도 달라, 가능하지만 비 이성적
	double* p2 = (double*)&n;
	// static_cast: 이성적 캐스팅 확인 -> 불가능
//	double* p2 = static_cast<double*>(&n);
	// reinterpre_cast: 비 이성적 캐스팅 가능하지만 항상 주의해서 사용해야 함
	double* p3 = reinterpret_cast<double*>(&n);
	// 컴파일되지만 실행시 에러 발생
//	*p3 = 3.14;
}
#endif

int main()
{
	const int c = 10;
	// c가 const 이므로 불가
//	int* p = &c;
//	int* p = static_cast<int*>(&c);
//	int* p = reinterpret_cast<int*>(&c);
	// 상수 포인터로만 가능
	const int* p = &c;
	// const_cast를 쓰면 일반 포인터로 할당 가능
	// const_cast: 상수성 제거
	int* p1 = const_cast<int*>(&c);
	*p1 = 20;
	cout << c << endl;	// 10
	cout << *p << endl;	// 20
	cout << *p1 << endl;	// 20
	// const 변수의 값을 바꾸면 의도하지 않은 결과 발생할 수 있다!!

	// const는 "메모리"가 변경되지 않는다.
	// volatile은 "휘발성" ??
	// 보통 변수는 레지스터에 로드된 값을 쓰는데 volatile는 항상 메모리에 직접 접근하여 사용한다.
	// 그리고 volatile 변수의 동작은 최적화 하지 않고 코드에 적힌 그대로 실행하게 한다.
	volatile int c1 = 10;

	// const_cast로 휘발성 제거
	//	int* p = static_cast<int*>(&c);
	int* p2 = const_cast<int*>(&c1);
	*p2 = 20;
	cout << c1 << endl;	// 10
	cout << *p2 << endl;	// 20
}
