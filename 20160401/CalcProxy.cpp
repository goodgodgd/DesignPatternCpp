
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

// 사용자가 구현 클래스의 이름을 알 필요없게 ICalc로 생성하는 생성 메소드 만들자.
// extern "C": C 스타일로 만들어라, 오버로딩 하지마라
// _declspec(dllexport): 윈도우 문법
extern "C" _declspec(dllexport) ICalc* CreateCalc()
{
	return new Calc;
}

// 개발자 명령 프롬프트
// cl CalcProxy.cpp /LD /link user32.lib gdi32.lib kernel32.lib
// /LD: DLL만들어라
// /link: ioacamedy가 의존하는 라이브러리 연결
