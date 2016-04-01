// 4_책임의전가
#include "ioacademy.h"
using namespace ioacademy;

// 책임의 전가 패턴
// - 이벤트 발생시 처리되지 않을 경우 다음 객체에게 전달한다.
// - 처리할 수 있을 때까지 고리에 따라 이벤트를 전달한다.

// 사용 
// 1) 맥킨토시 계열 - 코코아, 코코아 터치: 리스폰더 체인
//  : View -> ViewController -> AppDelegate

// 2) MFC에서 메뉴 메세지 - 책임의 고리
//  : View -> Document -> Frame -> App

#include <map>
#include <vector>
#include <iostream>
using namespace std;

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

  virtual void onLButtonDown() {}
  virtual void onKeyDown() {}

  static int foo(int handle, int msg, int param1, int param2)
  {
    Window* self = this_map[handle];

    switch (msg)
    {
    case WM_LBUTTONDOWN:
      self->onLButtonDown();
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
  virtual void onLButtonDown() {
    cout << "LButton" << endl;
  }
};

class ImageView : public Window
{
public:
  virtual void onLButtonDown() {
    cout << "Image" << endl;
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




#if 0
// http://d.pr/n/1j6Hs
int foo(int handle, int msg, int param1, int param2)
{
  switch (msg)
  {
  case WM_LBUTTONDOWN:
    cout << "left button down" << endl;
    break;

  case WM_KEYDOWN:
    cout << "key down" << endl;
    break;
  }

  return 0;
}

int main()
{
  int h1 = IoMakeWindow(foo);

  IoProcessMessage();
}
#endif






