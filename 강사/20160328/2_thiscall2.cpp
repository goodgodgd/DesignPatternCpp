// 2_thiscall2.cpp
#include <iostream>
using namespace std;

// http://d.pr/n/19aU4

class Sample
{
  int data;
public:
  void f1() // f1(Sample* this = 0) 
  { cout << "f1" << endl; }
  int f2()  // f2(Sample* this = 0)
  { cout << "f2" << endl; return 0; }

  // �Ʒ� �Լ��� �� ����������?
  int call_f3()
  {
    return this ? f3() : NULL;
  }

protected:
  int f3()  // f3(Sample* this = 0)
  {
    cout << "f3" << endl;
    return data;   // this->data �� �ǹǷ� error!
  }




};

int main()
{
  Sample* p = 0;  // �޸� �Ҵ��� �ϴٰ� �����ؼ� 0�� ���Դٰ�
                  // �����غ��ô�.
  
  p->f1();        // f1(p)
  p->f2();        // f2(p)
  // p->f3();
}