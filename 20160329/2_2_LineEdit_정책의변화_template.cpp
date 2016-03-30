// 2_LineEdit - �߿��� �����Դϴ�.
// http://d.pr/n/16QbJ

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// �Ѱ���
// 1) ���� �ð��� ��å�� ��ü�ϴ� ���� �Ұ����ϴ�.
//		��ü�� ������ �ƴ� Ŭ������ ����
// 2) ���ο��� ���Ǵ� ��å�� �ٸ� Ŭ�������� �����ϴ� ���� �Ұ����ϴ�.
//		TextEdit�̶�� �� Ŭ������ ���� �� ���� ��å�� ����ص� �ڵ尡 �������� �ʴ´�.

// Template method ������ ����
//		��å�� ������ ����ð��� ����Ǵ� ���� �Ұ��ϴ�. AddressEdit���� "����"�ؾ� �Ѵ�.

class LineEdit
{
	string data;
public:
	// Validataion ��å�� ������ �����ؾ� �Ѵ�.
	// ������ �ʴ� �ڵ�(���뼺)���� ���ؾ� �ϴ� ��(������)�� �ִٸ� �и��ؾ� �Ѵ�.
	// ��� 1. ���ϴ� ���� �����Լ�ȭ �Ѵ�. - "template method ����"
	virtual bool validate(char c)
	{
		if (isdigit(c) == 0)
			return false;
		return true;
	}

	string getData()
	{
		data.clear();
		while (1)
		{
			char c = getch();
			if (c == 13)	// enter
				break;

			if (validate(c))
			{
				data.push_back(c);
				cout << c;
			}
		}

		cout << endl;
		return data;
	}
};

// ���� ��å�� �����ϰ� �ʹٸ� �Ļ� Ŭ�������� �����Լ��� �������ϸ� �ȴ�.
class AddressEdit : public LineEdit
{
public:
	virtual bool validate(char c) { return true; }
};

int main()
{
	AddressEdit edit;
	while (1)
	{
		string s = edit.getData();
		cout << "input: " << s << endl;
	}
}
