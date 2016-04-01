// 6_가상함수의 원리

#include <iostream>
using namespace std;

class Animal
{
public:
  virtual void cry() { cout << "Animal cry" << endl; }
};

class Dog : public Animal
{
public:
  void cry() { cout << "Dog cry" << endl; }
};

int main()
{
  Animal a;     a.cry();
  Dog d;        d.cry();

  Animal* p = &d;
  p->cry();      // ?

  
}

// http://d.pr/n/1hiBS
// 함수 바인딩
//   p->cry() 를 어떤 함수로 연결할 것인가?
// 1. static binding: 컴파일 시간에 컴파일러가 결정한다.
//                    p의 포인터 타입으로만 결정된다.
//  C, C++, C#, 빠르다


// 2. dynamic binding: 컴파일 시간에는 p의 메모리를 조사하는 기계어 코드 생성
//                     실행 시간에는 메모리 조사후 호출
// Java, Objective-C, virtual, 상대적으로 느리다. 이성적이다.








