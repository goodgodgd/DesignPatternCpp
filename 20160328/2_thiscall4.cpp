// ��Ƽ �����带 ĸ��ȭ �غ��ô�.
// Java C#�� �ٸ��� C++ ���ο��� ����� ����. thread ����
// OS�� �����ϴ� API �̿��ؾ�. Win32API, System call
// �׷��� API�� C���� �Ǿ��־ �Ϻ� ����(���� ���)�� �����ؾ� ����� �� �ִ�.
// C++ wrapper �ʿ�
// http://d.pr/n/IpaL

#include <Windows.h>	// for thread
#include <iostream>
using namespace std;

#if 0
// __stdcall: ������ call ���
DWORD __stdcall foo(void* p)
{
	cout << "Thread start!!" << endl;
	return 0;
}

int main()
{
	// 0: use default value
	// 0���� ó���� ���ʿ���(�˰���� ����, ������) ���ڰ� �ʹ� ����. (C ���)
	CreateThread(0, 0, foo, "A", 0, 0);
	getchar();
}
#endif

// MyThread�� �����ϱ� ���ؼ��� run() �Լ��� threadLoop() �Լ��� �ʿ�
// thread �����δ� Thread Ŭ�������� ���
// run()������ threadLoop�� �ٷ� CreateThread()�� ������ �� ����
// => CreateThread()�� ���� ������ static �Լ� _threadLoop() ����� ����
// _threadLoop()������ ���� �����ؾ� �ϴ� threadLoop() ȣ�� �Ұ� (static �ƴ�)
// => CreateThread()���� this�� �޾ƿ� this->threadLoop()�� ����

class Thread
{
public:
	void run()
	{
		// ��� �Լ� �̹Ƿ� �Ϲ� �Լ� �����͸� �ѱ�� �� �ȴ�. -> static ��� �Լ�
//		CreateThread(0, 0, _threadLoop, 0, 0, 0);
		// static �Լ��� this�� ����
		CreateThread(0, 0, _threadLoop, this, 0, 0);
	}

	// 1. �Ʒ� �Լ��� static ��� �Լ� �� �� �ۿ� ���� ����: �Ϲ� �Լ� �����͸� CreateThread()�� ���� �� ���� ����
	// 2. this�� �����Ƿ� ������ �Լ� ���ڷ� this�� �����ϴ� ���
	// �ڹٳ� �ȵ���̵� �����ӿ�ũ���� ����ϴ� ���
	static DWORD __stdcall _threadLoop(void* user)
	{
		Thread* self = static_cast<Thread*>(user);
		// ���� �Լ������� (_threadLoop ) �Ϲ� ��� �Լ� ȣ�� �ȵ�
//		threadLoop();
		// this�� �޾ƿͼ� �Ϲ� ��� �Լ� ȣ��
		self->threadLoop();
		return 0;
	}

	// ���� ������ ������ ������ �Լ��� �Ϲ������� static �ƴϴ�.
	virtual bool threadLoop() { return false; }
};

// �Ʒ� Ŭ������ ���̺귯���� ����� �Դϴ�.
class MyThread : public Thread
{
public:
	virtual bool threadLoop()
	{
		cout << "My Thread threadLoop()" << endl;
		return true;
	}
};

int main()
{
	MyThread t;
	t.run();	// �� ���� �����尡 �����Ǿ �����Լ��� threadLooop()�� �����ؾ� �մϴ�.
	getchar();
}

// NEWS: ���� C11, C++11/14 ������ thread api �����ϰ� �ִ�.
// http://www.cplusplus.com/reference/thread/thread/
