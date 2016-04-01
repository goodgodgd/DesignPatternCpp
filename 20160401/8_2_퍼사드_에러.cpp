// 8_Facade

#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")		// 동적 라이브러리 링크

// SRP (Single Responsibility Principle) : 단일 책임의 원칙
//	- 모듈(클래스, 함수, 변수)은 단 하나만의 책임을 가져야 한다.
// 이 클래스는 주소만! 만든다.
class IPAddress
{
	SOCKADDR_IN addr;
public:
	IPAddress(const char* ip, short port) 
	{ 
		memset((void*)&addr, 0, sizeof(addr)); 
		addr.sin_family = AF_INET;		// 인터넷 사용
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);

	}
								// string::c_str()의 원리
	SOCKADDR* getRawAddress()	// string -> const char*
	{
		return (SOCKADDR*)&addr;	
	}

};

// 초기화/정리의 작업은 생성자/소멸자가 좋다 - RAII
// 만약 예외로 main을 빠져나간다 하더라도 지역객체의 소멸자는 호출한다 - 예외안정성
class NetworkSystem
{
public:
	NetworkSystem() 
	{
		WSADATA w;
		// 0x202: 버전, w: output
		WSAStartup(0x202, &w); // 네트워크 라이브러리 초기화
	}

	~NetworkSystem()
	{
		WSACleanup();
	}
};

class Socket
{
	int sock;
public:
	Socket(int type)
	{
		sock = socket(PF_INET, type, 0); // TCP 소켓
	}

	// C++ 이름 탐색 법칙
	// 이 bind가 전역함수인지 표시를 해줘야 한다.
	// :: - 전역스코프, 익명스코프
	void bind(IPAddress* ip)
	{
		::bind(sock, ip->getRawAddress(), sizeof(SOCKADDR_IN));
	}
	void listen(int backlog)
	{
		::listen(sock, backlog);
	}
	void accept()
	{
		// 4. 클라이언트 대기
		SOCKADDR_IN addr2 = { 0 };
		int sz = sizeof(addr2);
		::accept(sock, (SOCKADDR*)&addr2, &sz);	// Client가 접속할 때 까지 대기한다.
	}
};


// TCP 서버 프로그램을 하는데 필요한 클래스와 절차를 단순화시켜주는 상위 개념의 클래스를 제공하자.
// -> Facade Pattern


// => ACE (TCPSerer, Process, Thread...)
// C++ Network Programming I / II

// => boost asio / poco


#if 0
int main()
{
	NetworkSystem system;

	// 1. 소켓 생성
	Socket sock(SOCK_STREAM);

	// 2. 소켓에 주소 지정
	IPAddress ip("127.0.0.1", 4000);

	sock.bind((SOCKADDR*)&addr, sizeof(addr));	// 소켓 주소 지정

	// 3. 소켓을 대기 상태로변경
	sock.listen(5);	// 5: 무시, 전통일뿐

	// 4. 클라이언트 대기
	sock.accept();	// Client가 접속할 때 까지 대기한다.

}
#endif

// 하지만 이것조차 서버를 여는 과정을 알아야 한다.!!

class TCPServer
{
	NetworkSystem system;
	Socket sock;
public:
	TCPServer() : sock(SOCK_STREAM) {}

	void start(const char* ip, short port)
	{
		IPAddress ip(ip, port);
		sock.bind(&ip);
		sock.listen(5);
		sock.accept();
	}
};

int main()
{
	TCPServer server;
	server.start("127.0.0.1", 4000);
}

// 첫날 배운 thiscall에서 배운 스레드 래핑 클래스도 퍼사드다
// 사용자에게 필요한 것만 노출
