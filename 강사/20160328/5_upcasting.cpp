// 5_upcasting
#include <iostream>
using namespace std;
#include <vector>

// http://d.pr/n/1fGMX
// upcasting: public 상속만 가능하다.

// 핵심: A와 B를 묶고 싶다면 => 공통의 부모를 만들어라.
class Animal {};

class Dog : public Animal {
};

class Cat : private Animal {
};

int main()
{
  Dog dog; Cat cat;
  Animal* p = &cat;

  vector<Animal*> animals; // 모든 동물(Animal의 자식들)을 저장 가능하다.

  vector<Dog> dogs;   // Dog만 저장 가능
  vector<Cat> cats;   // Cat만 저장 가능
}







