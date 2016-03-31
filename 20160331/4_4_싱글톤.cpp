
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

// 싱글톤을 만드는 로직은 항상 동일합니다.
// 부모클래스로 제공하면 편리하게 사용할 수 있습니다.
// 자식클래스의 생성자는 부모의 생성자 접근 못해서 CRTP 패턴 이용

template<typename TYPE>
class Singleton
{

protected:
	Singleton() {}	// 생성자가 private이면 자식이 부모의 생성자 접근 못해
private:	// 복사 금지는 자식이 그대로 사용
	Singleton(const Singleton&);
	void operator=(const Singleton&);

	static Mutex sLock;
	static TYPE* sInstance;
public:
	static TYPE& getInstance()
	{
		Mutex::AutoLock al(sLock);	// 생성자에서 lock
		if (sInstance == 0)
			sInstance = new TYPE;
		return *sInstance;
	}
};

// 외부에서 정의를 할 때도 템플릿 사용
template<typename TYPE>
TYPE* Singleton<TYPE>::sInstance = 0;
template<typename TYPE>
Mutex Singleton<TYPE>::sLock;

// CRTP패턴 - 자신을 부모의 템플릿으로 사용
class Cursor : public Singleton<Cursor>
{
private:
	Cursor() {}	// 이거 없으면 Cursor 객체가 그냥 생성돼

	// 부모 클래스에서 자신의 private 생성자에 접근 가능하게 해준다. -> new TYPE
	friend class Singleton < Cursor > ;
};


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}
