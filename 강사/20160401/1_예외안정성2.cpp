// 1_예외 안전성
#include <iostream>
using namespace std;

// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생 하면 소멸자가 호출되지 않는다.

// 방법 1. 생성자에서 자원을 할당하지 말고 자원 할당 전용 함수를 제공하자.
//         Two Phase Constructor - 2단 생성자 호출

// 문제점: 객체의 상태가 불완전한 상태가 될 수 있다.
class Test
{
  int* p1;
  int* p2;
public:
  // 생성자에서는 절대 예외 가능성이 있는 자원 할당을 하지 말자.
  Test() : p1(0), p2(0) {}

  void Construct()
  {
    p1 = new int;
    throw std::bad_alloc();
    p2 = new int;   // 이 순간 메모리가 부족했습니다. 어떤 문제가 있을까요?
                    // 메모리가 부족하면 bad_alloc 이라는 예외가 발생합니다.
  }

  ~Test()
  {
    cout << "소멸자 호출" << endl;
    delete p1;
    delete p2;
  }
};

int main()
{
  try
  {
    Test t;
    t.Construct();
  }
  catch (...)
  {

  }

}

