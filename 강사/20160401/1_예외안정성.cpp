// 1_예외 안전성
#include <iostream>
using namespace std;

// 1. 생성자에서 실패를 알리는 방법은 예외 밖에 없다.
// 2. 생성자에서 예외가 발생 하면 소멸자가 호출되지 않는다.

class Test
{
  int* p1;
  int* p2;
public:
  Test()
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
  }
  catch (...) 
  {

  }

}

