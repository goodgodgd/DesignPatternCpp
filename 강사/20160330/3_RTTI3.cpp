// 3_RTTI3
#include <iostream>
#include <string>
using namespace std;

struct CRuntimeClass
{
  string name;
  string author;
  string version;
};

#define AAA XXX

// 매크로 문법
// 1. ##: 토큰 잇기
// 2. # : 토큰 문자열화

// 이중으로 매크로 함수를 제공해야 한다.
// => 매크로 치환과 같이 사용하기 위함이다.
// => Linux Kernel
// => MODULE_LINCENSE 매크로를 분석하면 됩니다.

// 이제부터 모든 클래스는 아래 규칙을 지켜야 합니다.
// 1. 모든 클래스에는 정적 멤버 변수인 CRuntimeClass 가 있어야 한다.
// 2. 변수 이름은 "class클래스이름" 으로 한다.
// 3. 정적 변수를 리턴하는 가상함수 GetRuntimeClass()가 있어야 한다.
// 위 규칙을 매크로화 합니다.
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

//-------------------------------

class Animal
{
  DECLARE_DYNAMIC(Animal)
};
IMPLEMENT_DYNAMIC(Animal)

class Dog : public Animal
{
  DECLARE_DYNAMIC(Dog)
};
IMPLEMENT_DYNAMIC(Dog)


void foo(Animal* p)
{
  if (p->GetRuntimeClass() == RUNTIME_CLASS(Dog))
    cout << "p는 Dog입니다. " << endl;
}
int main()
{
  Animal a; Dog d;
  foo(&a); foo(&d);
}
