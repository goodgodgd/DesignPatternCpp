	
#include <iostream>
using namespace std;

class RefCountedObject
{
	int mCount;
public:
	RefCountedObject() : mCount(0) { cout << "객체 생성" << endl; }
	virtual ~RefCountedObject() { cout << "객체 파괴" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// 참조계수가 0되면 자신 파괴
			delete this;
	}

};

struct ICalc : RefCountedObject
{
	virtual int add(int a, int b) = 0;
	virtual int sub(int a, int b) = 0;

	virtual ~ICalc() {}
};

// 스마트 포인터
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p) { ptr->addRef(); }	// 규칙 1.
	Ptr(const Ptr& p) : ptr(p.ptr)
	{
		ptr->addRef();
	}								// 규칙 2.
	~Ptr() { ptr->release(); }					// 규칙 3.

												// 진짜 포인터처럼 보여야 한다. ->, * 연산자를 재정의해야 한다.
												// => 스마트 포인터 기본
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
};

#include "ioacademy.h"
using namespace ioacademy;

// 객체를 생성하는 방법도 서버 개발자가 제공해줘야 한다.
// 안드로이드: asInterface, MS COM: CoCreateInstance
// Ptr<ICalc> 리턴 타입을 이렇게 쓰면 사용자가 스마트포인터를 쓰게 강제할 수 있다.
static ICalc* CreateInstance()
{
	// 1. CalcProxy.dll을 로드 합니다.
	void* addr = IoLoadModule("CalcProxy.dll");

	// 2. 객체를 생성하는 함수를 찾아야 합니다.
	typedef ICalc*(*F)();	// 멤버 함수 포인터
	F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

	// 3. Calc 객체 생성
	return f();
}
