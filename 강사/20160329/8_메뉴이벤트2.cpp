// 8_메뉴이벤트2
#include <iostream>
using namespace std;
// 1. 인터페이스 기반의 리스너 개념: Java, Android

// 메뉴를 처리하고 싶은 모든 클래스는 아래 인터페이스를 구현해야 한다.
struct IMenuListener
{
  virtual void onCommand(int id) = 0;
  virtual ~IMenuListener() {}
};

class MenuItem
{
  int id;
  IMenuListener* pListener;
public:
  MenuItem(int i) : id(i), pListener(0) {}
  void setListener(IMenuListener* p) { pListener = p; }
  //   addListener

  virtual void command()
  {
    // 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
    // "객체가 외부로 이벤트를 발생한다." 라고 표현
    if (pListener)
      pListener->onCommand(id);
  }
};

class Dialog : public IMenuListener
{
public:
  virtual void onCommand(int id)
  {
    // 어떤 객체로부터 이벤트가 발생했는지 여부를 반드시 분기하는 코드가
    // 필요하다.
    switch (id)
    {
    case 11: open(); break;
    case 12: close(); break;
    }

    close();
  }

  void open() { cout << "Dialog open" << endl; }
  void close() { cout << "Dialog close" << endl; }
};

int main()
{
  Dialog dialog;

  MenuItem m1(11); MenuItem m2(12);
  m1.setListener(&dialog);
  m2.setListener(&dialog);

  m1.command();
}
