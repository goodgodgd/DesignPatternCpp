// 110Zq
#include <iostream>
using namespace std;

// 변하지 않는 전체 알고리즘에서 변해야 하는 정책 코드는 분리되어야 한다.
//	-> 일반 함수에서는 변하는 것을 함수 인자(함수 포인터)로 뽑아 내면 된다.
#if 0
void sort(int* x, int n)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; j++)
			// 오름차순만 가능, 변해야 하는 정책은 함수의 외부로 나가야 한다.
			if (x[i] > x[j])
				swap(x[i], x[j]);
}
#endif

// inline을 쓰면 직접 구현과 같은 성능을 낼 수 있다.
// 그런데 inline 치환이 가능한가? 컴파일러가 기계어로 똑같이 만들어줄 것인가?
// 안된다면 어떻게 가능하게 만들까? 다음 코드에... (정답: 안된다)
inline bool cmp1(int a, int b)	{ return a > b; }
inline bool cmp2(int a, int b)	{ return a < b; }

void sort(int* x, int n, bool(*cmp)(int, int))
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; j++)
			if (cmp(x[i], x[j]))
				swap(x[i], x[j]);
}


int main()
{
	int x[10] = { 1, 3, 5, 7, 8, 2, 4, 6, 8, 10 };
	sort(x, 10, cmp2);

	for (int i = 0; i < 10; ++i)
		cout << x[i] << endl;
}
