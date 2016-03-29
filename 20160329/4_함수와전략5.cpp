
#include <iostream>
using namespace std;
#include <algorithm>		// �̹� ��å ���� ������ sort() ���� �ֽ��ϴ�.
#include <functional>		// less, greater �Լ� ��ü�� �� �ȿ� �ֽ��ϴ�.

inline bool cmp1(int a, int b)	{ return a > b; }
inline bool cmp2(int a, int b)	{ return a < b; }

// �̷��� �Լ� ��ü�� ����� ���� �����Ƽ� Lambda ���Դ�.
struct abs_less
{
	// �տ� inline ��� ������ �ϸ� inline?
	bool operator()(int a, int b) { return abs(a) < abs(b); }
};

int main()
{
	int x[10] = { 1, 3, 5, 7, 8, 2, 4, 6, 8, 10 };

	// 1. ��å���� �Լ��� ����� ��
	// ����: ��å�� ������ ��ȯ�ص� sort()�� ����� �Ѱ��̴�.
	// ����: ��å�� �ζ��� ġȯ�� �ȵǹǷ� ���� ���ϰ� �ִ�. 
	sort(x, x + 10, cmp1);		// sort(int*, int*, bool(*)(int,int))
	sort(x, x + 10, cmp2);		// ���� ������ ��� -> �ڵ尡 �ѹ��� ������
	for (int i = 0; i < 10; ++i)
		cout << x[i] << " ";
	cout << endl;

	// 2. ��å���� �Լ� ��ü�� ����� ��
	// ����: ��å�� �ζ��� ġȯ�ǹǷ� ������ �����Ѵ�.
	// ����: ��å�� ��ȯ�� Ƚ�� ��ŭ�� sort() ���� �ڵ� ����
	//		�����ڿ��� �Լ� ��ü Ŭ���� �̸��� �Լ� ��ü ��ü �̸��� �� ����� �ϴ� �δ�. �ڵ嵵 �������.
	less<int> f1;
	greater<int> f2;
	sort(x, x + 10, f1);		// sort(int*, int*, less<int>)
	sort(x, x + 10, f2);		// sort(int*, int*, greater<int>)	-> �� �ڵ� ����
	for (int i = 0; i < 10; ++i)
		cout << x[i] << " ";
	cout << endl;

	// lambda: �Լ� ��ü�� ���� ����� ���� - �͸��� �Լ� ��ü(Ŭ����)
	// �ڵ����� inline�̴�!!
	// 2008����� �����Ϸ����� �̹� �����Ͽ����ϴ�.
	// - Visual studio 2010, gcc 4.5 ����
	// 1980: C++ ź��
	// 1998: 1�� ǥ�� Ȯ��, 2003�� ������: C++98/08
	// 2011: 2�� ǥ�� Ȯ��, 2014�� ������: C++11/14 - Modern C++
	// 2017: 3�� ǥ�� Ȯ�� ����
	// ���ٴ� ���� ��ü ���� ���� ��� �����ϴ� ���
	// C#: �͸��� ��������Ʈ
	// java: �Լ��� �������̽�
	// ObjC: ��� ���α׷���

	sort(x, x + 10, [](int a, int b){ return abs(a) > abs(b); });
	int n = 20;
	sort(x, x + 10, [n](int a, int b){ return abs(a) > abs(b) + n; });

}