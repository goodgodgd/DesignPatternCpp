
#include <iostream>
using namespace std;

// 이렇게 하면 Base의 소멸자 호출 -> 암것도 안나온다.
#if 0
class Base {};

class Derived : public Base
{
public:
	~Derived() { cout << "소멸자 호출" << endl; }
};

int main()
{
	Base* p = new Derived;
	delete p;
}
#endif

// 그래서 항상 부모에 가상함수 소멸자로 만들어준다.
#if 0
class Base 
{
public:
	virtual ~Base() {}
};

class Derived : public Base
{
public:
	virtual ~Derived() { cout << "소멸자 호출" << endl; }
};

int main()
{
	Base* p = new Derived;
	delete p;
}
#endif

// 그런데 가상함수를 쓰면 가상함수 테이블이란 비용이 있다.
// 가상함수 테이블 비용을 없애기 위해 template으로 타입을 정해서 파괴한다.
template <typename T>
class Base
{
	// 자식을 통해서만 호출하겠다.
protected:
	~Base() {}
public:
	void finalize()
	{
		// 자식의 타입으로 객체를 파괴한다.
		delete static_cast<T*>(this);
	}
};

class Derived : public Base<Derived>
{
public:
	~Derived() { cout << "소멸자 호출" << endl; }
};

int main()
{
	Base<Derived>* p = new Derived;
	p->finalize();
}
