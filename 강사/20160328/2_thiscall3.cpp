// 2_thiscall3.cpp
#include <iostream>
using namespace std;

// 멤버 함수와 함수 포인터 이야기

class Dialog
{
public:
  void close() // void close(Dialog* this)
  { cout << "Dialog close" << endl; }

  static void goo()  // void goo()
  { cout << "goo" << endl; }

};

// http://d.pr/n/7Lpj
void foo() { cout << "foo" << endl; }

// 1. 일반 함수 포인터에 멤버 함수의 주소를 담을 수 없다.
// 2. 멤버 함수 포인터를 만들고 사용하는 방법
// 3. 일반 함수 포인터에 정적 멤버 함수의 주소를 담을 수 있다.

int main()
{
  void(*f3)() = &Dialog::goo;
  f3();
  
  Dialog dlg;
  void(Dialog::*f2)() = &Dialog::close;
  (dlg.*f2)();

  
  // f2();  error! 객체가 없다.
  // void(*f1)() = &Dialog::close;
  
  
  
  void(*f)() = &foo;
  f();
}

















