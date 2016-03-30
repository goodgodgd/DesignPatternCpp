// RTTI
// 1. 개념: 실행 시간에 p가 정말로 어떤 객체를 가리키는지 조사하는 것
//		Run Time Type Information (객체 타입 조사)
//		Java, C#: Reflection, ObjC: Instropection - C++보다 다양한 기능 제공
// 2. 가상함수 테이블로 관리되는 type_info를 사용하므로 가상함수 테이블이 존재해야 제대로 동작한다.

#include <iostream>
using namespace std;

class Animal 
{
public:
	// 가상함수가 있어야 가상함수 테이블이 만들어지고 type info 볼수 있다.
	virtual ~Animal() {}
};

class Dog : public Animal
{
public:
	int color;
};

// 만약 p가 Dog라면 color에 접근하고 싶다.
// sizeof(*p)는 1이 나온다. C++에서 empty object의 크기는 1, 객체는 존재해야 한다.
// Dog { Animal 1byte + color 4byte }
// Animal을 Dog로 다운캐스팅할 때 원래 Animal이었다면 color 접근시 에러
// 타입확인 필요
// 클래스에 가상 함수가 존재하지 않는다면, 컴파일 시간에
// p의 타입으로 type_info 구조체를 만드는 기계어 코드를 생성한다.

#if 0
void foo(Animal* p)
{
	const type_info& t1 = typeid(*p);		// typeid(객체)
	const type_info& t2 = typeid(Dog);		// typeid(클래스)

	// 조사하고 싶다면
	if (t1 == t2)
		cout << "p는 Dog 입니다." << endl;
	else
		cout << "p는 Animal 입니다." << endl;

	// 실제 타입을 조사할 때 아래와 같이 사용하면 됩니다.
	if (typeid(*p) == typeid(Dog))
	{
		;
	}

	// 객체 이름도 볼 수 있다.
	cout << typeid(*p).name() << endl;
	// 그럼 이름을 이용한 동적 생성도 가능하지 않을까??
	// 어떤 이름을 출력할지에 대한 부분이 표준에 정의되어 있지 않다. 프레임워크, 컴파일러마다 다르다.
	// 그래서 안드로이드나 등에서는 자체적으로 만들어 사용

}

int main()
{
	Animal a;
	Dog d;
	foo(&a);
	foo(&d);
}
#endif

// 어쨌든 color에 접근하려면 다운 캐스팅을 해야한다.
void foo(Animal* p)
{
	// 다운 캐스팅
	//	1) static_cast	: 컴파일 타임 캐스팅
	//		문제점: 잘못된 다운 캐스팅을 감지할 수 없다.
	//		장점: 캐스팅이 컴파일 타임에 수행되므로 성능 저하가 없다.
	//			의도한 설계가 의도한 자식만이 오도록 되어 이다면
	//			반드시 static_cast를 사용해야 한다.

//	Dog* pDog = static_cast<Dog*>(p);
//	pDog->color = 20;
//	cout << pDog << endl;

	//	2) dynamic_cast	: 런타임 캐스팅
	//		장점: 내부적으로 RTTI를 이용하여 구현되므로, 잘못된 다운 캐스팅을 감지할 수 있다.
	//			즉 잘못된 캐스팅은 NULL을 리턴한다.
	//		단점: 느리다. 꼭 필요할때만 사용한다.
	
	// p가 Animal 이면 0 나온다.
	Dog* pDog1 = dynamic_cast<Dog*>(p);
	cout << pDog1 << endl;

	// 그런데 다형성 타입은 안된다. ???
	Animal* pAni = dynamic_cast<Animal*>(p);
}

int main()
{
	Animal a;
	Dog d;
	foo(&a);
	foo(&d);
}
