// 3_캐스팅.cpp
#include <iostream>
using namespace std;

// http://d.pr/n/16nTT
// 1. C의 캐스팅은 비 이성적이다.
// 2. 그래서 C++ 4개의 캐스팅을 새로 제공합니다.
//   - static_cast: void* -> 다른 타입 또는 연관성 있는 캐스팅만 허용
//   - reinterpret_cast: 메모리 재해석, 거의 성공
//   - const_cast: 객체의 상수성, 휘발성 제거
//   - dynamic_cast: RTTI 기술, 다운 캐스팅 용도
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
  *p = 3.14; // 주의 해야 한다.
}
#endif
