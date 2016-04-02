// 빌더
// -> 공정은 동일하지만 표현이 달라지는 객체를 만들 때
// -> 객체 생성
// -> 생성자의 인자가 많을 때

#include <iostream>
#include <string>
using namespace std;

// 방법 1. Telescoping Constructor Pattern
//		: 점층적 생성자 패턴
#if 0
class UserInfo
{
	const string id;		// 변하지 않는 필드 const
	const string address;	// 생성자의 필수 인자다, 생성자에서만 초기화 할 수 있다.
	int level;
	int gold;
	int cash;

public:
	UserInfo(string i, string a) : id(i), address(a) {}
	UserInfo(string i, string a, int l) : id(i), address(a)
	UserInfo(string i, string a, int l, int g) : id(i), address(a) {}
	UserInfo(string i, string a, int l, int g, int c) : id(i), address(a) {}
};

int main()
{
	UserInfo ui("혁두", "서울", 0, 100, 1000);
}

#endif	// 문제: 생성자 구현이 너무 귀찮다.

// 생성자 위임 기능을 써보자.
class UserInfo
{
	const string id;		// 변하지 않는 필드 const
	const string address;	// 생성자의 필수 인자다, 생성자에서만 초기화 할 수 있다.
	int level;
	int gold;
	int cash;

public:
	UserInfo(string i, string a)
		: UserInfo(i, a, 0, 0, 0) {}
	UserInfo(string i, string a, int l)
		: UserInfo(i, a, l, 0, 0) {}
	UserInfo(string i, string a, int l, int g)
		: UserInfo(i, a, l, g, 0) // C++11 Delegating Constructor
	{}
	// this(i, a, l, g, 0); - 생성자 위임

	UserInfo(string i, string a, int l, int g, int c)
		: id(i), address(a), level(l), gold(g), cash(c) {}
};

// 이 방법을 객체를 생성할 때는 설정하려는 인자 개수에 맞는 생성자를 선택해서 생성하면 된다.

int main()
{
	UserInfo ui("혁두", "서울", 0, 100, 1000);
	// 문제점
	// 1) 가독성이 좋지 않다. 어떤 인자가 어떤 멤버를 초기화하는지 알기 어렵다.
	// 2) 같은 타입의 인자에 대해서 순서를 바꿀 경우 컴파일 에러가 발생하지 않습니다.
}
