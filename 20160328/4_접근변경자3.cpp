// ������ �̿��� �θ�Ŭ������ �������̽� ���������� ����
// http://d.pr/n/1lgo9

#include <list>
#include <iostream>
using namespace std;

// S/W�� ������ "���"�� "����"�� �ִ�.
// ����� ��� �������̽��� �ܺη� �����ϱ� ������ ������ ���� ���� ����.
// ����ڰ� �߸� ���� ��ư� �ȴ�.
// ���Կ����� �����ϰ��� �ϴ� Ŭ������ ���� �����ϴ�.

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
// stack�� include�� �ᵵ �Ȱ��� �۵�
//#include <stack>

// stack adpater��� �θ��ϴ�.
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
