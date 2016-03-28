// ���� ������: C++���� �ִ� ����
// Java�� extended�� �����ϰ� public ��Ӱ� ����, private, protected ���� ����
// http://d.pr/n/12tp7

#include <iostream>
using namespace std;

class Base
{
	// ���� ������: private, protected, public
private:	// Base�� ���� ����
	int a;
protected:	// Base�� �� �ڽĸ� ���� ����
	int b;
public:		// ��� ���� ����
	int c;

};

// 1. �θ� Ŭ������ private ������ ������ ���� �ʽ��ϴ�.
// 2. protected ���
//	1) �θ��� protected	-> �ڽ��� protected
//	2) �θ��� public		-> �ڽ��� protected
// 3. private ���
//	1) �θ��� protected	-> �ڽ��� private
//	2) �θ��� public		-> �ڽ��� private

//				���� ������: private, protected, public
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
