// Proxy Pattern
// Remote Proxy: 내부적인 프로토콜을 모르는 사용자도 서버의 기능을 로컬처럼 쓸 수 있게 해주자.
// 서버를 개발하는 사람이 클래스 만들어 제공해줘야 - 프로토콜은 서버 제작자가 알고 있기 때문.

// 이것을 실행하기 전 계산기 서버를 실행해야 합니다.

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

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
	// Remote Proxy: 사용자는 내부적인 프로토콜을 몰라도 IPC를 이용할 수 있다.
	Calc* pCalc = new Calc;
	cout << pCalc->add(1, 2) << endl;
	cout << pCalc->sub(1, 2) << endl;
}
