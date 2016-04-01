// 1_예외 안전성
#include <iostream>
using namespace std;

// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생 하면 소멸자가 호출되지 않는다.

// 허브 셔터 - 예외 안전성
// - Exceptional C++
// - More Exception C++
// - Exceptional C++ Style

// 예외 안전성(Exception safety)
// 1. 완전 보장: 예외가 없다.
// 2. 강력 보장: 예외가 발생해도 잡을 경우, 객체 상태는 예외 발생전으로 복구된다. 
//             => STL

// 3. 기본 보장: 예외가 발생해도 자원 누수는 없다. 단 객체 상태는 알 수 없기 때문에
//               사용이 불가능하다.


#include <memory>  // unique_ptr

class Image
{
public:
  Image() { cout << "Image 생성" << endl; }
  ~Image() { cout << "Image 파괴" << endl; }
};

class Test
{
  unique_ptr<Image> p1;
  unique_ptr<Image> p2;
public:
  // 멤버 변수의 타입이 객체 타입이라면, 생성자에서 예외가 발생하였을 경우
  // 멤버 변수의 소멸자의 호출을 표준에서는 보장하고 있다.
  Test() : p1(new Image), p2(new Image)
  {
    throw std::bad_alloc();
    // 이 순간 메모리가 부족했습니다. 어떤 문제가 있을까요?
    // 메모리가 부족하면 bad_alloc 이라는 예외가 발생합니다.
  }

  ~Test()
  {
  }
};

int main()
{
  try
  {
    Test t;
  }
  catch (...)
  {

  }

}

