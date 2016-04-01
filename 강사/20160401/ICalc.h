
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

  // ��¥ ������ó�� ������ �Ѵ�. ->, * �����ڸ� �������ؾ� �Ѵ�.
  // => ����Ʈ ������ �⺻
  T* operator->() { return ptr; }
  T& operator*() { return *ptr; }
};


struct ICalc : public RefCountedObject
{
  virtual int add(int a, int b) = 0;
  virtual int sub(int a, int b) = 0;

  virtual ~ICalc() {}
};

// ��ü�� �����ϴ� ����� ���� �����ڰ� �������־�� �Ѵ�.
// asInterface, CoCreateInstance

#include "ioacademy.h"
using namespace ioacademy;

// Ptr<ICalc>
static ICalc* CreateInstance()
{
  // 1. CalcProxy.dll�� �ε� �մϴ�.
  void* addr = IoLoadModule("CalcProxy.dll");

  // 2. Calc ��ü �����ϴ� �Լ��� ã�ƾ� �մϴ�.
  typedef ICalc*(*F)();
  F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

  // 3. Calc ��ü ����
  return f();
}