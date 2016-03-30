// RTTI
// 1. ����: ���� �ð��� p�� ������ � ��ü�� ����Ű���� �����ϴ� ��
//		Run Time Type Information (��ü Ÿ�� ����)
//		Java, C#: Reflection, ObjC: Instropection - C++���� �پ��� ��� ����
// 2. �����Լ� ���̺�� �����Ǵ� type_info�� ����ϹǷ� �����Լ� ���̺��� �����ؾ� ����� �����Ѵ�.

#include <iostream>
using namespace std;

class Animal 
{
public:
	// �����Լ��� �־�� �����Լ� ���̺��� ��������� type info ���� �ִ�.
	virtual ~Animal() {}
};

class Dog : public Animal
{
public:
	int color;
};

// ���� p�� Dog��� color�� �����ϰ� �ʹ�.
// sizeof(*p)�� 1�� ���´�. C++���� empty object�� ũ��� 1, ��ü�� �����ؾ� �Ѵ�.
// Dog { Animal 1byte + color 4byte }
// Animal�� Dog�� �ٿ�ĳ������ �� ���� Animal�̾��ٸ� color ���ٽ� ����
// Ÿ��Ȯ�� �ʿ�
// Ŭ������ ���� �Լ��� �������� �ʴ´ٸ�, ������ �ð���
// p�� Ÿ������ type_info ����ü�� ����� ���� �ڵ带 �����Ѵ�.

#if 0
void foo(Animal* p)
{
	const type_info& t1 = typeid(*p);		// typeid(��ü)
	const type_info& t2 = typeid(Dog);		// typeid(Ŭ����)

	// �����ϰ� �ʹٸ�
	if (t1 == t2)
		cout << "p�� Dog �Դϴ�." << endl;
	else
		cout << "p�� Animal �Դϴ�." << endl;

	// ���� Ÿ���� ������ �� �Ʒ��� ���� ����ϸ� �˴ϴ�.
	if (typeid(*p) == typeid(Dog))
	{
		;
	}

	// ��ü �̸��� �� �� �ִ�.
	cout << typeid(*p).name() << endl;
	// �׷� �̸��� �̿��� ���� ������ �������� ������??
	// � �̸��� ��������� ���� �κ��� ǥ�ؿ� ���ǵǾ� ���� �ʴ�. �����ӿ�ũ, �����Ϸ����� �ٸ���.
	// �׷��� �ȵ���̵峪 ����� ��ü������ ����� ���

}

int main()
{
	Animal a;
	Dog d;
	foo(&a);
	foo(&d);
}
#endif

// ��·�� color�� �����Ϸ��� �ٿ� ĳ������ �ؾ��Ѵ�.
void foo(Animal* p)
{
	// �ٿ� ĳ����
	//	1) static_cast	: ������ Ÿ�� ĳ����
	//		������: �߸��� �ٿ� ĳ������ ������ �� ����.
	//		����: ĳ������ ������ Ÿ�ӿ� ����ǹǷ� ���� ���ϰ� ����.
	//			�ǵ��� ���谡 �ǵ��� �ڽĸ��� ������ �Ǿ� �̴ٸ�
	//			�ݵ�� static_cast�� ����ؾ� �Ѵ�.

//	Dog* pDog = static_cast<Dog*>(p);
//	pDog->color = 20;
//	cout << pDog << endl;

	//	2) dynamic_cast	: ��Ÿ�� ĳ����
	//		����: ���������� RTTI�� �̿��Ͽ� �����ǹǷ�, �߸��� �ٿ� ĳ������ ������ �� �ִ�.
	//			�� �߸��� ĳ������ NULL�� �����Ѵ�.
	//		����: ������. �� �ʿ��Ҷ��� ����Ѵ�.
	
	// p�� Animal �̸� 0 ���´�.
	Dog* pDog1 = dynamic_cast<Dog*>(p);
	cout << pDog1 << endl;

	// �׷��� ������ Ÿ���� �ȵȴ�. ???
	Animal* pAni = dynamic_cast<Animal*>(p);
}

int main()
{
	Animal a;
	Dog d;
	foo(&a);
	foo(&d);
}
