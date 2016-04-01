// 5_�̱���3

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
  // - ����: ��ɾ� ����� ó��

  // C++ ������ DCLP�� ����� �������� �ʽ��ϴ�. ������� ���ƾ� �մϴ�.
  // Java������ 1.5 �̻���� DCLP�� ����� �����ϴ� ���� �����մϴ�.
  // - IODH �� �� ���� ����մϴ�.

  // C++11/14���� ���� �����ϴ� �̱���
  // - ��Ƽ ������ �������� ǥ�� �������� �����Ѵ�.
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