// 4_���ٺ�����.cpp
#include <iostream>
using namespace std;

class Base
{
  // ���� ������
private:   int a;
protected: int b;
public:    int c;
};

// http://d.pr/n/12tp7
// 1. �θ� Ŭ������ private ������ ������ ���� �ʽ��ϴ�.
// 2. protected ���
//   1) protected -> protected
//   2) public    -> protected
// 3. private ���
//   1) protected -> private
//   2) public    -> private

            // : <���� ������> Base
class Derived : private Base
{
};

int main()
{
  // Base b;    b.c = 10;
  Derived d; d.c = 10;
}




