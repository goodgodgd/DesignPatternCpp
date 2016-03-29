// 110Zq
#include <iostream>
using namespace std;

// ������ �ʴ� ��ü �˰��򿡼� ���ؾ� �ϴ� ��å �ڵ�� �и��Ǿ�� �Ѵ�.
//	-> �Ϲ� �Լ������� ���ϴ� ���� �Լ� ����(�Լ� ������)�� �̾� ���� �ȴ�.
#if 0
void sort(int* x, int n)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; j++)
			// ���������� ����, ���ؾ� �ϴ� ��å�� �Լ��� �ܺη� ������ �Ѵ�.
			if (x[i] > x[j])
				swap(x[i], x[j]);
}
#endif

// inline�� ���� ���� ������ ���� ������ �� �� �ִ�.
// �׷��� inline ġȯ�� �����Ѱ�? �����Ϸ��� ����� �Ȱ��� ������� ���ΰ�?
// �ȵȴٸ� ��� �����ϰ� �����? ���� �ڵ忡... (����: �ȵȴ�)
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
