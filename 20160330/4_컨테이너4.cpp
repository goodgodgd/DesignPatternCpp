// 컨테이너를 설계하는 기술
// 방법 3. Thin Template

// void* 를 사용하면 일반 데이터 뿐만 아니라 객체 데이터 모두 담을 수 있다.
// 근데 void는 항상 캐스팅을 해줘야 한다 -> 캐스팅 자동화 해주는 클래스 만들어주자.

#include <iostream>
using namespace std;

struct node
{
	(void*) data;
	node* next;
	node(void* a, node* n) : data(a), next(n) {}
};

// 모든 구현은 이곳에서 void* 기반으로 구현
class slistImpl
{
	node* head;
public:
	slistImpl() : head(0) {}

	void push_front(void* a) { head = new node(a, head); }
	void* front() { return head->data; }
};

// slistImpl을 직접 사용하면 캐스팅 때문에 불편하다.
// 사용자가 편리하게 사용할 수 있도록 구현을 물려 받는 자식 클래스를 템플릿으로 제공하자.
// 구현은 상속 받고 인터페이스는 구현한다 -> private 상속
template <typename T>
class slist : private slistImpl
{
public:
	// 이것을 inline화 하면 코드 메모리 부하 줄임
	// 이 함수는 기계어에 존재하지 않음.
	inline void push_front(const T& a)
	{
		// const T& -> const* T
		// node(void* a, node* n) 에서는 const가 아니므로 const를 없애주기 위해 const_cast 쓴다.
		slistImpl::push_front(const_cast<T*>(&a));
	}
	inline T& front()
	{
		// void* -> T* -> T&
		return *static_cast<T*>(slistImpl::front());
	}
};


// const cast를 node로 옮겨도 되네?
#if 0
struct node
{
	(void*) data;
	node* next;
	// const cast를 이쪽으로 옮겨도 되네?
	node(const void* a, node* n) : data(const_cast<void*>(a)), next(n) {}
};

// 모든 구현은 이곳에서 void* 기반으로 구현
class slistImpl
{
	node* head;
public:
	slistImpl() : head(0) {}

	void push_front(const void* a) { head = new node(a, head); }
	void* front() { return head->data; }
};

template <typename T>
class slist : private slistImpl
{
public:
	inline void push_front(const T& a)
	{
		// const T& -> const* T
		slistImpl::push_front(&a);
	}
	inline T& front()
	{
		// void* -> T* -> T&
		return *static_cast<T*>(slistImpl::front());
	}
};
#endif

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
