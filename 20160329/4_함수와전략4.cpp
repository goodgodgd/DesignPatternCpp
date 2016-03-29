#include <iostream>
using namespace std;

// 함수 객체는 컴파일 시간에 inline이 확인되므로 inline 최적화가 가능하다
// 함수 포인터는 컴파일 시간에 알 수 없으므로 최적화가 안된다.
// 정책에 관련된 부분을 template으로 지정해줄 수 있다. -> 코드가 컴파일 시간에 만들어진다.
// 함수 객체에서는 inline이 가능하므로 함수 포인터로 인한 성능저하를 막을 수 있다.
// C++에서 함수 객체를 지원하는 이유
// 코드 메모리를 고려한다면 함수 포인터를, 성능을 생각한다면 함수 객체를 쓰자!

struct Less
{
	inline bool operator()(int a, int b) { return a > b; }
};

struct Greater
{
	inline bool operator()(int a, int b) { return a < b; }
};

// 이것도 가능하지만 정책을 바꿀 수 없다.
#if 0
void sort(int* x, int n, Less cmp)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; j++)
			if (cmp(x[i], x[j]))
				swap(x[i], x[j]);
}
#endif

template <typename T>
void sort(int* x, int n, T cmp)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; j++)
			if (cmp(x[i], x[j]))
				swap(x[i], x[j]);
}


int main()
{
	Less f1;
	Greater f2;
	int x[10] = { 1, 3, 5, 7, 8, 2, 4, 6, 8, 10 };
	sort(x, 10, f1);
	for (int i = 0; i < 10; ++i)
		cout << x[i];
	cout << endl;

	sort(x, 10, f2);
	for (int i = 0; i < 10; ++i)
		cout << x[i];
	cout << endl;

}
