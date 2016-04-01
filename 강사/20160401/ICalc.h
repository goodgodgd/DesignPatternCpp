
// ICalc.h
class RefCountedObject
{
  int mCount;
public:
  RefCountedObject() : mCount(0) {}
  virtual ~RefCountedObject() {}

  void addRef() { ++mCount; }
  void release()
  {
    if (--mCount == 0)
      delete this;
  }
};

template <typename T>
class Ptr
{
  T* ptr;
public:
  Ptr(T* p) : ptr(p) { ptr->addRef(); }
  Ptr(const Ptr& p) : ptr(p.ptr)
  {
    ptr->addRef();
  }

  ~Ptr() { ptr->release(); }

  // 진짜 포인터처럼 보여야 한다. ->, * 연산자를 재정의해야 한다.
  // => 스마트 포인터 기본
  T* operator->() { return ptr; }
  T& operator*() { return *ptr; }
};


struct ICalc : public RefCountedObject
{
  virtual int add(int a, int b) = 0;
  virtual int sub(int a, int b) = 0;

  virtual ~ICalc() {}
};

// 객체를 생성하는 방법도 서버 개발자가 제공해주어야 한다.
// asInterface, CoCreateInstance

#include "ioacademy.h"
using namespace ioacademy;

// Ptr<ICalc>
static ICalc* CreateInstance()
{
  // 1. CalcProxy.dll을 로드 합니다.
  void* addr = IoLoadModule("CalcProxy.dll");

  // 2. Calc 객체 생성하는 함수를 찾아야 합니다.
  typedef ICalc*(*F)();
  F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

  // 3. Calc 객체 생성
  return f();
}