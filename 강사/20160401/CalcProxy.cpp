// CalcProxy.cpp
#include "ICalc.h"

#include <iostream>
using namespace std;


class Calc : public ICalc
{
  int handle;
public:
  Calc() { handle = IoFindServer("CalcServer"); }
  ~Calc() { cout << "Calc �ı�" << endl; }

  int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
  int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }
};

// DLL ���ʿ��� Proxy�� ����� �Լ��� ���� �����ؾ� �մϴ�.
extern "C" __declspec(dllexport) ICalc* CreateCalc()
{
  return new Calc;
}

// ������ ��� ������Ʈ
// cl CalcProxy.cpp /LD /link user32.lib gdi32.lib kernel32.lib

// cd [���]
// d: