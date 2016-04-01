#include <iostream>
using namespace std;

// http://d.pr/n/10pCB
// 디폴트 인자: 컴파일 시간에 결정된다.
// 가상 함수: 실행 시간에 결정된다.

// 1. 가상함수에서는 되도록이면 디폴트 인자를 사용하지 말자.
// 2. 사용했다면 재정의할 때 절대 변경하지 말자.
class A
{
public:
  virtual void foo(int a = 10) 
  { cout << "A: " << a << endl; }
};

class B : public A   // 이제 상속입니다.
{
public:
  virtual void foo(int a = 20)
  { cout << "B: " << a << endl; }
};
// http://d.pr/n/1kmqW
int main()
{
  A* p = new B;
  p->foo();       // 실행 결과 예측해보세요.
}