// 2_thiscall4.cpp
// 멀티 스레드를 캡슐화 해봅시다.
// http://d.pr/n/IpaL
#include <Windows.h>

#include <iostream>
using namespace std;

// #include "Thread.h"
class Thread
{
public:
  void run()
  {
    CreateThread(0, 0, _threadLoop, this, 0, 0);
  }

  // 1. 아래 함수가 static 멤버 함수 일수 밖에 없는 이유를 정확히 알아야 합니다.
  // 2. this가 없으므로 스레드 함수 인자로 this를 전달하는 기술
  static DWORD __stdcall _threadLoop(void* user)
  {
    Thread* self = static_cast<Thread*>(user);

    self->threadLoop();   // threadLoop(self);
    return 0;
  }

  virtual bool threadLoop() { return false; }

};


// 아래 클래스는 라이브러리 사용자 입니다.
class MyThread : public Thread
{
public:
  virtual bool threadLoop()
  {
    cout << "MyThread threadLoop()" << endl;
    return true;
  }
};

int main()
{
  MyThread t;
  t.run();      // 이 순간 스레드가 생성되어서 가상함수인 threadLoop()를
                // 수행해야 합니다.

  getchar();
}



#if 0
DWORD __stdcall foo(void* p)
{
  cout << "Thread start!!" << endl;
  return 0;
}

int main()
{
  CreateThread(0, 0, foo, "A", 0, 0);
  getchar();
}
#endif
