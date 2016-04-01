// 1_메세지맵2
// : 가상 함수 테이블의 오버헤드를 줄이기 위해 사용자가 직접 테이블을 생성하도록
//   만드는 기술입니다.

// -> 복잡한 코드를 매크로로 제공합니다.
#include "ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

class Window;
struct AFX_MSG
{
  int message;                // 메세지 번호
  void(Window::*handler)();   // 처리할 함수의 주소
};

class Window
{
  static map<int, Window*> this_map;
public:

  // 이제 모든 자식 클래스는 자신이 처리하고자 하는 이벤트와
  // 이벤트 핸들러를 담은 배열을 리턴해야 한다.
  virtual AFX_MSG* GetMessageMap() { return 0; }

  void create()
  {
    int handle = IoMakeWindow(foo);
    this_map[handle] = this;
  }

  // 이번 예제의 핵심은 아래 함수입니다.
  static int foo(int handle, int msg, int param1, int param2)
  {
    Window* self = this_map[handle];
    if (self == 0) return 0;

    // 1. 배열을 얻어온다.
    AFX_MSG* msgArray = self->GetMessageMap();
    if (msgArray == 0)  // 처리할 메세지가 없는 경우
      return 0;

    // 2. 배열에 현재 메세지가 있는지 여부를 확인하고
    //    등록된 핸들러를 호출한다.
    for (;msgArray->message != 0; msgArray++)
    {
      if (msgArray->message == msg)
      {
        void (Window::*f)() = msgArray->handler;
        (self->*f)();
      }
    }

    return 0;
  }


};
map<int, Window*> Window::this_map;

//-------------------------------------------
// GetMessageMap()을 생성하는 매크로 입니다.

#define DECLARE_MESSAGE_MAP()                   \
  virtual AFX_MSG* GetMessageMap();

#define BEGIN_MESSEAGE_MAP(classname)           \
  AFX_MSG* classname::GetMessageMap()           \
  {                                             \
    typedef void(Window::*HANDLER)();           \
    static AFX_MSG msgMap[] = {

#define ADD_MAP(message, handler)               \
  { message, static_cast<HANDLER>(handler) },

#define END_MESSAGE_MAP()                       \
      { 0, 0 }                                  \
  };                                            \
  return msgMap;                                \
}

// .h
class MyWindow : public Window
{
public:
  void foo() { cout << "key down" << endl; }

  void onLButtonDown() {
    cout << "LButton" << endl;
  }

  DECLARE_MESSAGE_MAP()
};

// .cpp
BEGIN_MESSEAGE_MAP(MyWindow)
  ADD_MAP(WM_LBUTTONDOWN, &MyWindow::onLButtonDown)
  ADD_MAP(WM_KEYDOWN, &MyWindow::foo)
END_MESSAGE_MAP()

int main()
{
  MyWindow w;
  w.create();       // 이 순간 윈도우가 만들어져야 합니다.
                    // 왼쪽 버튼을 누르면 "LBUTTON" 이라고 출력되어야 합니다.
  IoProcessMessage();
}