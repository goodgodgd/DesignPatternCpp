// ���� ����� �̱���
// RAII (Resource Acquisition Is Initialize)
// �׷��� 4_2 �̱��� ����: getInstance() �Ҷ����� lock�� �����ϱ� ������ �������� �߻�
// -> DCLP - Double Checked Locking Pattern
// C++���� ���� ��������!!

// �����ڷ�: http://gameprogrammingpatterns.com/contents.html
// ... C++11 mandates that the initializer for a local static variable is only run once


#include <iostream>
using namespace std;


class Mutex
{
public:
	void lock() { cout << "Mutex lock" << endl; }
	void unlock() { cout << "Mutex unlock" << endl; }
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
#if 0
	static Cursor& getInstance()
	{
		// DCLP : C++������ ���� ����ϸ� �ȵȴ�.
		// �̱��ھ� ��Ƽ�����忡���� �� �۵������� ��Ƽ�ھ� ��Ƽ�����忡���� ���� �ȵ�
		// - ����: ��ɾ� ����� ó��
		//		CPU�� ó�� ������ ������� �ٲ۴�.
		//		�װ� ���ϰ� memory fence�� �־�� �Ѵ�.
		//		���� �ȵƴµ� C++11 ���� �޸� �潺 �߰���

		// C++������ DCLP�� ����� �������� �ʽ��ϴ�. ������� ���ƾ� �մϴ�.
		// Java������ 1.5 �̻���� DCLP�� ����� �����ϴ� ���� �����մϴ�.
		//	- ������, IODH �� �� ���� ����մϴ�. Initialization on demand holder
		if (sInstance == 0)
		{
			Mutex::AutoLock al(sLock);	// �����ڿ��� lock
			if (sInstance == 0)
				sInstance = new Cursor;
			return *sInstance;
		}
		// �����鼭 AutoLock�� �Ҹ��� ���� -> unlock
	}
#endif

	// ���: �̷��� ���!!
	// C++11/14���� ���� �����ϴ� �̱���
	//	- ��Ƽ������ ������ ǥ���������� �����Ѵ�.
	// ���̾ �̱����� Ȯ����
	static Cursor& getInstance()
	{
		static Cursor* instance = new Cursor();
		return *instance;
	}


};
Cursor* Cursor::sInstance = 0;
Mutex Cursor::sLock;


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	// ���� ���� ���ƾ� �ϴ� �̱��� ���
//	Cursor::getInstance().foo();
//	Cursor::getInstance().goo();
//	Cursor::getInstance().hoo();

	cout << &c1 << endl;
	cout << &c2 << endl;
}
