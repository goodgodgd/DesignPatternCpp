// 6_가상함수의원리3.cpp
#include <iostream>
using namespace std;

class A
{
  int a;
public:
  virtual void foo() { cout << "A foo" << endl; }
};

// http://d.pr/n/19UjG
class B
{
  int b;
public:
  virtual void goo() { cout << "B goo" << endl; }
};

int main()
{
  A aaa;
  B* p = reinterpret_cast<B*>(&aaa);
  p->goo();
}