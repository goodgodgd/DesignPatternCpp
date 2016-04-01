// 8_Facade

#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")		// ���� ���̺귯�� ��ũ

// SRP (Single Responsibility Principle) : ���� å���� ��Ģ
//	- ���(Ŭ����, �Լ�, ����)�� �� �ϳ����� å���� ������ �Ѵ�.
// �� Ŭ������ �ּҸ�! �����.
class IPAddress
{
	SOCKADDR_IN addr;
public:
	IPAddress(const char* ip, short port) 
	{ 
		memset((void*)&addr, 0, sizeof(addr)); 
		addr.sin_family = AF_INET;		// ���ͳ� ���
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);

	}
								// string::c_str()�� ����
	SOCKADDR* getRawAddress()	// string -> const char*
	{
		return (SOCKADDR*)&addr;	
	}

};

// �ʱ�ȭ/������ �۾��� ������/�Ҹ��ڰ� ���� - RAII
// ���� ���ܷ� main�� ���������� �ϴ��� ������ü�� �Ҹ��ڴ� ȣ���Ѵ� - ���ܾ�����
class NetworkSystem
{
public:
	NetworkSystem() 
	{
		WSADATA w;
		// 0x202: ����, w: output
		WSAStartup(0x202, &w); // ��Ʈ��ũ ���̺귯�� �ʱ�ȭ
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
		sock = socket(PF_INET, type, 0); // TCP ����
	}

	// C++ �̸� Ž�� ��Ģ
	// �� bind�� �����Լ����� ǥ�ø� ����� �Ѵ�.
	// :: - ����������, �͸�����
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
		// 4. Ŭ���̾�Ʈ ���
		SOCKADDR_IN addr2 = { 0 };
		int sz = sizeof(addr2);
		::accept(sock, (SOCKADDR*)&addr2, &sz);	// Client�� ������ �� ���� ����Ѵ�.
	}
};


// TCP ���� ���α׷��� �ϴµ� �ʿ��� Ŭ������ ������ �ܼ�ȭ�����ִ� ���� ������ Ŭ������ ��������.
// -> Facade Pattern


// => ACE (TCPSerer, Process, Thread...)
// C++ Network Programming I / II

// => boost asio / poco


#if 0
int main()
{
	NetworkSystem system;

	// 1. ���� ����
	Socket sock(SOCK_STREAM);

	// 2. ���Ͽ� �ּ� ����
	IPAddress ip("127.0.0.1", 4000);

	sock.bind((SOCKADDR*)&addr, sizeof(addr));	// ���� �ּ� ����

	// 3. ������ ��� ���·κ���
	sock.listen(5);	// 5: ����, �����ϻ�

	// 4. Ŭ���̾�Ʈ ���
	sock.accept();	// Client�� ������ �� ���� ����Ѵ�.

}
#endif

// ������ �̰����� ������ ���� ������ �˾ƾ� �Ѵ�.!!

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

// ù�� ��� thiscall���� ��� ������ ���� Ŭ������ �ۻ���
// ����ڿ��� �ʿ��� �͸� ����
