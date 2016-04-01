// 5_싱글톤3

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

class Cursor
{
private:
  Cursor() {}
  Cursor(const Cursor&);
  void operator=(const Cursor&);

  static Mutex   sLock;
  static Cursor* sInstance;
public:

  // DCLP - Double Checked Locking Pattern
  // - 원인: 명령어 비순차 처리

  // C++ 에서는 DCLP가 제대로 동작하지 않습니다. 사용하지 말아야 합니다.
  // Java에서는 1.5 이상부터 DCLP가 제대로 동작하는 것을 보장합니다.
  // - IODH 를 더 많이 사용합니다.

  // C++11/14에서 힙에 생성하는 싱글톤
  // - 멀티 스레드 안전성을 표준 차원에서 보장한다.
  // http://gameprogrammingpatterns.com/contents.html

  static Cursor& getInstance()
  {
    static Cursor* instance = new Cursor();
    return *instance;
  }

#if 0
  static Cursor& getInstance()
  {
    if (sInstance == 0) 
    {
      Mutex::AutoLock al(sLock);

      if (sInstance == 0)
        sInstance = new Cursor;
    }

    return *sInstance;
  }
#endif
};

Mutex   Cursor::sLock;
Cursor* Cursor::sInstance = 0;


int main()
{
  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  cout << &c1 << endl;
  cout << &c2 << endl;
}