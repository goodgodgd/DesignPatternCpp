// http://d.pr/n/19UjG

#include <iostream>
using namespace std;

class A
{
	int a;
public:
	virtual void foo() { cout << "A foo" << endl; }
};

class B
{
	int b;
public:
	virtual void goo() { cout << "B goo" << endl; }
};

int main()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();	// 어떻게 나올까?
	// 정적 바인딩인 경우 "B goo"
	// 동적 바인딩인 경우 "A foo", foo()와 goo() 모두 가상함수인 경우, A::foo()에 연결된 vfptr에 접근한다.

	// 둘다 비가상: B goo
	// B만 가상: 실행 에러
	// A만 가상: B goo
	// 둘다 가상: A foo

}
