
#include <iostream>
using namespace std;

#include <memory>

// 순환 참조
// => 강한 참조의 개념과 약한 참조의 개념을 이해하고 구현할 수 있어야 한다.
// 강한 참조: ref count 가 변하는 것
// 약한 참조: ref count 가 변하지 않는 것

#if 0
struct node
{
	~node() { cout << "node 파괴" << endl; }
	shared_ptr<node> next;
};

int main()
{
	shared_ptr<node> p1(new node);
	shared_ptr<node> p2(new node);

	// 이걸하면 파괴되지 않는다.
	//p1->next = p2;
	//p2->next = p1;
}
#endif

struct node
{
	~node() { cout << "node 파괴" << endl; }
	// 약한 참조
	weak_ptr<node> next;
};

// Java에서는?
// Node p = new Node();		-> 강한 참조
// WeakReference<Node> wp = new WeakReference<>(new Node());
// SoftReference -> 약한 참조
// Java에서는 기본적으로 garbage collection이 발생하거나 말거나 메모리가 계속 증가하는데
// SoftReference: garbage collection이 발생해도 늘어나다가 out of memory 전에 수거한다. 죽지 않는다.
// WeakReference: garbage collection이 발생하면 바로 수거한다.

int main()
{
	shared_ptr<node> p1(new node);
	shared_ptr<node> p2(new node);

	// 이제 파괴된다.
	p1->next = p2;
	p2->next = p1;

	shared_ptr<node> p = p1->next.lock();
	// 사용전에 소유권을 얻어야 한다.
}
