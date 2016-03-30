// C++ 라이브러리를 이해하기 위해서는 일반화를 이애해야 합니다.
// C++ - OOP + 일반화(Generic)

#include <vector>
#include <iostream>
using namespace std;

// C의 문자열 함수
#if 0
char* xstrchr(char* s, char c)
{
	while (*s != '\0' && *s != c)
		++s;
	return *s == c ? s : NULL;
}

int main()
{
	char s[] = "abcdefg";
	char* p = strchr(s, 'c');	// 문자열 선형 탐색
	// -> 이것을 다른 타입에 대해 일반화 해보자.
	if (p != NULL)
		cout << *p << endl;
}
#endif

// 1. 검색 구간의 일반화: 부분 문자열 검색 가능하게 하자.
//		문자열은 '\0'으로 끝나게 되어있다. 부분 구간도 지정할 수 없다.
//		-> 구간 지정, 배열을 탐색할 때 포인터가 낫다.
// [first, last) - 반개 구간의 형태, 마지막 요소를 포함하고 있다. 마지막인 '\0'까지 도달하게 만든다.
#if 0
char *xstrchr(char* first, char* last, char value)
{
	while (first != last && *first != value)
		++first;

//	return first == last ? 0 : first;
	return first;	// first == last 이면 에러다는 약속
}

int main()
{
	char s[] = "abcdefg";
	char* p = xstrchr(s, s + 7, 'c');
	if (p != s + 7)
		cout << *p << endl;
}
#endif

// 2. 검색 타입의 일반화 - template 도입
#if 0
template <typename T>
T *xfind(T* first, T* last, T value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last 이면 에러다는 약속
}

int main()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int* p = xfind(x, x + 5, 3);
	if (p != x + 5)
		cout << *p << endl;
}
#endif

// 문제점 1)
// 구간의 타입과 찾는 요소의 타입이 연결되어 있다.
// int 배열 안에서 double이나 short를 찾을 수 없다.
// 	컴파일러가 암시적 타입을 결정할 때 타입이 모호해진다.

// 템플릿 타입을 하나 더 늘려준다. -> 구간 타입과 값 타입을 분리하자.
#if 0
template <typename T1, typename T2>
T1 *xfind(T1* first, T1* last, T2 value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last 이면 에러다는 약속
}

int main()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int* p = xfind(x, x + 5, 3);
	if (p != x + 5)
		cout << *p << endl;
}
#endif

// 문제점 2)
// - T* 라고 하면 진짜 포인터만 사용할 수 있다. 스마트 포인터를 사용할 수 없다.
// -> 포인터 타입 자체를 암시적 타입으로 받아버리자
template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last 이면 에러다는 약속
}

int main()
{
	int x[] = { 1, 2, 3 };
	cout << *xfind(x, x + 3, 3) << endl;

	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	cout << *xfind(v.begin(), v.end(), 30) << endl;
}

// C++에서는 list나 vector 내부에 find, sort 등을 구현하지 않고 <algorithm>에 구현해 놓았다.
// Iterator: 컨테이너 내부의 구간을 나타낸다. algorithm에서 STL 컨테이너들을 공통적으로 쓸수 있게 해주는 경계면 역할
