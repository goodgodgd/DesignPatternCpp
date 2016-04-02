// 가상함수의 원리
// virtual 키워드가 정적 바인딩을 동적 바인딩으로 바꾼다.
#include <iostream>
using namespace std;

class Animal
{
public:
	//void cry()	{ cout << "Animal cry" << endl; }
	// virtual 키워드는 정적 바인딩을 동적 바인딩으로 바꿔준다.
	virtual void cry()	{ cout << "Animal cry" << endl; }
};

class Dog : public Animal
{
public:
	// 오버라이딩
	void cry()	{ cout << "Dog cry" << endl; }
};

int main()
{
	Animal a;
	a.cry();	// Animal cry
	Dog d;
	d.cry();	// Dog cry

	Animal* p = &d;
	p->cry();	// Animal cry() 가 비 가상 함수면: 정적 바인딩 -> Animal cry 출력
				// Animal cry() 가 가상 함수면	 : 동적 바인딩 -> Dog cry 출력
}

// 함수 바인딩
// p->cry() 를 어떤 함수로 연결할 것인가?

// 1. static binding:	컴파일 시 컴파일러가 결정
//						p의 포인터 타입으로만 결정한다.
//						C, C++, C# 기본 바인딩 방식, 빠르다, 컴파일러 최적화 가능, 비 이성적이다. virtual 키워드 제공

// 2. dynamic binding:	컴파일 시 p의 메모리를 조사하는 기계어 코드 생성
//						실행 시간에는 메모리 조사 후 호출
//						Java, Objective-C, "상대적으로" 느리다, 이성적이다.

// C++, 특히 C# 은 최신 기술들을 적극적으로 도입하고 있다. C++11/14는 기존 C++09와는 완전히 다르다. C++09는 C에서 클래스만 추가된 느낌 추상화 덜 됨
// Java는 maintainer가 새로운 기능을 받아들이는 것에 대해 비판적이었는데 최근 maintainer가 바뀌어서 최신 기술 도입 중이다.
