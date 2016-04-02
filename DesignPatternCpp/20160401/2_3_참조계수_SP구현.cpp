// 객체의 수명을 참조계수로 관리하는 경우가 많습니다.
// 객체를 공유하는데 효과적인 방법

// 객체의 참조 카운트 기능을 부모로 옮기고, 다양한 객체를 담을수 있는 템플릿 포인터 객체를 만들자.

#include <iostream>
using namespace std;

// 참조 계수 카운트 기능담은 부모 클래스
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

// 본연의 기능만 구현된 자식 클래스
class Image : public RefCountedObject
{
public:
	void draw() { cout << "draw" << endl; }
};


// 참조 계수 기능이 있는 다양한 객체에 대해 참조 계수 관리 기능을 캡슐화한 클래스
// 생성, 복사, 소멸시 참조 계수 증감
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p)				{ ptr->addRef(); }	// 규칙 1. 객체를 만들면 참조 계수 증가
	Ptr(const Ptr& p) : ptr(p.ptr)	{ ptr->addRef(); }	// 규칙 2. 포인터를 복사하면 참조 계수 증가
	~Ptr()							{ ptr->release(); }	// 규칙 3. 객체 포인터 사용 후 참조 계수 감소
	
	// 진짜 포인터처럼 보여야 한다: ->, * 연산자를 재정의해야 한다.
	// - 스마트 포인터 기본
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
