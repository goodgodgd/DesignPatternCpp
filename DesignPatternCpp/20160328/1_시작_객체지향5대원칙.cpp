// 1_시작.cpp

// 객체지향의 5대 원칙 - SOLID 원칙 (클린 코드 저자)
// 1. SRP - Single Responsibility Principle
//	: 모듈은 단 하나의 책임을 가져야 한다. 
//		하나의 책임이 여러 클래스에 분산되어 있다면 유지보수가 복잡해진다. (확산적 변경)
//		하나 이상의 책임을 가지면 요구사항 변경이 잦아서 코드가 너덜너덜해진다.
//		클래스 이름에 하나의 목적과 기대되는 결과가 명확하게 나타나야 한다.
// 2. OCP - Open Close Principle
//	: 모듈은 수정에는 닫혀 있고, 확장에는 열려 있어야 한다.
//		새로운 기능이 추가되어도 기존 모듈에는 수정이 발생하면 안 된다.
// 3. LSP - Liskov Substitution Principle
//	: 리스코프의 대체 원칙
//	: 자식 클래스는 부모 클래스를 대체 가능해야 한다. (다형성)
// 4. ISP - Interface Segregation Principle
//	: 인터페이스 분리 원칙 (인터페이스 단일 책임의 원칙)
//	: 구현하지 않고 명세(인터페이스)만 만들어 구현방식은 교체 가능한 유연한 디자인 만든다.
//		명세 또한 변경될 수 있으므로 여러 기능을 하나의 인터페이스로 만들지 말고 각각의 기능별로 분리해서 만들어야 한다.
// 5. DIP - Dependency Inversion Principle
//	: 의존 관계 역전 원칙
//	: 클라이언트는 구체 클래스에 의존하는 것이 아니라 인터페이스나 추상 클래스에 의존해야 한다. (느슨한 결합)
//		A 클래스가 B (구체) 클래스를 바로 사용하면 A를 가져갈 때 B도 항상 가져가야 한다. (강한 결합)

// 5대 원칙을 지키는 것이 좋지만 효율성이 떨어질 수도 있으므로 왜 안 써야 하는지 알고 안 쓰는것이 중요한다.
// 패턴의 지옥에 빠지지 말라. 패턴은 요구사항의 변경에 대응하기 위한 것이다.


#include <iostream>
using namespace std;

int main()
{
	cout << "Hello Design Pattern" << endl;
}

// http://d.pr/n/KULG

// 리팩토링 - 디자인 패턴으로 가능 과정
// 패턴화 과정
// 1. 요구 사항의 변경을 예측하고 미리 패턴을 적용한 디자인
// 2. 단순하게 설계 후, 요구 사항 변경이 발생할 경우 패턴을 적용 (리팩토링)


//-GoF 23가지 패턴 중 22가지 - 20년 지났어
//- C++ Idioms: c++ 언어적 특성을 이용한 설계 : 최근 오픈소스 이해에 패턴보다 더 중요
//- Idiom 위해 기초 / 고급 문법이해 필요
//- C++98 / 03 (1.0), C++11 / 14 (2.0), C++17 (3.0)
//- g++ 4.8 (ubuntu 14) 이상이면 11 / 14지원 옵션은 걸어야
//- visual studio 2013 : 11 / 14 지원
//- visual studio 2015 community 사용 추천
//- LLVM clang : 가장 최신 기능을 가장 정확하게 지원하는 컴파일러
//
