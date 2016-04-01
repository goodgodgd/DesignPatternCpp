// 8_메뉴이벤트7
#include <iostream>
using namespace std;

class Dialog
{
public:
  void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

#include <functional> 
// 이미 표준에 범용적 함수 포인터가 있습니다.
// TR1 - 2008년도에 추가되었습니다.

void goo(int n)        { printf("goo: %d\n", n);       }
void hoo(int a, int b) { printf("hoo: %d %d\n", a, b); }
void koo(int a, int b, int c, int d)
{
  printf("koo: %d %d %d %d\n", a, b, c, d);
}

using namespace std::placeholders;

int main()
{
  function<void(int, int)> f;

  f = bind(&koo, _2, _1, _1, _2);
  f(10, 20);
}


#if 0
int main()
{
  function<void(int)> f = &goo;
  f(10);

  f = bind(&hoo, 10, _1);
  f(300);

  f = bind(&koo, 10, _1, 30, _1);
  f(20);
}
#endif


#if 0
int main()
{
  function<void()> f = &foo;
  f();

  f = bind(&goo, 10);
  f = bind(&hoo, 10, 20);
  f = bind(&koo, 10, 20, 30, 40);

  f();
}
#endif




#if 0
int main()
{
  function<void()> f = &foo;
  f();

  Dialog dialog;
  f = bind(&Dialog::close, &dialog);
  f();
}
#endif


// 가실때 출석부 서명해주세요.












