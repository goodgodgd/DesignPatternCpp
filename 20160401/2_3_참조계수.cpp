// 객체의 수명을 참조계수로 관리하는 경우가 많습니다.
// 객체를 공유하는데 효과적인 방법

// 객체의 참조 카운트 기능을 부모로 옮기고, 다양한 객체를 담을수 있는 템플릿 포인터 객체를 만들자.

#include <iostream>
using namespace std;

// 객체가 힙에 생성되어야 한다. new로 생성?
class RefCountedObject
{
	int mCount;
public:
	RefCountedObject() : mCount(0) { cout << "객체 생성" << endl; }
	~RefCountedObject() { cout << "객체 파괴" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// 참조계수가 0되면 자신 파괴
			delete this;
	}

};

// 근데 상속받은 객체가 
class Image : public RefCountedObject
{
public:
	void draw() { cout << "draw" << endl; }
};


// RefCountedObject*를 바로 사용하면 참조계수를 매번 관리해야 한다.
// 불편하므로 참조계수를 자동으로 관리해주는 클래스를 만들자.
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p) { ptr->addRef(); }	// 규칙 1.
	Ptr(const Ptr& p) : ptr(p.ptr)
	{
		ptr->addRef();
	}								// 규칙 2.
	~Ptr() { ptr->release(); }					// 규칙 3.

	// 진짜 포인터처럼 보여야 한다. ->, * 연산자를 재정의해야 한다.
	// => 스마트 포인터 기본
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
};

int main()
{
	Ptr<Image> p1 = new Image;	// 객체 생성
	Ptr<Image> p2 = p1;
	p1->draw();					// draw
								// 객체 파괴
}

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
