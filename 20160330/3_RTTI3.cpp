// C++의 많은 프레임워크들이 자체적으로 RTTI의 개념을 직접 구현해서 사용하고 있습니다.
// MFC, Qt, Android ...
// Reflection => 문자열 => 객체생성

// 객체와 클래스가 동일한 변수를 공유해야 한다면 -> 정적 변수 static int a;
// RTTI의 핷미은 type_info입니다. => 정적 멤버 변수

#include <iostream>
#include <string>
using namespace std;

struct CRuntimeClass
{
	string name;
	// 하기에 따라 추가적인 정보를 넣을 수 있다.
};

// 이제부터 모든 클래스는 아래 규칙을 지켜야 합니다.
// 1. 모든 클래스에는 정적 멤버 변수인 CRuntimeClass 가 있어야 한다.
// 2. 변수 이름은 "class클래스이름" 으로 한다.
// 3. 정적 변수를 리턴하는 가상함수 GetRuntimeClass()가 있어야 한다.

// 매크로 문법
// 1. ## : 토큰 잇기
// 2. # : 토큰 문자열화

// 이중으로 매크로 함수를 제공해야 한다.
// => 매크로 치환과 같이 사용하기 위함읻.
// => Linux Kernel 에서 MODULE_LICENSE 매크로를 분석하면 됩니다.


// 이제 매크로로 구현해보자!!
// 위 규칙을 매크로화 합니다.

// ## : 매크로에서 토큰을 이어준다.!!
/*
#define DECLARE_DYNAMIC(classname)					\
	public:											\
	static CRuntimeClass class##className;			\
	virtual CRuntimeClass* GetRuntimeClass();

// # : 토큰을 문자열로 바꿔준다.
#define IMPLEMENT_DYNAMIC(classname)							\
	CRuntimeClass classname::class##classname = { #classname };	\
	CRuntimeClass* classname::GetRuntimeClass()					\
	{ return &class##classname; }

// 클래스 이름으로 static 변수인 RuntimeClass 얻는 매크로
#define RUNTIME_CLASS(classname)		&(class::class##classname)
*/

#define DECLARE_DYNAMIC(classname)                                \
  public:                                                         \
  static CRuntimeClass class##classname;                          \
  virtual CRuntimeClass* GetRuntimeClass();

#define IMPLEMENT_DYNAMIC(classname)                              \
  CRuntimeClass classname::class##classname = { #classname };     \
  CRuntimeClass* classname::GetRuntimeClass()                     \
  { return &class##classname; }

// 클래스 이름으로 static 변수인 RuntimeClass 얻는 매크로
#define RUNTIME_CLASS(classname)    &(classname::class##classname)


class Animal
{
	DECLARE_DYNAMIC(Animal);
};
IMPLEMENT_DYNAMIC(Animal)

class Dog : public Animal
{
	DECLARE_DYNAMIC(Dog);
};
IMPLEMENT_DYNAMIC(Dog)

//---------------------------------------------

void foo(Animal* p)
{
	if (p->GetRuntimeClass() == RUNTIME_CLASS(Dog))
		cout << "p는 Dog입니다." << endl;
	if (p->GetRuntimeClass() == RUNTIME_CLASS(Animal))
		cout << "p는 Animal입니다." << endl;
}

int main()
{
	Animal ani;
	foo(&ani);
	Dog dog;
	foo(&dog);
}
