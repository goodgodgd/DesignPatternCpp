// 7_����Ҹ���

// Inside C++ Object - ���ĸ� ����

#include <iostream>
using namespace std;
// http://d.pr/n/1lDeC
// 1. �θ� Ŭ������ �Ҹ��ڰ� ���� �Լ��̸�, ��� �ڽ��� �Ҹ��ڵ� �����Լ��̴�.
// 2. ��� �θ� Ŭ������ �Ҹ��ڴ� �ݵ�� ���� �Լ��̾�� �Ѵ�.
class Base
{
public:
  virtual ~Base() {}
};

class Derived : public Base
{
public:
  Derived()  { cout << "�ڿ� �Ҵ�" << endl; }
  ~Derived() { cout << "�ڿ� ����" << endl; }
};

int main()
{
  Base* p = new Derived;
  delete p;

  // Derived d;
}