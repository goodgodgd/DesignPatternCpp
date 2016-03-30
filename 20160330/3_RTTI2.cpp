// C++�� ���� �����ӿ�ũ���� ��ü������ RTTI�� ������ ���� �����ؼ� ����ϰ� �ֽ��ϴ�.
// MFC, Qt, Android ...

// ��ü�� Ŭ������ ������ ������ �����ؾ� �Ѵٸ� -> ���� ���� static int a;
// RTTI�� �ٽ��� type_info�Դϴ�. => ���� ��� ����
#include <iostream>
#include <string>
using namespace std;

struct CRuntimeClass
{
	string name;
	// �ϱ⿡ ���� �߰����� ������ ���� �� �ִ�.
};

// �������� ��� Ŭ������ �Ʒ� ��Ģ�� ���Ѿ� �մϴ�.
// 1. ��� Ŭ�������� ���� ��� ������ CRuntimeClass �� �־�� �Ѵ�.
// 2. ���� �̸��� "classŬ�����̸�" ���� �Ѵ�.
// 3. ���� ������ �����ϴ� �����Լ� GetRuntimeClass()�� �־�� �Ѵ�.

class Animal
{
public:
	static CRuntimeClass classAnimal;
	virtual CRuntimeClass* GetRuntimeClass()
	{
		return &classAnimal; 
	}
};

CRuntimeClass Animal::classAnimal = { "Animal" };

class Dog : public Animal
{
public:
	static CRuntimeClass classDog;
	virtual CRuntimeClass* GetRuntimeClasss()
	{ return &classDog; }
};

CRuntimeClass Dog::classDog = { "Dog" };

void foo(Animal* p)
{
	if (p->GetRuntimeClass() == &Dog::classDog)
		cout << "p�� Dog�Դϴ�." << endl;
}

// �̷��� ¥�� ���� �ѵ� ������ ������.
// �����ӿ�ũ���� ���ϰ� ������ ��ũ�� ������ -> ����

int main()
{
	Dog dog;
	foo(&dog);
}

