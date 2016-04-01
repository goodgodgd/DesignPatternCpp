// CalcProxy.cpp
#include "ICalc.h"

#include <iostream>
using namespace std;


class Calc : public ICalc
{
  int handle;
public:
  Calc() { handle = IoFindServer("CalcServer"); }
  ~Calc() { cout << "Calc 파괴" << endl; }

  int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
  int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }
};

// DLL 안쪽에서 Proxy를 만드는 함수를 같이 제공해야 합니다.
extern "C" __declspec(dllexport) ICalc* CreateCalc()
{
  return new Calc;
}

// 개발자 명령 프롬프트
// cl CalcProxy.cpp /LD /link user32.lib gdi32.lib kernel32.lib

// cd [경로]
// d: