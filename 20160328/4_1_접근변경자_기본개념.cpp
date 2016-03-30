// 접근 변경자: C++에만 있는 문법
// Java는 extended로 접근하고 public 상속과 동일, private, protected 접근 없음
// http://d.pr/n/12tp7

#include <iostream>
using namespace std;

class Base
{
	// 접근 지정자: private, protected, public
private:	// Base만 접근 가능
	int a;
protected:	// Base와 그 자식만 접근 가능
	int b;
public:		// 모두 접근 가능
	int c;

};

// 1. 부모 클래스의 private 접근은 영향을 받지 않습니다.
// 2. protected 상속
//	1) 부모의 protected	-> 자식의 protected
//	2) 부모의 public		-> 자식의 protected
// 3. private 상속
//	1) 부모의 protected	-> 자식의 private
//	2) 부모의 public		-> 자식의 private

//				접근 변경자: private, protected, public
class Derived : public Base
{

};

int main()
{
	Base b;
	b.c = 10;
	Derived d;
	d.c = 10;
}
