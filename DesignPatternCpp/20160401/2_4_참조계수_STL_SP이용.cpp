// 기존 객체를 참조 계수 기반을 관리하고 싶다. RefCount 기능 없는 객체
// shared_ptr<>
// shared_ptr<Image> p(new Image)
// 힙에 생성해준다. 별도의 힙공간에 참조계수 관리해줘
// 그럼 왜 RefCount 객체 쓰나? 성능때문
// RefCount 객체는 참조변수와 객체메모리가 붙어있기 때문에 성능이 더 좋다.
// 그런데 shared_ptr 도 메모리 연결할 수 있어
// shared_ptr<Image> p = make_shared<Image>();
// 이렇게 하면 스마트포인터와 객체를 하나로 묶은 코드를 생성해줘

// 스마트 포인터 - 자원의 소유권
// - shared_ptr : 참조 계수 기반 - 소유권 공유
// - unique_ptr : 복사 금지		- 혼자 소유
//				  해당 포인터만이 객체에 접근할 수 있어. 하지만 소유권 이전은 가능하다.
// unique_ptr<int> p1(new int);
// unique_ptr<int> p2 = p1;				// 컴파일 에러, 복사 금지
// unique_ptr<int> p2 = std::move(p1);	// 소유권 이전, p1 -> 0
// 이러한 개념을 이해하기 위해서는
// Effective Modern C++ - 인사이트, 류광 번역
//		Effective C++ 과 중복되는 내용 아니라 확장되기 때문에 Effective C++를 미리 읽어야 한다.

// 그러나 shared_ptr을 마구 사용하면 성능저하
// 멀티스레드에서 사용할 때 refCount를 증감하는 것을 스레드안전하게 설계되어있다. -> atomic 연산
// atomic 연산을 쓰면서 CPU가 조금씩 놀게되어 성능저하
// 따라서 raw pointer나 unique_ptr을 쓰는 것이 더 빠르다.
// 스마트 포인터: 문제가 발생했을 경우 원인을 알기 어렵다. 메모리 두번 해지라든가...
// 스마트 포인터를 쓸 때 도움되는 자료
// http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
// 어느정도 스마트 포인터에 대한 학습이 되어야만 잘 쓸수 있다.

// 주의: 순환 참조
// p1-->A, p2=->B
// p1->next==B, p2->next==A
// next가 shared_ptr 이면?

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
