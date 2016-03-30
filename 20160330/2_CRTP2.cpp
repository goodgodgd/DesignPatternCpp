// ��ü�� ������ N���� �����ϴ� ���

#include <iostream>
using namespace std;

// �⺻���� ����
#if 0
class Mouse
{
	static int n;
public:
	Mouse()
	{
		if (++n > 5)
			throw 1;
	}
};

int Mouse::n = 0;

int main()
{
	try {
		Mouse m[6];
	}
	catch (...) {
		cout << "��ü ���� ����" << endl;
	}
}
#endif


// N ���� ����� �ִ� ��ü Ÿ���� �����

#if 0
// ���ø��� �� �־ �ȴ�.
template <int N>
class LimitMaxObject
{
	static int n;
public:
	LimitMaxObject()
	{
		if (++n > 5)
			throw 1;
	}
};

template <int N>	// �Ʒ� �ٿ��� N�� �𸣱� ������ ���ø��� �ѹ� �� ����.
int LimitMaxObject<N>::n = 0;

// 5���� ����� �ִ� ��ü Ÿ���� ����ڴ�.
class Mouse : public LimitMaxObject < 5 >
{
};

int main()
{
	try {
		Mouse m[6];
	}
	catch (...) {
		cout << "��ü ���� ����" << endl;
	}
}
#endif

// ���� ������: �ٸ� Ÿ���� ��ü�� ������µ� ��� Ÿ�Կ��� �������� n�� �����Ǿ� 
// LimitMaxObject�� ��ӹ޴� ��� Ŭ���� ��ü�� ���� n���� ���ѵȴ�.
// template ���ڸ� �߰��� Ÿ���� �ٲ���� �Ѵ�.
// �Ʒ��� ������ CRTP�� �̿��ؼ� ���� �ٸ� ���������� ����ϴ� ����Դϴ�.

// ���������� ���� ���� ���� ���ø��� �̿��� Ÿ���� ��ȭ
template <typename T, int N>
class LimitMaxObject
{
	static int n;
public:
	LimitMaxObject()
	{
		if (++n > 5)
			throw 1;
	}
};

template <typename T, int N>	// �Ʒ� �ٿ��� T, N�� �𸣱� ������ ���ø��� �ѹ� �� ����.
int LimitMaxObject<T, N>::n = 0;

class Mouse : public LimitMaxObject < Mouse, 5 >
{
};

class Keyboard : public LimitMaxObject < Keyboard, 5 >
{
};

int main()
{
	// 3+3 �� 6������ �������� �ʴ´�.
	try {
		Mouse m[3];
		Keyboard k[3];
	}
	catch (...) {
		cout << "��ü ���� ����" << endl;
	}
}

