// 2_thiscall3.cpp
#include <iostream>
using namespace std;

// ��� �Լ��� �Լ� ������ �̾߱�

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

// 1. �Ϲ� �Լ� �����Ϳ� ��� �Լ��� �ּҸ� ���� �� ����.
// 2. ��� �Լ� �����͸� ����� ����ϴ� ���
// 3. �Ϲ� �Լ� �����Ϳ� ���� ��� �Լ��� �ּҸ� ���� �� �ִ�.

int main()
{
  void(*f3)() = &Dialog::goo;
  f3();
  
  Dialog dlg;
  void(Dialog::*f2)() = &Dialog::close;
  (dlg.*f2)();

  
  // f2();  error! ��ü�� ����.
  // void(*f1)() = &Dialog::close;
  
  
  
  void(*f)() = &foo;
  f();
}

















