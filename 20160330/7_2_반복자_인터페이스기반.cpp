// 자바스타일의 인터페이스 반복자를 구현해보자.

#include <iostream>
using namespace std;

// 모든 반복자의 인터페이스를 먼저 설계하자.	Java		C#
// 앞선 코드의 규칙을 인터페이스화 하자
// 1. 반복자 인터페이스						- Iterator	- IEnumerator
// 2. 반복의 대상(컬렉션) 인터페이스			- Iterable	- IEnumerable

template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T> 
struct IEnumerator
{
	// java에는 operator 아닌 메소드로 구현
	virtual bool moveNext() = 0;	// ++
	virtual T& getObject() = 0;		// * (레퍼런스)
	virtual ~IEnumerator() {}
};

template <typename T>
class slist_enumerator : public IEnumerator<T>
{
	node<T>* current;
public:
	slist_enumerator(node<T>* p = 0) : current(p) {}

	virtual bool moveNext()
	{
		current = current->next;
		return current;
	}

	virtual T& getObject() { return current->data; }
};

// 컨테이너에서 반복자 꺼내기
// 1. STL: begin()/end() => 암시적 약속 (generic 다형성) 동적 바인딩 쓰기 싫어서
// 2. C# java: 인터페이스 기반 함수 약속

// 모든 컨테이너는 아래 인터페이스를 구현해야 한다.
template <typename T>
struct IEnumerable
{
	virtual IEnumerator<T>* getEnumeratorN() = 0;	// begin() 역할
	virtual ~IEnumerable() {}
};

template <typename T>
class slist : IEnumerable<T>
{
	node<T>* head;
public:
	virtual IEnumerator<T>* getEnumeratorN()	// begin() 역할
	{
		// slist_enumerator 객체를 생성하고 그 포인터를 리턴 (new 사용)
		return new slist_enumerator<T>(head);
	}
	// 일반적으로 함수 내에서 new를 해서 리턴해야 한다면, 스마트 포인터를 사용하는 경우가 많다.
	// Tizen: UniquePtr<>

	// free -> strdup
	// char s[] = "hell";
	// char* p = malloc(strlen(s) + 1);
	// strcpy(p, s);

	// char* p = strdup(s);	// 같은 코드인데 malloc이 안보이니까 free를 안해서 누수가 많이 생겼다.

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

	IEnumerator<int>* p = s.getEnumeratorN();
	do {
		cout << p->getObject() << endl;
	} while (p->moveNext());

	// 반드시 delete를 수행해야 합니다.
	delete p;
}
