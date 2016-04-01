// 8_Facade



#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")

int main()
{
  WSADATA w;
  WSAStartup(0x202, &w); // 네트워크 라이브러리 초기화

  // 1. 소켓 생성
  int sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓

  // 2. 소켓에 주소 지정
  SOCKADDR_IN addr = { 0 };
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(sock, (SOCKADDR*)&addr, sizeof(addr));

  // 3. 소켓을 대기 상태로변경
  listen(sock, 5);

  // 4. 클라이언트 대기
  SOCKADDR_IN addr2 = { 0 };
  int sz = sizeof(addr2);

  accept(sock, (SOCKADDR*)&addr2, &sz);// Client가 접속할
                                       // 때 까지 대기한다.

  WSACleanup();
}