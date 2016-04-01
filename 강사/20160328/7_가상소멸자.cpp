// 7_가상소멸자

// Inside C++ Object - 스탠리 립만

#include <iostream>
using namespace std;
// http://d.pr/n/1lDeC
// 1. 부모 클래스의 소멸자가 가상 함수이면, 모든 자식의 소멸자도 가상함수이다.
// 2. 모든 부모 클래스의 소멸자는 반드시 가상 함수이어야 한다.
class Base
{
public:
  virtual ~Base() {}
};

class Derived : public Base
{
public:
  Derived()  { cout << "자원 할당" << endl; }
  ~Derived() { cout << "자원 해지" << endl; }
};

int main()
{
  Base* p = new Derived;
  delete p;

  // Derived d;
}