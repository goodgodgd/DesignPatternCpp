#include <iostream>
using namespace std;

// http://d.pr/n/10pCB
// ����Ʈ ����: ������ �ð��� �����ȴ�.
// ���� �Լ�: ���� �ð��� �����ȴ�.

// 1. �����Լ������� �ǵ����̸� ����Ʈ ���ڸ� ������� ����.
// 2. ����ߴٸ� �������� �� ���� �������� ����.
class A
{
public:
  virtual void foo(int a = 10) 
  { cout << "A: " << a << endl; }
};

class B : public A   // ���� ����Դϴ�.
{
public:
  virtual void foo(int a = 20)
  { cout << "B: " << a << endl; }
};
// http://d.pr/n/1kmqW
int main()
{
  A* p = new B;
  p->foo();       // ���� ��� �����غ�����.
}