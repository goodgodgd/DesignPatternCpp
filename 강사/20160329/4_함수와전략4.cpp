// 4_함수와전략
#include <iostream>
using namespace std;

inline bool cmp1(int a, int b) { return a > b; }
inline bool cmp2(int a, int b) { return a < b; }

struct Less
{
  inline bool operator()(int a, int b) { return a > b; }
};

struct Greater
{
  inline bool operator()(int a, int b) { return a < b; }
};

// void sort(int* x, int n, Less cmp)
// void sort(int* x, int n, bool(*)(int, int))
template <typename T>
void sort(int* x, int n, T cmp)
{
  for (int i = 0; i < n - 1; ++i)
    for (int j = i + 1; j < n; j++)
      if (cmp(x[i], x[j]))
        // if (x[i] < x[j])
        swap(x[i], x[j]);
}

int main()
{
  Less f; Greater f2;

  int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
  sort(x, 10, cmp1);

  for (int i = 0; i < 10; ++i)
    cout << x[i] << endl;
}