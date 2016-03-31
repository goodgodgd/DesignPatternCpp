// ���� ����� �̱���
//	- �ȵ���̵� �����ӿ�ũ�� ����ϰ� �ִ� �̱����Դϴ�.
// RAII (Resource Acquisition Is Initialize)
// C++ ǥ�ؿ��� ���Ե� <mutex> lock_guard
// C++ �ڿ� ������ �ſ� �߿�, ���� ���������� ũ�� �⿩
// �����ڷ�: http://occamsrazr.net/tt/297

#include <iostream>
using namespace std;

#if 0
class Mutex
{
public:
	// ����ȭ ��ü ���� ���ܰ� �߻��ϸ� ������� Ȯ���� �ֽ��ϴ�.
	// ������/�Ҹ��ڷ� ����ȭ ��ü�� �����ϸ� ���ϴ�.
	void lock() { cout << "Mutex lock" << endl; }
	void unlock() { cout << "Mutex unlock" << endl; }
};

class Cursor
{
private:
	// �ܺ� ���� ����
	Cursor() {}
	// ���� ����
	Cursor(const Cursor&);
	void operator=(const Cursor&);

	static Mutex sLock;
	// ���� ������ ���
	static Cursor* sInstance;
public:
	static Cursor& getInstance()
	{
		// NULL Ȯ�κ��� new�� �� �����ϴ�.
		// �ΰ��� �����尡 ���ÿ� ������ new�� �ϰ� �ִ� �߿� �ٸ����� ������ �� �ִ�.
		// new ������ Critical section �̶� �����ϰ� ��ȣ �ʿ� (Mutex)
		// �׷��� lock�� ���� �߰��� ���������� ���ϸ� �ϳ��� ������ �ȵ� - ���ܰ� �߻����� ��
		sLock.lock();
		if (sInstance == 0)
			sInstance = new Cursor;	// std::bad_alloc ���ܰ� �߻��Ҽ� �ֽ��ϴ�.
									// unlock�� ȣ����� �ʰ� ������ �������� �� �ִ�.
		sLock.unlock();
		return *sInstance;
	}
};
// static ��� ������ �ݵ�� �ܺο� �����ؾ� �մϴ�.
Cursor* Cursor::sInstance = 0;
Mutex Cursor::sLock;
#endif

// C ��Ÿ�� �ڿ�����: goto Ȱ��
// C++������ ���� ��������!
void foo()
{
	// ����1
	// ����2

	// �Ʒ��� ���� ��������
	// if(err1) �Ҹ�1 �Ҹ�2 ����
	// if(err2) �Ҹ�1 �Ҹ�2 ����

	// if(err1) goto
	// if(err2) goto
	// error: �Ҹ�1 �Ҹ�2
}

class Mutex
{
public:
	void lock() { cout << "Mutex lock" << endl; }
	void unlock() { cout << "Mutex unlock" << endl; }

	// ����ȭ ��ü ���� ���ܰ� �߻��ϸ� ������� Ȯ���� �ֽ��ϴ�.
	// ������/�Ҹ��ڷ� ����ȭ ��ü�� �����ϸ� ���ϴ�.
	// C++������ ���ܿ� ���ؼ� �Լ��� �������� �� ���� ��ü�� �Ҹ��� �����Ѵ�.
	// ���� lock -unlock ���� ���� �ʿ䰡 ����.
	// RAII (Resource Acquision Is Initialize)��� ���
	class AutoLock
	{
		Mutex& mLock;
	public:
		inline AutoLock(Mutex& m) : mLock(m) { mLock.lock(); }
		inline ~AutoLock() { mLock.unlock(); }
	};
};

#include <mutex>		// lock_guard

class Cursor
{
private:
	// �ܺ� ���� ����
	Cursor() {}
	// ���� ����
	Cursor(const Cursor&);
	void operator=(const Cursor&);

	static Mutex sLock;
	// ���� ������ ���
	static Cursor* sInstance;
public:
	static Cursor& getInstance()
	{
//		sLock.lock();
		Mutex::AutoLock al(sLock);	// �����ڿ��� lock
		// C++ ǥ���̿��ϸ� ������ ���� �� �� �մ�.
//		lock_guard<Mutex> al(sLock);

		if (sInstance == 0)
			sInstance = new Cursor;
		return *sInstance;
		// �����鼭 AutoLock�� �Ҹ��� ���� -> unlock
		// ���ܰ� �߻��ص� �Ҹ�ȴ�.
	}
};
// static ��� ������ �ݵ�� �ܺο� �����ؾ� �մϴ�.
Cursor* Cursor::sInstance = 0;
Mutex Cursor::sLock;


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}

// �ؽ�Ʈ �˻��� �� grep ����ϴ� �ͺ��� ag ����� ���� ���� �ξ� ������. ���İ˻�
