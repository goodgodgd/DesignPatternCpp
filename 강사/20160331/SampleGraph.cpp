// SampleGraph.cpp
#include "IObserver.h"

#include <iostream>
using namespace std;

class SampleGraph : public IObserver
{
public:
  virtual void onUpdate(void* p)
  {
    int* data = static_cast<int*>(p);
    cout << "******** Sample Graph *********" << endl;
    for (int i = 0; i < 5; ++i)
      cout << i << " : " << data[i] << endl;
  }
};

// 반드시 동적 모듈 안에서 객체를 생성하는 방법을 제공해주어야 합니다. - 핵심!!!
// - SampleGraph 라는 이름은 현재 DLL을 만드는 사람만 알고 있습니다.
// - 프로그램 내부에서는 절대 이름을 사용하면 안됩니다.

// 반드시 DLL 내부에서 자신이 만든 클래스의 객체를 생성해주어야 합니다.
// - 함수 하나를 약속합니다.

extern "C"
__declspec(dllexport)   // 윈도우에서 DLL 내부 심볼을 공개하는 방법.
IObserver* CreateGraph()
{
  return new SampleGraph;
}

#if 0
void foo() {}          -> foo

void foo(int) {}       -> foo@int
void foo(double) {}    -> foo@double
void foo(int, int) {}  -> foo@int@int
#endif

// 프로그램 -> visual studio 2013 -> visual studio 2013 tools -> Developer Command Prompt
// cl SampleGraph.cpp /LD

// /LD: DLL로 만들라는 옵션입니다.

// D:\plugin 폴더를 만들어서 SampleGraph.dll을 복사해 넣어 주세요.