// 2_CRTP
#include <iostream>
using namespace std;

class MyWindow;


//       Mixin template
// CRTP: Curiosly Recurring Template Pattern - C++ idioms
// : 부모 클래스가 템플릿 인데 자식에서 템플릿의 인자로 자신의 타입을 전달하는 기술

// 여러가지 활용이 가능한데, 아래 코드는 비가상함수를 가상함수처럼 
// 동작하게 만드는 기법.

// MS 라이브러리 중 WTL, ATL가 아래와 같이 설계가 되어 있습니다.
template <typename T>
class Window
{
public:
  void msgLoop()
  {
    // this : Window* 
    (static_cast<T*>(this))->onClick();

  }

  void onClick() {}
};

class MyWindow : public Window<MyWindow>
{
public:
  void onClick() { cout << "My Window on Click" << endl; }
};

int main()
{
  MyWindow w;
  w.msgLoop();
}








