// 힙에 만드는 싱글톤
// RAII (Resource Acquisition Is Initialize)
// 그런데 4_2 싱글톤 문제: getInstance() 할때마다 lock을 실행하기 때문에 성능저하 발생
// -> DCLP - Double Checked Locking Pattern
// C++에선 절대 쓰지마라!!

// 참고자료: http://gameprogrammingpatterns.com/contents.html
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
	// 외부 생성 금지
	Cursor() {}
	// 복사 금지
	Cursor(const Cursor&);
	void operator=(const Cursor&);

	static Mutex sLock;
	// 내부 포인터 사용
	static Cursor* sInstance;
public:
#if 0
	static Cursor& getInstance()
	{
		// DCLP : C++에서는 절대 사용하면 안된다.
		// 싱글코어 멀티스레드에서는 잘 작동하지만 멀티코어 멀티스레드에서는 쓰면 안돼
		// - 원인: 명령어 비순차 처리
		//		CPU가 처리 순서를 마음대로 바꾼다.
		//		그걸 못하게 memory fence가 있어야 한다.
		//		원래 안됐는데 C++11 에서 메모리 펜스 추가됨

		// C++에서는 DCLP가 제대로 동작하지 않습니다. 사용하지 말아야 합니다.
		// Java에서는 1.5 이상부터 DCLP가 제대로 동작하는 것을 보장합니다.
		//	- 하지만, IODH 를 더 많이 사용합니다. Initialization on demand holder
		if (sInstance == 0)
		{
			Mutex::AutoLock al(sLock);	// 생성자에서 lock
			if (sInstance == 0)
				sInstance = new Cursor;
			return *sInstance;
		}
		// 나가면서 AutoLock의 소멸자 실행 -> unlock
	}
#endif

	// 결론: 이렇게 써라!!
	// C++11/14에서 힙에 생성하는 싱글톤
	//	- 멀티스레드 안정성 표준차원에서 보장한다.
	// 마이어스 싱글톤의 확장판
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

	// 절대 쓰지 말아야 하는 싱글톤 용법
//	Cursor::getInstance().foo();
//	Cursor::getInstance().goo();
//	Cursor::getInstance().hoo();

	cout << &c1 << endl;
	cout << &c2 << endl;
}
