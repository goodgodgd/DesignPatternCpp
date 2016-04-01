// 프록시
// Remote Proxy - IPC
#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// 서버 대신에 사용할 클래스를 만들어 봅시다.
class Calc
{
  int handle;
public:
  Calc() { handle = IoFindServer("CalcServer"); }

  int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
  int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }
};
// 서버 제작자가 위 클래스를 제작해서 클라이언트 개발자에게 
// 배포하는 것 입니다.

// 이제 서버 개발자에게 2개의 파일을 받아야 합니다.
// 1. ICalc.h: 인터페이스 헤더
// 2. CalcProxy.dll: Proxy Class가 있는 DLL


int main()
{
  Calc* pCalc = new Calc;
  cout << pCalc->add(1, 2) << endl;
  cout << pCalc->sub(1, 2) << endl;
}