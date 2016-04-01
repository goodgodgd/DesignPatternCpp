// http://d.pr/n/13fsR

// 1_시작.cpp
// 객체지향의 5대 원칙 - SOLID 원칙
// 1. SRP - Single Responsiblity Principle
//    : 모듈은 단 하나의 책임을 가져야 한다.
// 2. OCP - Open Close Principle
//    : 모듈은 수정에는 닫혀 있고, 확장에는 열려 있어야 한다.
//    : 새로운 기능이 추가되어도, 기존 모듈에는 수정이 발생하면 안된다.
// 3. LSP - Liskov Substitution Principle
//    : 리스코프의 대체 원칙
//    : 자식 클래스는 부모 클래스로 대체 가능해야 한다. - 다형성
// 4. ISP - Interface Segregation Principle
//    : 인터페이스 분리 법칙
//    : 범용 인터페이스 보다는 세분화된 인터페이스가 낫다.
// 5. DIP - Dependeny Inversion Principle
//    : 의존 관계 역전 원칙
//    : 클라이언트는 구체 클래스에 의존하는 것이 아니라
//      인터페이스나 추상 클래스에 의존해야 한다.

#include <iostream>
using namespace std;

int main()
{
  cout << "Hello Design Pattern" << endl;
}

// Compile: ctrl + F7
// Compile + Run: Ctrl + F5


// http://d.pr/n/KULG

// 리팩토링
// 1. 요구 사항의 변경을 예측하고 미리 패턴을 적용한 디자인
// 2. 단순하게 설계 후, 요구 사항 변경이 발생할 경우 패턴을 적용
