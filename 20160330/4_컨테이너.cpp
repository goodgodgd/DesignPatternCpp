// 컨테이너를 설계하는 기술
// - 단일 연결 리스트 기반의 컨테이너

// 다양한 타입을 담기 위해서는 template을 쓸수도 있고 object pointer를 쓸 수도 있다.(같은 부모 상속)

#include <iostream>
using namespace std;

struct node
{
	int data;
	node* next;
	// 내부생성자를 통해 기능 응집
	node(int a, node* n) : data(a), next(n) {}
};

class slist
{
	node* head;
public:
	slist() : head(0) {}

	// 노드이 생성자를 잘 활용한 코드입니다.
	// 생성자 통해 노드 생성 로직을 캡슐화
	void push_front(int a) { head = new node(a, head); }
	int front() { return head->data; }
};

int main()
{
	slist s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
