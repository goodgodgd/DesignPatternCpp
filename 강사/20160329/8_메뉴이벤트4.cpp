// 8_메뉴이벤트4
#include <iostream>
using namespace std;

// 핸들러 방식의 이벤트 처리 
// => 함수 포인터
// => iPhone target-action
//    C#  delegate
//    MFC message map
//    Qt  signal-slot

// 문제점: C++에는 범용 함수 포인터라는 개념이 존재하지 않는다.


class Dialog;
class MenuItem
{
  void(Dialog::*handler)();
  Dialog* object;
public:
  void setHandler(void(Dialog::*h)(), Dialog* o)
  {
    handler = h;
    object = o;
  }

  virtual void command()
  {
    (object->*handler)();
  }
};

void foo() {}

class Dialog
{
public:
  void open()  { cout << "Dialog open" << endl;  }
  void close() { cout << "Dialog close" << endl; }
};

int main()
{
  MenuItem m1; MenuItem m2;

  Dialog dlg;
  m1.setHandler(&Dialog::open, &dlg);
  m2.setHandler(&Dialog::close, &dlg);
  
  m1.command();
  m2.command();
}
