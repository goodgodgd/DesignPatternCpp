
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

// �̱����� ����� ������ �׻� �����մϴ�.
// �θ�Ŭ������ �����ϸ� ���ϰ� ����� �� �ֽ��ϴ�.
// �ڽ�Ŭ������ �����ڴ� �θ��� ������ ���� ���ؼ� CRTP ���� �̿�

template<typename TYPE>
class Singleton
{

protected:
	Singleton() {}	// �����ڰ� private�̸� �ڽ��� �θ��� ������ ���� ����
private:	// ���� ������ �ڽ��� �״�� ���
	Singleton(const Singleton&);
	void operator=(const Singleton&);

	static Mutex sLock;
	static TYPE* sInstance;
public:
	static TYPE& getInstance()
	{
		Mutex::AutoLock al(sLock);	// �����ڿ��� lock
		if (sInstance == 0)
			sInstance = new TYPE;
		return *sInstance;
	}
};

// �ܺο��� ���Ǹ� �� ���� ���ø� ���
template<typename TYPE>
TYPE* Singleton<TYPE>::sInstance = 0;
template<typename TYPE>
Mutex Singleton<TYPE>::sLock;

// CRTP���� - �ڽ��� �θ��� ���ø����� ���
class Cursor : public Singleton<Cursor>
{
private:
	Cursor() {}	// �̰� ������ Cursor ��ü�� �׳� ������

	// �θ� Ŭ�������� �ڽ��� private �����ڿ� ���� �����ϰ� ���ش�. -> new TYPE
	friend class Singleton < Cursor > ;
};


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}
