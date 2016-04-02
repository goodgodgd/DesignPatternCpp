// 핵심: A와 B를 묶고 싶다면 => 공통의 부모를 만들어라.
// upcasting: public 상속만 가능하다.
// public 상속: 부모클래스의 모든 구현과 인터페이스를 물려 받겠다.
// 상속은 is a 관계가 명확하게 성립해야만하고 그렇지 않으면 포함을 쓰는 것이 낫다.
// http://d.pr/n/1fGMX

#include <vector>
#include <iostream>
using namespace std;

class Animal {};

class Dog : public Animal {

};

class Cat : private Animal {

};

int main()
{
	// 이런 방법은 동물이 추가될 때마다 vector도 추가 되어야 한다.
	vector<Dog> dogs;	// Dog만 저장 가능
	vector<Cat> cats;	// Cat만 저장 가능

	vector<Animal*> animals;	// 모든 동물(Animal의 자식들)을 저장 가능하다.
	// upcasting 가능: 'is a' 관계 성립하고 public 상속일 때만!!
	// Dog is a Animal, Cat is a Animal
	Dog dog;
	Cat cat;
	Animal *p = &dog;
	// 아래는 안돼
//	Animal *p = &cat;
}

