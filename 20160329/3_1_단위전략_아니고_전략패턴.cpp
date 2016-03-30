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
		// 이렇게 짜면 싱글 스레드 사용자는 엄청난 성능 저하 발생
		// 동기화 정책도 분리되서 사용자가 선택할 수 있게 해야 한다.
		// mutex lock
		// ...
		// mutex unlock
	}
};
#endif

// 동기화 여부를 인터페이스 기반의 다른 클래스로 분리하자.
// 장점: 실행 시간에 정책을 교체할 수 있다. - setSync
// 단점: 가상 함수 기반이므로 느리다.
//		싱글 스레드에서 lock, unlock 에서 아무것도 하지 않아도 함수 콜 자체가 부하가 있기 때문에 직접 구현을 넣는 것보다는 느리다.
// 그런데 내부적인 정책 (싱글 스레드, 멀티 스레드)가 고정적이면 인터페이스를 쓸 필요가 없다.

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
	// 동기화 정책 선택
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

List<int> st; // 전역 변수: 멀티 스레드에서 동기화 문제 주의

int main()
{
	st.setSync(new MultiThread);
//	st.setSync(new SingleThread);
	st.push_front(10);
}
