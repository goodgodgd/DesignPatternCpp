#include <iostream>
using namespace std;
// 3_RTTI
// 1. 개념: 실행 시간에 p가 정말로 어떤 객체를 가르키는지 조사하는 것
//    Run Time Type Information
// Java, C#: Reflection, ObjC: Instropection

// 2. 가상 함수 테이블로 관리되는 type_info를 사용하므로 가상 함수 테이블이
//    존재해야 제대로 동작한다.

class Animal 
{
public:
  virtual ~Animal() {}
};
class Dog : public Animal
{
public:
  int color;
};

void foo(Animal* p)
{
  // 다운 캐스팅
  // 1) static_cast: 컴파일 타임 캐스팅
  //  문제점: 잘못된 다운 캐스팅을 감지할 수 없다.
  // Dog* pDog = static_cast<Dog*>(p);
  //  장점: 캐스팅이 컴파일 타임에 수행되므로 성능 저하가 없다.
  //        의도한 설계가 의도한 자식만이 오도록 되어 있다면
  //        반드시 static_cast를 사용해야 한다.

  Dog* pDog = dynamic_cast<Dog*>(p);
  cout << pDog << endl;
  // pDog->color = 20;
  
  // 2) dynamic_cast: 런타임 캐스팅
  //  장점: 내부적으로 RTTI를 이용하여 구현되므로, 잘못된 다운 캐스팅을
  //        감지할 수 있다. 즉 잘못된 캐스팅은 NULL을 리턴한다.
  //  단점: 느리다. 꼭 필요할때만 사용해야 한다.
}

int main()
{
  Animal a; Dog d;
  foo(&a); foo(&d);
}




#if 1
void foo(Animal* p)
{
  cout << typeid(*p).name() << endl;
  // 어떤 이름을 출력할지에 대한 부분이 표준에 정의되어 있지 않습니다.

  // 실제로 타입을 조사할 땐 아래와 같이 사용하면 됩니다.
  if (typeid(*p) == typeid(Dog)) {
    //...
  }

  // 만약 p가 Dog라면 color에 접근하고 싶다.
  // 즉 클래스에 가상 함수가 존재하지 않는다면, 컴파일 시간에
  // p의 타입으로 type_info 구조체를 만드는 기계어 코드 생성한다.
  const type_info& t1 = typeid(*p);     // typeid(객체)
  const type_info& t2 = typeid(Dog);    // typeid(클래스)

                                        // 조사하고 싶다면
  if (t1 == t2)
    cout << "p는 Dog 입니다." << endl;
  else
    cout << "p는 Animal 입니다." << endl;
}
#endif

