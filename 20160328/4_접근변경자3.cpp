// 포함을 이용해 부모클래스의 인터페이스 선택적으로 수용
// http://d.pr/n/1lgo9

#include <list>
#include <iostream>
using namespace std;

// S/W의 재사용은 "상속"과 "포함"이 있다.
// 상속은 모든 인터페이스를 외부로 노출하기 때문에 포함이 좋을 때가 많다.
// 사용자가 잘못 쓰기 어렵게 된다.
// 포함에서는 포함하고자 하는 클래스도 지정 가능하다.

#if 0
template <typename T>
class stack
{
	list<T> st;
public:
	void push(const T& a)	{ st.push_back(a); }
	T pop()					{ st.pop_back(); }
	T top()					{ return st.back(); }
};

int main()
{
	stack<int> s;
	s.push(10);
	s.push(20);

	cout << s.top() << endl;
}
#endif

#include <vector>
#include <deque>
// stack을 include해 써도 똑같이 작동
//#include <stack>

// stack adpater라고 부릅니다.
template < typename T, typename C = deque<T> >
class stack
{
	C st;
public:
	void push(const T& a)	{ st.push_back(a); }
	T pop()					{ st.pop_back(); }
	T top()					{ return st.back(); }
};

int main()
{
	stack<int> s;
	stack<int, list<int>> s1;
	s.push(10);
	s1.push(20);

	cout << s.top() << endl;
}
