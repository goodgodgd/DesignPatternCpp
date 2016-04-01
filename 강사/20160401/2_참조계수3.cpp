// 2_참조계수3 - 매우 중요합니다.

#include <iostream>
using namespace std;

// 객체의 수명을 참조 계수로 관리하는 경우가 많습니다.
class RefCountedObject
{
  int mCount;
public:
  RefCountedObject() : mCount(0) {}
  virtual ~RefCountedObject() { cout << "객체 파괴" << endl; }

  void addRef() { ++mCount; }
  void release()
  {
    if (--mCount == 0)
      delete this;
  }
};

template <typename T>
class Ptr 
{
  T* ptr;
public:
  Ptr(T* p) : ptr(p) { ptr->addRef(); } 
  Ptr(const Ptr& p) : ptr(p.ptr)
  {
    ptr->addRef();
  }  

  ~Ptr() { ptr->release(); }  

  // 진짜 포인터처럼 보여야 한다. ->, * 연산자를 재정의해야 한다.
  // => 스마트 포인터 기본
  T* operator->() { return ptr;  }
  T& operator*()  { return *ptr; }
};

//----------------

class Image : public RefCountedObject
{
public:
  void draw() { cout << "Image draw" << endl; }

};


// 기존의 객체를 참조 계수 기반으로 관리하고 싶다.
// shared_ptr<>
// shared_ptr<Image> p(new Image);
// shared_ptr<Image> p = make_shared<Image>();

// 스마트 포인터 - 자원의 소유권
// - shared_ptr : 참조 계수 기반           : 소유권 공유
// - unique_ptr : 복사 금지, 소유권 이전   : 혼자 소유

// Effective Modern C++ - 인사이트, 류광
// unique_ptr<int> p1(new int);
// unique_ptr<int> p2 = p1;             // 에러. 복사 금지
// unique_ptr<int> p2 = std::move(p1);  // 소유권 이전, p1 -> 0

// http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/ 참고

int main()
{
  Ptr<Image> p1 = new Image;
  Ptr<Image> p2 = p1;

  p1->draw();
  p2->draw();

}