// 6_�����Լ��� ����

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
// �Լ� ���ε�
//   p->cry() �� � �Լ��� ������ ���ΰ�?
// 1. static binding: ������ �ð��� �����Ϸ��� �����Ѵ�.
//                    p�� ������ Ÿ�����θ� �����ȴ�.
//  C, C++, C#, ������


// 2. dynamic binding: ������ �ð����� p�� �޸𸮸� �����ϴ� ���� �ڵ� ����
//                     ���� �ð����� �޸� ������ ȣ��
// Java, Objective-C, virtual, ��������� ������. �̼����̴�.








