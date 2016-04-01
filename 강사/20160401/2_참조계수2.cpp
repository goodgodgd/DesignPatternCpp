// 2_참조계수 - 매우 중요합니다.

#include <iostream>
using namespace std;

// 객체의 수명을 참조 계수로 관리하는 경우가 많습니다.
class Image
{
  int mCount;
public:
  Image() : mCount(0) {}
  ~Image() { cout << "Image 파괴" << endl; }

  void addRef() { ++mCount; }
  void release()
  {
    if (--mCount == 0)
      delete this;
  }
};

// Image*를 바로 사용하면 참조 계수를 매번 관리해야 한다.
// 불편하므로 참조 계수를 자동으로 관리해주는 클래스를 만들자.
class ImageProxy
{
  Image* ptr;
public:
  ImageProxy(Image* p) : ptr(p) { ptr->addRef(); } // 규칙 1.
  ImageProxy(const ImageProxy& p) : ptr(p.ptr)
  {  ptr->addRef();  }   // 규칙 2.

  ~ImageProxy() { ptr->release(); }   // 규칙 3.
};

int main()
{
  ImageProxy p1 = new Image;
  ImageProxy p2 = p1;
}


#if 0
int main()
{
  Image* p1 = new Image;  // 규칙 1. 객체를 만들면 참조 계수 증가
  p1->addRef();

  Image* p2 = p1;     // 규칙 2. 포인터를 복사하면 참조 계수 증가
  p2->addRef();

  p1->release();      // 규칙 3. 객체 포인터 사용 후 참조 계수 감소
  p2->release();
}
#endif