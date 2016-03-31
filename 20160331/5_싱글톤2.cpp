#include <iostream>
using namespace std;

// 힙에 만드는 싱글톤
// - 안드로이드 프레임워크가 사용하고 있는 싱글톤 입니다.

class Mutex
{
public:
  void lock() { cout << "Mutex lock" << endl; }
  void unlock() { cout << "Mutex unlock" << endl; }

  // 동기화 객체 사용시 예외가 발생하면 데드락의 확률이 있습니다.
  // 생성자/소멸자로 동기화 객체를 관리하면 편리하다.
  // RAII(Resource Acqusion Is Initialize) 라는 기술
  // - 편의성, 예외 안정성


  class AutoLock
  {
    Mutex& mLock;
  public:
    AutoLock(Mutex& m) : mLock(m) { mLock.lock();   }
    ~AutoLock()                   { mLock.unlock(); }
  };
};

#include <mutex>  // lock_guard


class Cursor
{
private:
  Cursor() {}
  Cursor(const Cursor&);
  void operator=(const Cursor&);

  static Mutex   sLock;
  static Cursor* sInstance;
public:
  static Cursor& getInstance()
  {
    // sLock.lock();
    lock_guard<Mutex> al(sLock);
    // Mutex::AutoLock al(sLock);

    if (sInstance == 0)
      sInstance = new Cursor;  // std::bad_alloc 예외가 발생 
                               // 할 수 있습니다.
    // sLock.unlock();

    return *sInstance;
  }
};

// static 멤버 변수는 반드시 외부에 정의를 해야 합니다.
Mutex   Cursor::sLock;
Cursor* Cursor::sInstance = 0;


int main()
{
  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  cout << &c1 << endl;
  cout << &c2 << endl;

}