// 객체의 생성을 N개로 제한하는 기술

#include <iostream>
using namespace std;

// 기본적인 구현
#if 0
class Mouse
{
	static int n;
public:
	Mouse()
	{
		if (++n > 5)
			throw 1;
	}
};

int Mouse::n = 0;

int main()
{
	try {
		Mouse m[6];
	}
	catch (...) {
		cout << "객체 생성 실패" << endl;
	}
}
#endif


// N 개만 만들수 있는 객체 타입을 만들기

#if 0
// 템플릿은 뭘 넣어도 된다.
template <int N>
class LimitMaxObject
{
	static int n;
public:
	LimitMaxObject()
	{
		if (++n > 5)
			throw 1;
	}
};

template <int N>	// 아래 줄에서 N을 모르기 때문에 템플릿을 한번 더 쓴다.
int LimitMaxObject<N>::n = 0;

// 5개만 만들수 있는 객체 타입을 만들겠다.
class Mouse : public LimitMaxObject < 5 >
{
};

int main()
{
	try {
		Mouse m[6];
	}
	catch (...) {
		cout << "객체 생성 실패" << endl;
	}
}
#endif

// 위의 문제점: 다른 타입의 객체를 만들었는데 모든 타입에서 정적변수 n이 공유되어 
// LimitMaxObject을 상속받는 모든 클래스 객체의 합이 n으로 제한된다.
// template 인자를 추가해 타입을 바꿔줘야 한다.
// 아래의 예제는 CRTP를 이용해서 서로 다른 정적변수를 사용하는 기술입니다.

// 정적변수를 따로 쓰기 위해 템플릿을 이용한 타입의 분화
template <typename T, int N>
class LimitMaxObject
{
	static int n;
public:
	LimitMaxObject()
	{
		if (++n > 5)
			throw 1;
	}
};

template <typename T, int N>	// 아래 줄에서 T, N을 모르기 때문에 템플릿을 한번 더 쓴다.
int LimitMaxObject<T, N>::n = 0;

class Mouse : public LimitMaxObject < Mouse, 5 >
{
};

class Keyboard : public LimitMaxObject < Keyboard, 5 >
{
};

int main()
{
	// 3+3 총 6개지만 실패하지 않는다.
	try {
		Mouse m[3];
		Keyboard k[3];
	}
	catch (...) {
		cout << "객체 생성 실패" << endl;
	}
}

