// �ٽ�: A�� B�� ���� �ʹٸ� => ������ �θ� ������.
// upcasting: public ��Ӹ� �����ϴ�.
// public ���: �θ�Ŭ������ ��� ������ �������̽��� ���� �ްڴ�.
// ����� is a ���谡 ��Ȯ�ϰ� �����ؾ߸��ϰ� �׷��� ������ ������ ���� ���� ����.
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
	// �̷� ����� ������ �߰��� ������ vector�� �߰� �Ǿ�� �Ѵ�.
	vector<Dog> dogs;	// Dog�� ���� ����
	vector<Cat> cats;	// Cat�� ���� ����

	vector<Animal*> animals;	// ��� ����(Animal�� �ڽĵ�)�� ���� �����ϴ�.
	// upcasting ����: 'is a' ���� �����ϰ� public ����� ����!!
	// Dog is a Animal, Cat is a Animal
	Dog dog;
	Cat cat;
	Animal *p = &dog;
	// �Ʒ��� �ȵ�
//	Animal *p = &cat;
}

