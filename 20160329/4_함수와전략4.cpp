#include <iostream>
using namespace std;

// �Լ� ��ü�� ������ �ð��� inline�� Ȯ�εǹǷ� inline ����ȭ�� �����ϴ�
// �Լ� �����ʹ� ������ �ð��� �� �� �����Ƿ� ����ȭ�� �ȵȴ�.
// ��å�� ���õ� �κ��� template���� �������� �� �ִ�. -> �ڵ尡 ������ �ð��� ���������.
// �Լ� ��ü������ inline�� �����ϹǷ� �Լ� �����ͷ� ���� �������ϸ� ���� �� �ִ�.
// C++���� �Լ� ��ü�� �����ϴ� ����
// �ڵ� �޸𸮸� ����Ѵٸ� �Լ� �����͸�, ������ �����Ѵٸ� �Լ� ��ü�� ����!

struct Less
{
	inline bool operator()(int a, int b) { return a > b; }
};

struct Greater
{
	inline bool operator()(int a, int b) { return a < b; }
};

// �̰͵� ���������� ��å�� �ٲ� �� ����.
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
