// 2_thiscall4.cpp
// ��Ƽ �����带 ĸ��ȭ �غ��ô�.
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

  // 1. �Ʒ� �Լ��� static ��� �Լ� �ϼ� �ۿ� ���� ������ ��Ȯ�� �˾ƾ� �մϴ�.
  // 2. this�� �����Ƿ� ������ �Լ� ���ڷ� this�� �����ϴ� ���
  static DWORD __stdcall _threadLoop(void* user)
  {
    Thread* self = static_cast<Thread*>(user);

    self->threadLoop();   // threadLoop(self);
    return 0;
  }

  virtual bool threadLoop() { return false; }

};


// �Ʒ� Ŭ������ ���̺귯�� ����� �Դϴ�.
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
  t.run();      // �� ���� �����尡 �����Ǿ �����Լ��� threadLoop()��
                // �����ؾ� �մϴ�.

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
