// GoF의 디자인 패턴에는 컨테이너에 적용하는 패턴이 두가지 있습니다.
// 1. 반복자: 컨테이너의 내부 구조에 상관없이 요소를 열거한다.
// 2. 방문자: 컨테이너의 내부 구조에 상관없이 요소에 연산을 수행한다.

// 컨테이너 안에 있는 모든 요소를 2배고 하고 싶다.
// 1. 루프를 수행하면서 모든 요소를 2배로 해서 다시 넣으면 된다.
// 2. 특정 작업을 자주하게 된다면 멤버 함수로 추가하는 것이 좋다.
//		그런데 사용자가 어떤 작업을 자주하는지 라이브러리 설계자는 모른다.
// 3. 방문자 패턴을 사용하자.
//	=> 모든 컨테이너에 대해서 원하는 작업을 수행할 수 있다.
// C++ 표준에는 방문자가 없고 java 스타일 구현해보자!

#include <ppl.h>	// 마이크로 소프트에서 제공하는 병렬함수
// for_each 대신 parallel_for_each를 쓰면 된다.

// 명령적 프로그래밍: 루프 돌려서 직접 구현
// 선언적 프로그래밍: query와 비슷하게 비슷한 다른 이름으로 간편하게 제공????


#include <iostream>
using namespace std;

template <typename T>
struct IVisitor
{
	virtual void visit(T& a) = 0;
	virtual ~IVisitor() {}
};

// 모든 방문 대상(컨테이너)의 인터페이스
template < typename T >
struct IAcceptor
{
	virtual void accept(IVisitor<T>* visitor) = 0;
	virtual ~IAcceptor() {}
}

// 컨테이너를 바꾸지 않고도 방문자를 통해 기능을 추가할 수 있다.
// 모든 요소를 두배로 하는 방문자
template < typename T >
struct TwiceVisitor : public IVisitor < T >
{
public:
	virtual void visit(T& a) { a *= 2; }
};

// 모든 요소를 보여주는 방문자
template < typename T >
struct ShowVisitor : public IVisitor < T >
{
public:
	virtual void visit(T& a) { cout << a << endl; }
};


template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};


template <typename T>
class slist : public IAcceptor<T>
{
	node<T>* head;
public:
	// 아래 함수만 정확하게 이해하면 됩니다.
	virtual void accept(IVisitor<T>* visitor)
	{
		node<T>* current = head;
		while (current)
		{
			visitor->visit(current->data);
			current = current->next;
		}
	}

	slist() : head(0) {}
	void push_front(const T& a) { head = new node<T>(a, head); }
	T& front() { return head->data; }
};

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	TwiceVisitor<int> tv;
	ShowVisitor<int> sv;

	s.accept(&tv);
	s.accept(&sv);

	cout << s.front() << endl;
}


