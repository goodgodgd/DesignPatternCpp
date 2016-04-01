// 4_접근변경자.cpp
#include <iostream>
using namespace std;

class Base
{
  // 접근 지정자
private:   int a;
protected: int b;
public:    int c;
};

// http://d.pr/n/12tp7
// 1. 부모 클래스의 private 접근은 영향을 받지 않습니다.
// 2. protected 상속
//   1) protected -> protected
//   2) public    -> protected
// 3. private 상숙
//   1) protected -> private
//   2) public    -> private

            // : <접근 변경자> Base
class Derived : private Base
{
};

int main()
{
  // Base b;    b.c = 10;
  Derived d; d.c = 10;
}




