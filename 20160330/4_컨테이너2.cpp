// 컨테이너를 설계하는 기술
// 방법 1. object* 기반의 컨테이너 (최상위 부모클래스
//		java, C#: Object
//		Objective C: NSObject
//		MFC: CObject
//		Qt: QObject

#include <iostream>
using namespace std;

class object{
public:
	virtual ~object() {}
};

// 라이브러리 내의 모든 클래스는 object의 자식이어야 한다.
class Dialog : public object {};
class Point : public object {};
class Rect : public object {};

struct node
{
	// C++의 레퍼런스도 있지만 C++에서는 레퍼런스가 변경 불가다.
	// 포인터 쓰자.
	object* data;
	node* next;
	// 내부생성자를 통해 기능 응집
	node(object* a, node* n) : data(a), next(n) {}
};

class slist
{
	node* head;
public:
	slist() : head(0) {}

	// 노드이 생성자를 잘 활용한 코드입니다.
	// 생성자 통해 노드 생성 로직을 캡슐화
	void push_front(object* a) { head = new node(a, head); }
	object* front() { return head->data; }
};
/*
class Interger : public object
{
	node* head;
public:
	slist() : head(0) {}

	// 노드이 생성자를 잘 활용한 코드입니다.
	// 생성자 통해 노드 생성 로직을 캡슐화
	void push_front(object* a) { head = new node(a, head); }
	object* front() { return head->data; }
};
*/

// object 기반 컨테이너의 장점? 단점?
// 단점:
//	1. 타입 안정성이 떨어진다. 실수로 다른 타입을 넣어도 컴파일 시간에 에러가 발생하지 않는다.
//	2. 값을 꺼낼 때 항상 해당 타입으로 캐스팅해야 한다.
//	3. 객체가 아닌 표준 타입(primitive type)은 저장할 수 없다.
//		s.push_front(3);  // error
//		wrapper class가 필요하다 - 표준 타입의 레퍼런스 타입
//		int - integer
//		double - Double
//		java는 autoboxing, autounboxing이라는 기능으로 해결

// 장점:
// template을 사용하게 되면, 코드 메모리 오버 헤드가 없다.
// 하나의 구현으로 모든 타입 다룰수 있다.

// 장점: 여러가지 타입을 넣고 꺼낼수 있다.
// 단점: 꺼낼때 object* 형식으로 꺼내야 한다. -> 다운 캐스팅해야 한다.

int main()
{
	slist s;
	s.push_front(new Point);
	s.push_front(new Dialog);
	s.push_front(new Rect);		// 장점 아니고 실수!!

//	s.push_front(3);		// 불가
//	Point* p = s.front();		// error


	Point* p = dynamic_cast<Point*>(s.front());	// 성능저하, 그러나 잘못된 캐스팅을 막아줘
//	Point* p =  static_cast<Point*>(s.front());	// static 도 가능하지만 불안정
}
