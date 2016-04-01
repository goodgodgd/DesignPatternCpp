#include <iostream>
using namespace std;

// 일반적 프로그래밍
// C++ 라이브러리를 이해하기 위해서는 일반화를 이해 해야 합니다.
// C++ - OOP + 일반화(Generic)

// C의 문자열 함수
char* xstrchr(char *s, char c)
{
  while (*s != '\0' && *s != c)
    ++s;

  return *s == c ? s : NULL;
}

// 1. 검색 구간의 일반화 : 부분 문자열 검색 가능하게 하자.
// [first, last) - 반개 구간
char* xstrchr(char* first, char* last, char value)
{
  while (first != last && *first != value)
    ++first;

  return first;
}

// 2. 검색 대상 타입의 일반화 - template 도입
// 문제점 1)
// - 구간의 타입과 찾는 요소의 타입이 연관되어 있다.
// template <typename T>
// T* xfind(T* first, T* last, T value)

// 문제점 2)
//  - T* 라고 하면 진짜 포인터만 사용할 수 있다. 
//    스마트 포인터를 사용할 수 없다.
template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
  while (first != last && *first != value)
    ++first;

  return first;
}

#include <vector>
#include <algorithm>  // find

int main()
{
  int x[] = { 1, 2, 3 };
  cout << *xfind(x, x + 3, 3) << endl;

  vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);

  cout << *xfind(v.begin(), v.end(), 30) << endl;
}


#if 0
int main()
{
  int x[] = { 1, 2, 3, 4, 5 };
  int* p = xfind(x, x + 5, 3.0);
  if (p != x + 5)
    cout << *p << endl;
}
#endif


#if 0
int main()
{
  char s[] = "abcdefg";
  char* p = xfind(s + 3, s + 7, 'c');
  if (p != s + 7)
    cout << *p << endl;
}
#endif



#if 0
int main()
{
  char s[] = "abcdefg";
  char* p = xstrchr(s, 'c');
  if (p != NULL)
    cout << *p << endl;
}
#endif
