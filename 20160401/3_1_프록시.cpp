// Proxy Pattern
// Remove Proxy: IPC, Network 서버 역할을 대신하는 클래스
// Smart Proxy: 기존 요소에 추가적인 작업을 하는 클래스, 스마트 포인터, RAII

#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// 문제: 내부적인 프로토콜을 알아야만 쓸 수 있다.
// 서버의 기능을 로컬처럼 쓸 수 있게 해주자.


int main()
{
	// 1. 서버의 번호를 얻어온다.
	int handle = IoFindServer("CalcServer");
	cout << "서버 번호: " << handle << endl;

	cout << IoSendServer(handle, 1, 1, 2) << endl;	// 3 = 1 + 2
	cout << IoSendServer(handle, 2, 1, 2) << endl;	// -1 = 1 - 2;
}

