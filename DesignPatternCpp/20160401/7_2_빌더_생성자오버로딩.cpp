// ����
// -> ������ ���������� ǥ���� �޶����� ��ü�� ���� ��
// -> ��ü ����
// -> �������� ���ڰ� ���� ��

#include <iostream>
#include <string>
using namespace std;

// ��� 1. Telescoping Constructor Pattern
//		: ������ ������ ����
#if 0
class UserInfo
{
	const string id;		// ������ �ʴ� �ʵ� const
	const string address;	// �������� �ʼ� ���ڴ�, �����ڿ����� �ʱ�ȭ �� �� �ִ�.
	int level;
	int gold;
	int cash;

public:
	UserInfo(string i, string a) : id(i), address(a) {}
	UserInfo(string i, string a, int l) : id(i), address(a)
	UserInfo(string i, string a, int l, int g) : id(i), address(a) {}
	UserInfo(string i, string a, int l, int g, int c) : id(i), address(a) {}
};

int main()
{
	UserInfo ui("����", "����", 0, 100, 1000);
}

#endif	// ����: ������ ������ �ʹ� ������.

// ������ ���� ����� �Ẹ��.
class UserInfo
{
	const string id;		// ������ �ʴ� �ʵ� const
	const string address;	// �������� �ʼ� ���ڴ�, �����ڿ����� �ʱ�ȭ �� �� �ִ�.
	int level;
	int gold;
	int cash;

public:
	UserInfo(string i, string a)
		: UserInfo(i, a, 0, 0, 0) {}
	UserInfo(string i, string a, int l)
		: UserInfo(i, a, l, 0, 0) {}
	UserInfo(string i, string a, int l, int g)
		: UserInfo(i, a, l, g, 0) // C++11 Delegating Constructor
	{}
	// this(i, a, l, g, 0); - ������ ����

	UserInfo(string i, string a, int l, int g, int c)
		: id(i), address(a), level(l), gold(g), cash(c) {}
};

// �� ����� ��ü�� ������ ���� �����Ϸ��� ���� ������ �´� �����ڸ� �����ؼ� �����ϸ� �ȴ�.

int main()
{
	UserInfo ui("����", "����", 0, 100, 1000);
	// ������
	// 1) �������� ���� �ʴ�. � ���ڰ� � ����� �ʱ�ȭ�ϴ��� �˱� ��ƴ�.
	// 2) ���� Ÿ���� ���ڿ� ���ؼ� ������ �ٲ� ��� ������ ������ �߻����� �ʽ��ϴ�.
}
