// 4_책임의전가
#include "ioacademy.h"
using namespace ioacademy;

#include <map>
#include <vector>
#include <iostream>
using namespace std;

// 디자인 패턴에서는 이벤트 처리에 관련된 패턴이 2가지 있습니다.
// 1. 관찰자     : 이벤트가 발생시 등록된 객체에게 이벤트를 전파
// 2. 책임의 전가: 이벤트 발생시 다음 객체에게 전달
class Window
{
  static map<int, Window*> this_map;

  int handle;                // C 함수를 통해 윈도우를 실제로 조작하기 위해서는
                             // 반드시 저장해야 한다.

  Window* parent;            // 부모 윈도우는 1개이다.
  vector<Window*> children;  // 자식은 여러개이다.
public:
  Window() : parent(0) {}

  void addChild(Window* p)
  {
    p->parent = this;
    children.push_back(p);

    // C 함수로 자식 윈도우를 붙인다.
    IoAddChild(this->handle, p->handle);
  }

  void create()
  {
    handle = IoMakeWindow(foo);
    this_map[handle] = this;
  }

  virtual bool onLButtonDown() { return false; }
  virtual void onKeyDown() {}

  // 아래 함수가 책임의 전가(Chain of Responsibility) 패턴의 핵심입니다.
  void fireLButtonDown()
  {
    // 1. 먼저 자신이 처리를 시도합니다.
    if (onLButtonDown() == true)
      return;

    // 2. 자신이 처리하지 않은 경우 부모에게 전달
    if (parent != 0)
      parent->fireLButtonDown();
  }

  static int foo(int handle, int msg, int param1, int param2)
  {
    Window* self = this_map[handle];

    switch (msg)
    {
    case WM_LBUTTONDOWN:
      self->fireLButtonDown();
      // self->onLButtonDown();
      break;

    case WM_KEYDOWN:
      self->onKeyDown();
      break;
    }

    return 0;
  }


};

map<int, Window*> Window::this_map;

class MyWindow : public Window
{
public:
  virtual bool onLButtonDown() {
    cout << "LButton" << endl;
    return false;
  }
};

class ImageView : public Window
{
public:
  virtual bool onLButtonDown() {
    cout << "Image" << endl;
    return false;
  }
};

int main()
{
  MyWindow w;
  w.create();

  ImageView imageView;
  imageView.create();

  w.addChild(&imageView);

  IoProcessMessage();
}
