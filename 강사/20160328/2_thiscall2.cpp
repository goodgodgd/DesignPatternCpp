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

  // 아래 함수는 왜 만들었을까요?
  int call_f3()
  {
    return this ? f3() : NULL;
  }

protected:
  int f3()  // f3(Sample* this = 0)
  {
    cout << "f3" << endl;
    return data;   // this->data 가 되므로 error!
  }




};

int main()
{
  Sample* p = 0;  // 메모리 할당을 하다가 실패해서 0이 나왔다고
                  // 가정해봅시다.
  
  p->f1();        // f1(p)
  p->f2();        // f2(p)
  // p->f3();
}