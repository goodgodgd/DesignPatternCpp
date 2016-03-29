// 1cEbJ
#include <iostream>
using namespace std;

// ���� ����(Policy-based) Design - "Modern C++ design"
// => ��å�� ���� �ڵ带 ������ �ð��� ������ ���� ���
// => C++ ǥ�� ���̺귯���� �ٽ� ������ ���
//		���� ���������� ���� �������̽��� ���ǵ��� �ʰ� �������� "����"�� �����Ͽ� �����Ѵ�.

// java, C#���� ����� Ȯ���Ϸ��� �������̽��� ����ϸ� �Ǵµ� "C++ǥ�� ���̺귯���� Ȯ���ؼ� ����ϱ�" ���ؼ��� ���������� �����ؾ� �Ѵ�.
// "Modern C++ design" ���� - C++ ǥ������, Template�� õ��, ���� C++�� �������� �ٲ����. ���� Facebook�� ���̺귯�� ���� folly, C++17���� �ݿ�
// folly: ���ڿ� �ٷ�µ� ���� (unicode), vector �缳��

// ����: �����Լ��� �ƴ� �ζ��� �Լ��̴�. ȣ�⿡ ���� ���� ���ϰ� ����.
// ����: ��å Ŭ������ �Լ��� �ƴ� ���ø� ���ڷ� ���޵ǹǷ�, ���� �ÿ� ��å�� ��ü�ϴ� ���� �Ұ����ϴ�.
//		=> ������ �� �� ��å�� �����ȴ�!!

// ����� ����� ���� ����
template <typename T, typename ThreadModel>
class List : public ThreadModel
{
public:
	void push_front(const T& a)
	{
		// ��� ���� lock, unlock
		lock();
		//...
		unlock();
	}
};

class MultiThread
{
public:
	void lock() { cout << "mutex lock" << endl; }
	void unlock() { cout << "mutex unlock" << endl; }
};

class SingleThread
{
public:
	// inline���� ����� ���ΰ� ������Ƿ� lock(); unlock(); ���� �����Ϸ��� ����������.
	// �̱� ������� ������ ����!!
	inline void lock() {}
	inline void unlock() {}
};

// ��Ƽ �������� "Ÿ��"�� �Ѿ��.

List<int, MultiThread> st;

int main()
{
	st.push_front(10);
}
