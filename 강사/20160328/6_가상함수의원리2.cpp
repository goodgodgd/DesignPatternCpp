#include <iostream>
using namespace std;
// 6_가상함수의원리2

class Animal 
{
  int age;
public:
 virtual void cry() { cout << "Animal cry" << endl; }
 virtual void foo() {}
 virtual void goo() {}

};

class Dog : public Animal
{
  int color;
public:
  virtual void cry() { cout << "Dog cry" << endl; }
  virtual void foo() {}
};
// http://d.pr/n/1kdfb
int main()
{
  Animal a; Dog d;
  cout << sizeof(a) << endl;
  cout << sizeof(d) << endl;


  Animal* p = &d;
  p->cry();       // 이 순간의 정확한 원리를 생각해 봅시다.
  // (*p)[0](p);
}
