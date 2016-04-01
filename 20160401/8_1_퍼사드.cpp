// 8_Facade



#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")		// DLL 링킹, 동적 라이브러리 링크

int main()
{
	WSADATA w;
	WSAStartup(0x202, &w); // 네트워크 라이브러리 초기화
							// 0x202: 버전, w: output

	// 1. 소켓 생성
	int sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓

	// 2. 소켓에 주소 지정
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		// 인터넷 사용
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sock, (SOCKADDR*)&addr, sizeof(addr));	// 소켓 주소 지정

	// 3. 소켓을 대기 상태로변경
	listen(sock, 5);	// 5: 무시, 전통일뿐

	// 4. 클라이언트 대기
	SOCKADDR_IN addr2 = { 0 };
	int sz = sizeof(addr2);

	accept(sock, (SOCKADDR*)&addr2, &sz);	// Client가 접속할 때 까지 대기한다.



	// 이 과정이 복잡하다. 클래스로 래핑하자 -> 다음

	WSACleanup();
}
