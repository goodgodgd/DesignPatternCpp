// C++ ���̺귯���� �����ϱ� ���ؼ��� �Ϲ�ȭ�� �̾��ؾ� �մϴ�.
// C++ - OOP + �Ϲ�ȭ(Generic)

#include <vector>
#include <iostream>
using namespace std;

// C�� ���ڿ� �Լ�
#if 0
char* xstrchr(char* s, char c)
{
	while (*s != '\0' && *s != c)
		++s;
	return *s == c ? s : NULL;
}

int main()
{
	char s[] = "abcdefg";
	char* p = strchr(s, 'c');	// ���ڿ� ���� Ž��
	// -> �̰��� �ٸ� Ÿ�Կ� ���� �Ϲ�ȭ �غ���.
	if (p != NULL)
		cout << *p << endl;
}
#endif

// 1. �˻� ������ �Ϲ�ȭ: �κ� ���ڿ� �˻� �����ϰ� ����.
//		���ڿ��� '\0'���� ������ �Ǿ��ִ�. �κ� ������ ������ �� ����.
//		-> ���� ����, �迭�� Ž���� �� �����Ͱ� ����.
// [first, last) - �ݰ� ������ ����, ������ ��Ҹ� �����ϰ� �ִ�. �������� '\0'���� �����ϰ� �����.
#if 0
char *xstrchr(char* first, char* last, char value)
{
	while (first != last && *first != value)
		++first;

//	return first == last ? 0 : first;
	return first;	// first == last �̸� �����ٴ� ���
}

int main()
{
	char s[] = "abcdefg";
	char* p = xstrchr(s, s + 7, 'c');
	if (p != s + 7)
		cout << *p << endl;
}
#endif

// 2. �˻� Ÿ���� �Ϲ�ȭ - template ����
#if 0
template <typename T>
T *xfind(T* first, T* last, T value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last �̸� �����ٴ� ���
}

int main()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int* p = xfind(x, x + 5, 3);
	if (p != x + 5)
		cout << *p << endl;
}
#endif

// ������ 1)
// ������ Ÿ�԰� ã�� ����� Ÿ���� ����Ǿ� �ִ�.
// int �迭 �ȿ��� double�̳� short�� ã�� �� ����.
// 	�����Ϸ��� �Ͻ��� Ÿ���� ������ �� Ÿ���� ��ȣ������.

// ���ø� Ÿ���� �ϳ� �� �÷��ش�. -> ���� Ÿ�԰� �� Ÿ���� �и�����.
#if 0
template <typename T1, typename T2>
T1 *xfind(T1* first, T1* last, T2 value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last �̸� �����ٴ� ���
}

int main()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int* p = xfind(x, x + 5, 3);
	if (p != x + 5)
		cout << *p << endl;
}
#endif

// ������ 2)
// - T* ��� �ϸ� ��¥ �����͸� ����� �� �ִ�. ����Ʈ �����͸� ����� �� ����.
// -> ������ Ÿ�� ��ü�� �Ͻ��� Ÿ������ �޾ƹ�����
template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last �̸� �����ٴ� ���
}

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

// C++������ list�� vector ���ο� find, sort ���� �������� �ʰ� <algorithm>�� ������ ���Ҵ�.
// Iterator: �����̳� ������ ������ ��Ÿ����. algorithm���� STL �����̳ʵ��� ���������� ���� �ְ� ���ִ� ���� ����
