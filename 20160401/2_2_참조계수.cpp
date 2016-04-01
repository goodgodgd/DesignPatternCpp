// 객체의 수명을 참조계수로 관리하는 경우가 많습니다.
// 객체를 공유하는데 효과적인 방법

#include <iostream>
using namespace std;

// 객체가 힙에 생성되어야 한다. new로 생성?
class Image
{
	int mCount;
public:
	Image() : mCount(0) {}
	~Image() { cout << "이미지 파괴" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// 참조계수가 0되면 자신 파괴
			delete this;
	}
};


// Image*를 바로 사용하면 참조계수를 매번 관리해야 한다.
// 불편하므로 참조계수를 자동으로 관리해주는 클래스를 만들자.
class ImageProxy
{
	Image* ptr;
public:
	ImageProxy(Image* p) : ptr(p) { ptr->addRef(); }	// 규칙 1.
	ImageProxy(const ImageProxy& p) : ptr(p.ptr)
	{	ptr->addRef();	}								// 규칙 2.
	~ImageProxy() { ptr->release(); }					// 규칙 3.
};

int main()
{
	ImageProxy p1 = new Image;
	ImageProxy p2 = p1;
}
