// 5_upcasting
#include <iostream>
using namespace std;
#include <vector>

// http://d.pr/n/1fGMX
// upcasting: public ��Ӹ� �����ϴ�.

// �ٽ�: A�� B�� ���� �ʹٸ� => ������ �θ� ������.
class Animal {};

class Dog : public Animal {
};

class Cat : private Animal {
};

int main()
{
  Dog dog; Cat cat;
  Animal* p = &cat;

  vector<Animal*> animals; // ��� ����(Animal�� �ڽĵ�)�� ���� �����ϴ�.

  vector<Dog> dogs;   // Dog�� ���� ����
  vector<Cat> cats;   // Cat�� ���� ����
}







