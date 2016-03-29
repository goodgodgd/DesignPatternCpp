// http://p.dr/n/17
#include <iostream>
using namespace std;

#if 0
template <typename T>
class List
{
public:
	void push_front(const T& a)
	{
		// �̷��� ¥�� �̱� ������ ����ڴ� ��û�� ���� ���� �߻�
		// ����ȭ ��å�� �и��Ǽ� ����ڰ� ������ �� �ְ� �ؾ� �Ѵ�.
		// mutex lock
		// ...
		// mutex unlock
	}
};
#endif

// ����ȭ ���θ� �������̽� ����� �ٸ� Ŭ������ �и�����.
// ����: ���� �ð��� ��å�� ��ü�� �� �ִ�. - setSync
// ����: ���� �Լ� ����̹Ƿ� ������.
//		�̱� �����忡�� lock, unlock ���� �ƹ��͵� ���� �ʾƵ� �Լ� �� ��ü�� ���ϰ� �ֱ� ������ ���� ������ �ִ� �ͺ��ٴ� ������.
// �׷��� �������� ��å (�̱� ������, ��Ƽ ������)�� �������̸� �������̽��� �� �ʿ䰡 ����.

struct ISync
{
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual ~ISync() {}
};

template <typename T>
class List
{
	ISync* pSync;
public:
	List() : pSync(0) {}
	// ����ȭ ��å ����
	void setSync(ISync* p) { pSync = p; }

	void push_front(const T& a)
	{
		pSync->lock();
		// ...
		pSync->unlock();
	}
};

class MultiThread : public ISync
{
public:
	virtual void lock() { cout << "Mutex lock" << endl; }
	virtual void unlock() { cout << "Mutex unlock" << endl;} 
};


class SingleThread : public ISync
{
public:
	virtual void lock() {}
	virtual void unlock() {}
};

List<int> st; // ���� ����: ��Ƽ �����忡�� ����ȭ ���� ����

int main()
{
	st.setSync(new MultiThread);
//	st.setSync(new SingleThread);
	st.push_front(10);
}
