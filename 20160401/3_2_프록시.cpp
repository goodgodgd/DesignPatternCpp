// Proxy Pattern
// Remove Proxy: IPC, Network 서버 역할을 대신하는 클래스
// Smart Proxy: 기존 요소에 추가적인 작업을 하는 클래스, 스마트 포인터, RAII

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// 문제: 내부적인 프로토콜을 알아야만 쓸 수 있다.
// 서버의 기능을 로컬처럼 쓸 수 있게 해주자.

// 서버 대신에 사용할 클래스를 만들어 봅시다.
// 서버를 개발하는 사람이 만들어 제공해줘야 - 프로토콜은 서버 제작자가 알고 있기 때문.

// 서버 제작자가 아래 클래스를 제작해서 클라이언트 개발자에게 제공하는 것입니다.
class Calc
{
	int handle;
public:
	Calc() { handle = IoFindServer("CalcServer"); }
	int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
	int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }
};

int main()
{
	// Remote Proxy: 사용자는 내부적인 프로토콜을 몰라도 IPC 이용할 수 있다.
	Calc* pCalc = new Calc;
	cout << pCalc->add(1, 2) << endl;
	cout << pCalc->sub(1, 2) << endl;
}

// 구현체를 제공하기 보다는 인터페이스를 제공하자
// 서버쪽 구현이 달라져도 클라이언트 모듈이 다시 컴파일될 필요 없이 DLL만 바꾸면 되게 하자.
// 이제 서버 개발자에게 2개의 파일을 받아야 합니다.
// 1. ICalc.h : 인터페이스 헤더
// 2. CalcProxy.dll: Proxy Class 가 있는 DLL
