// 프록시
// Remote Proxy - IPC
#include <iostream>
#include "ioacademy.h"

using namespace std;
using namespace ioacademy;

// Proxy Pattern
// Remote Proxy: IPC, Network 서버 역활을 대신하는 클래스
// Smart Proxy: 기존 요소에 추가적인 작업을 하는 클래스

int main()
{
  // 1. 서버의 번호를 얻어온다.
  int handle = IoFindServer("CalcServer");
  cout << "서버 번호: " << handle << endl;

  cout << IoSendServer(handle, 1, 1, 2) << endl;
  cout << IoSendServer(handle, 2, 1, 2) << endl;
}