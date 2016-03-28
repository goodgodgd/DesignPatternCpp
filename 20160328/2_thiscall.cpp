// ��ǥ: ��ü�� �Լ� ���� ���� ����
// http://d.pr/n/1kzQ7

#include <iostream>
using namespace std;

class Point
{
	// field, member variable
	int x, y;
public:
	// member function, method
	void set(int a, int b)	// function signature: void set(Point* const this, int a, int b)
	{
		x = a;	// this->x = a;
		y = b;	// this->y = b;
	}

	// static method, class method
	static void foo(int a)	// function signature: void foo(int a)
	{
//		x = a;	// this->x = a; �� �Ǿ�� �ϴ� this�� ����!
	}
};

int main()
{
	Point p1, p2;
	// p1�� ��� �Լ��� ��ó�� �������� set �Լ��� ��� ��ü�� �����ǰ�
	// set(&p1, 10, 20) �̶�� ������ ��, ��ü ���ο��� �θ��°� �ƴ϶� ��ü�� �޸𸮸� �Լ� ���ڷ� ����
	// push 20
	// push 10
	// mov ecx (&p1 ����)
	// call set
	p1.set(10, 20);

	Point::foo(10);	// ���� ��� �Լ��� ��ü ���� ȣ�� �����ϴ�. -> this�� ���޵��� �ʴ´�.
}
