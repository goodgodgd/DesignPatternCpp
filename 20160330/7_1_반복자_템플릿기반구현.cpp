
#include <iostream>
using namespace std;

template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};

// slist의 반복자를 설계해봅시다.
// - 반복자: 컨테이너의 구간을 표현하는 타입 (이면서 스마트 포인터)
// iterator는 vector나 list를 배열처럼 쓰게 해주는 경계면 역할을 해준다.

template <typename T>
class slist_iterator
{
	node<T>* current;
public:
	// 규칙2. (C++ document)
	// 모든 컨테이너 설계자는 자신의 반복자 이름을 미리 약속된 형태로 외부에 알려야 한다.
	slist_iterator(node<T>* p = 0) : current(p) {}

	// ==, != 를 제공한다.
	inline bool operator==(const slist_iterator& t)	{ return t.current == current; }
	inline bool operator!=(const slist_iterator& t)	{ return t.current != current; }

	// 값을 얻는 연산
	inline T& operator*() { return current->data; }

	// 이동하는 연산
	inline slist_iterator& operator++()
	{
		current = current->next;
		return *this;
	}
};



// 규칙1. (C++ document)
// 모든 컨테이너의 설계자는 자신의 처음과 끝 다음을 가르키는 반복자를 꺼낼 수 있는 연산을 제공해야 한다.
// begin() / end()

template <typename T>
class slist
{
	node<T>* head;
public:
	typedef slist_iterator<T> iterator;

	slist() : head(0) {}	// -> list의 맨 마지막은 '0'이된다. -> end()에서 0 리턴

	void push_front(const T& a) { head = new node<T>(a, head); }
	T& front() { return head->data; }

	// 반복자를 꺼내는 함수
	slist_iterator<T> begin() { return slist_iterator<T>(head); }	// slist_iterator 객체를 생성하고 그 객체를 리턴
	slist_iterator<T> end() { return slist_iterator<T>(0); }		// 왜 0? 생성자 참조
};

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
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

//	slist_iterator<int> p = xfind(s.begin(), s.end(), 20);
	slist<int>::iterator p = xfind(s.begin(), s.end(), 20);
	if (p != s.end())
		cout << *p << endl;
}

