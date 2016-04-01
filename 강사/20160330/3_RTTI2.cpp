#include <iostream>
#include <string>
using namespace std;
// 3_RTTI2
// C++의 많은 프레임워크들이 자체적으로 RTTI의 개념을 
// 직접 구현해서 사용하고 있습니다.
// MFC, Qt, Android ...

// 객체와 클래스가 동일한 변수를 공유해야 한다면 -> 정적 멤버 변수

// RTTI의 핵심은 type_info입니다. => 정적 멤버 변수
struct CRuntimeClass
{
  string name;
  string author;
  string version;
};

// 이제부터 모든 클래스는 아래 규칙을 지켜야 합니다.
// 1. 모든 클래스에는 정적 멤버 변수인 CRuntimeClass 가 있어야 한다.
// 2. 변수 이름은 "class클래스이름" 으로 한다.
// 3. 정적 변수를 리턴하는 가상함수 GetRuntimeClass()가 있어야 한다.
class Animal
{
public:
  static CRuntimeClass classAnimal;
  virtual CRuntimeClass* GetRuntimClass()
  { return &classAnimal; }
};

CRuntimeClass Animal::classAnimal = { "Animal" };

class Dog : public Animal
{
public:
  static CRuntimeClass classDog;
  virtual CRuntimeClass* GetRuntimClass()
  { return &classDog; }
};

CRuntimeClass Dog::classDog = { "Dog" };

void foo(Animal* p)
{
  if (p->GetRuntimClass() == &Dog::classDog)
    cout << "p는 Dog입니다. " << endl;
}


int main()
{
  Animal a; Dog d;
  foo(&a); foo(&d);
}
