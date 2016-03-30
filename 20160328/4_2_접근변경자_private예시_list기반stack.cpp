// http://d.pr/n/0aYa

#include <iostream>
using namespace std;

// list가 이미 있습니다.
#include <list>

// 그런데 클라이언트가 stack을 요구합니다.
// 1. stack을 다시 만들어주자. - 힘들어
// 2. list를 한쪽으로 사용하면 stack이다. list를 재사용하자. - Better, 이미 검증되었고 효율적

// Adapter Pattern: 기존 클래스의 인터페이스(함수 이름)을 변경해서
//					사용자가 요구하는 새로운 클래스처럼 보이게 하는 패턴

// 라이브러리는 쉽게 사용할 수 있도록 만들어야 하고,
// 잘못 사용하기 어렵게 만들어야 한다.
// 아래 stack의 문제는 stack 내부의 push, pop, top 뿐만 아니라
// list의 모든 기능도 들어간다.
// private 상속: 부모 클래스로부터 구현은 물려 받지만, (자식이 내부적으로 사용하지만)
//				인터페이스는 물려 받지 않겠다. (부모 함수를 외부로 노출하지 않겠다.)

// list를 기능을 이용해서 stack 구현
template <typename T>
//class stack : public list < T >
class stack : private list < T >	
{
public:
	// private으로 받아도 using을 쓰면 접근 가능
	using list<T>::push_back;

	void push(const T& a)	{ push_back(a); }	// 부모의 함수 재사용
	void pop()				{ pop_back(); }
	T& top()				{ return back(); }
};

int main()
{
	stack<int> s;
	s.push(10);
	s.push(20);
	// 부모에게서 받고 싶지 않은 것도 받게 됨.
//	s.push_back(300);
	// top = 20;
	cout << s.top() << endl;
}
