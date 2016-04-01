// 8_메뉴이벤트3
#include <iostream>
#include <vector>
using namespace std;

struct IMenuListener
{
  virtual void onCommand(int id) = 0;
  virtual ~IMenuListener() {}
};

class MenuItem
{
  int id;
  vector<IMenuListener*> v;
public:
  MenuItem(int i) : id(i) {}
  void addListener(IMenuListener* p)
  {
    v.push_back(p);
  }

  virtual void command()
  {
    // 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
    // "객체가 외부로 이벤트를 발생한다." 라고 표현
    // => 등록된 모든 객체에게 알려준다. -> 관찰자 패턴
    for (int i = 0; i < v.size(); ++i)
      v[i]->onCommand(id);
  }
};

class Window : public IMenuListener
{
public:
  virtual void onCommand(int id)
  { cout << "Window onCommand" << endl; }
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
  }

  void open() { cout << "Dialog open" << endl; }
  void close() { cout << "Dialog close" << endl; }
};

int main()
{
  Dialog dialog;
  Window window;

  MenuItem m1(11);
  m1.addListener(&dialog);
  m1.addListener(&window);

  m1.command();
}
