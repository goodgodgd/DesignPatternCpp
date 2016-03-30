// 컨테이너를 설계하는 기술
// 방법 2. template 기반의 컨테이너
//		- java, C#, ObjC: Generic

#include <iostream>
using namespace std;

// 인자를 전달			표준 타입				객체 타입
// call by value		void foo(int n)			void foo(AAA n)	- 복사 발생, 성능 저하
// call by reference	void foo(int& n)		void foo(AAA& n)

// T - 표준 타입 또는 객체 타입도 될 수 있다.
// 모든 라이브러리에서 객체의 크기가 작다고 명확하지 않을 때는 객체를 전달할 때 const T& 으로 보낸다.

// template 컨테이너
// 장점: 타입 안정성이 뛰어나고 표준 타입 뿐만 아니라 객체도 저장 가능하다.
//		꺼낼 때 캐스팅이 필요없다.
// 단점: template 이므로 여러가지 타입에 사용하면 list의 기계어 코드가 많아진다. 코드 메모리 오버헤드가 생긴다.
//		데스크탑 환경은 코드 메모리가 별로 상관없지만 임베디드 환경에서는 문제될 수도

// object도 template도 장단점 있어 -> 완충된 형태??

template <typename T>
struct node
{
	T data;
	node* next;
	// 복사 부담 없애고 값 변경 위험 없애기 위해 const reference
	node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist
{
	node<T>* head;
public:
	slist() : head(0) {}

	// 노드이 생성자를 잘 활용한 코드입니다.
	// 생성자 통해 노드 생성 로직을 캡슐화
	void push_front(const T& a) { head = new node<T>(a, head); }

	// T pop_front();	// list에서 빼기 때문에 실제 값 복사
	// T& front();		// 값을 빼지 않고 전달하기 때문에 레퍼런스로 준다.
	// 예외 안정성
	// STL: 강력보장 제공, 예외 발생하면 이전 상태로 복구해준다.
	T& front() { return head->data; }
};

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
