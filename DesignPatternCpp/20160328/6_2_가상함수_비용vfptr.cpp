// 가상함수의 비용을 이해하자.
// 가상함수를 사용하는 클래스가 있으면 클래스 밖에 가상함수 테이블을 운용해야 한다.
// 가상함수 하나당 테이블에 포인터 하나씩 메모리 사용이 늘어나기 때문에 감안해서 써야한다.

// http://d.pr/n/1kdfb

#include <iostream>
using namespace std;

class Animal
{
	int age;
public:
	virtual void cry() { cout << "Animal cry" << endl; }
	virtual void foo() {}
	virtual void goo() {}
};

// Animal 객체는 age란 변수와 함께 vfptr을 가지고 있다.
// Animal 객체의 가상함수가 Animal의 함수를 가리키는지 상속받은 Dog의 함수를 가리키는지는 각 객체마다 다르기 때문에
// 그것을 저장할 포인터 vfptr이 필요하다.

class Dog : public Animal
{
	int color;
public:
	// virtual을 쓰지 않아도 내부적으로 virtual로 인식하지만 가독성을 위해 virtual을 써주는 것이 좋다.
	virtual void cry() { cout << "Dog cry" << endl; }
};

int main()
{
	Dog d;
	Animal* p = &d;
	p->cry();	// 이 순간의 정확한 원리를 생각해 봅시다.
	// (*p)[0](p);	// 실제 구현방법, (*p)[0]==vfptr 가상함수 테이블에 연결된 포인터

	Animal a;
	cout << sizeof(a) << endl;	// 8 => age 외에도 vfptr 포함하기 때문, 64 bit면 
	cout << sizeof(d) << endl;	// 12 => age + color + vfptr
}
