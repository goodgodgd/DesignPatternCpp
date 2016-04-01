// 5_스마트포인터
#include <iostream>
using namespace std;

class Car
{
public:
  Car()  { cout << "자원 생성" << endl; }
  ~Car() { cout << "자원 해지" << endl; }

  void go() { cout << "Car go" << endl; }
};

// 스마트 포인터
// 개념: 임의의 객체가 다른 객체의 포인터의 역활을 수행하는 것.
// 구현원리: -> 와 * 연산자를 재정의해서 포인터처럼 보이게 만든다.
// 장점: 진짜 포인터가 아니라 객체이다.
//       생성/복사/대입/소멸의 모든 과정을 제어할 수 있다.
// 활용: 대표적 활용은 소멸자에서의 자동 삭제 기능이다.

// C++ 표준에서도 이미 다양한 정책을 가지고 있는 스마트 포인터를 제공하고 있습니다.
//  C++98/03 - auto_ptr
//  C++11/14 - unique_ptr, shared_ptr, weak_ptr, auto_ptr(deprecated)

template <typename T>
class Ptr
{
  T* obj;
public:
  inline T* operator->() { return obj; }
  inline T& operator*()  { return *obj; }

  inline Ptr(T* p = 0) : obj(p) {}
  inline ~Ptr()
  {
    delete obj;
  }
};

int main()
{
  Ptr<Car> p = new Car;

  p->go();
  (*p).go();
}



#if 0
int main()
{
  Car* p = new Car;

  p->go();
  (*p).go();

  delete p;
}
#endif








