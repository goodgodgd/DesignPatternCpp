// 힙에 만드는 싱글톤
//	- 안드로이드 프레임워크가 사용하고 있는 싱글톤입니다.
// RAII (Resource Acquisition Is Initialize)
// C++ 표준에도 도입됨 <mutex> lock_guard
// C++ 자원 관리에 매우 중요, 예외 안정성에도 크게 기여
// 참고자료: http://occamsrazr.net/tt/297

#include <iostream>
using namespace std;

#if 0
class Mutex
{
public:
	// 동기화 객체 사용시 예외가 발생하면 데드락의 확률이 있습니다.
	// 생성자/소멸자로 동기화 객체를 관리하면 편리하다.
	void lock() { cout << "Mutex lock" << endl; }
	void unlock() { cout << "Mutex unlock" << endl; }
};

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
	static Cursor& getInstance()
	{
		// NULL 확인보다 new가 더 복잡하다.
		// 두개의 스레드가 동시에 들어오면 new를 하고 있는 중에 다른것이 생성될 수 있다.
		// new 라인을 Critical section 이라 생각하고 보호 필요 (Mutex)
		// 그런데 lock을 쓰고 중간에 빠져나가지 못하면 하나도 생성이 안돼 - 예외가 발생했을 때
		sLock.lock();
		if (sInstance == 0)
			sInstance = new Cursor;	// std::bad_alloc 예외가 발생할수 있습니다.
									// unlock이 호출되지 않고 밖으로 빠져나갈 수 있다.
		sLock.unlock();
		return *sInstance;
	}
};
// static 멤버 변수는 반드시 외부에 정의해야 합니다.
Cursor* Cursor::sInstance = 0;
Mutex Cursor::sLock;
#endif

// C 스타일 자원관리: goto 활용
// C++에서는 절대 쓰지마라!
void foo()
{
	// 생성1
	// 생성2

	// 아래와 같이 쓰지말고
	// if(err1) 소멸1 소멸2 리턴
	// if(err2) 소멸1 소멸2 리턴

	// if(err1) goto
	// if(err2) goto
	// error: 소멸1 소멸2
}

class Mutex
{
public:
	void lock() { cout << "Mutex lock" << endl; }
	void unlock() { cout << "Mutex unlock" << endl; }

	// 동기화 객체 사용시 예외가 발생하면 데드락의 확률이 있습니다.
	// 생성자/소멸자로 동기화 객체를 관리하면 편리하다.
	// C++에서는 예외에 의해서 함수를 빠져나갈 때 지역 객체의 소멸을 보장한다.
	// 또한 lock -unlock 쌍을 맞출 필요가 없다.
	// RAII (Resource Acquision Is Initialize)라는 기술
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
	static Cursor& getInstance()
	{
//		sLock.lock();
		Mutex::AutoLock al(sLock);	// 생성자에서 lock
		// C++ 표준이용하면 다음과 같이 쓸 수 잇다.
//		lock_guard<Mutex> al(sLock);

		if (sInstance == 0)
			sInstance = new Cursor;
		return *sInstance;
		// 나가면서 AutoLock의 소멸자 실행 -> unlock
		// 예외가 발생해도 소멸된다.
	}
};
// static 멤버 변수는 반드시 외부에 정의해야 합니다.
Cursor* Cursor::sInstance = 0;
Mutex Cursor::sLock;


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}

// 텍스트 검색할 때 grep 사용하는 것보다 ag 명령을 쓰는 것이 훨씬 빠르다. 병렬검색
