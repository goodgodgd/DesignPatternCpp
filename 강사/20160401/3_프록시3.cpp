// 3_프록시3
// 서버 제작자에게서 ICalc.h와 CalcProxy.dll을 받아야 합니다.
#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "ICalc.h"

int main()
{
  // sp<> - 모듈의 수명을 관리하기 위해서 입니다.
  Ptr<ICalc> pCalc = CreateInstance();

  // 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
  cout << pCalc->add(10, 20) << endl;
  cout << pCalc->sub(10, 20) << endl;

  // delete pCalc;   // 절대 하면 안됩니다.
  // dll을 만들 때와 dll을 사용하는 코드의 컴파일러 버전이 달라도
  // 같은 컴파일러에서 new와 delete의 코드가 생성되어야 한다.
  // -> 참조 계수 기반 객체 수명 관리
}


#if 0
int main()
{
  // 1. CalcProxy.dll을 로드 합니다.
  void* addr = IoLoadModule("CalcProxy.dll");

  // 2. Calc 객체 생성하는 함수를 찾아야 합니다.
  typedef ICalc*(*F)();
  F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

  // 3. Calc 객체 생성
  ICalc* pCalc = f();

  // 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
  cout << pCalc->add(10, 20) << endl;
  cout << pCalc->sub(10, 20) << endl;
}
#endif