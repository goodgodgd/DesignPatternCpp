// 3_ĳ����.cpp
#include <iostream>
using namespace std;

// http://d.pr/n/16nTT
// 1. C�� ĳ������ �� �̼����̴�.
// 2. �׷��� C++ 4���� ĳ������ ���� �����մϴ�.
//   - static_cast: void* -> �ٸ� Ÿ�� �Ǵ� ������ �ִ� ĳ���ø� ���
//   - reinterpret_cast: �޸� ���ؼ�, ���� ����
//   - const_cast: ��ü�� �����, �ֹ߼� ����
//   - dynamic_cast: RTTI ���, �ٿ� ĳ���� �뵵
int main()
{
  volatile int c = 10;

  // int* p = static_cast<int*>(&c);
  int* p = const_cast<int*>(&c);
  *p = 20;

  cout << *p << endl;
  cout << c << endl;
}



#if 0
int main()
{
  // int *p1 = (int*)malloc(sizeof(100));
  int *p1 = static_cast<int*>(malloc(sizeof(100)));

  int n = 0;
  // double* p = static_cast<double*>(&n);
  double* p = reinterpret_cast<double*>(&n);
  *p = 3.14; // ���� �ؾ� �Ѵ�.
}
#endif
