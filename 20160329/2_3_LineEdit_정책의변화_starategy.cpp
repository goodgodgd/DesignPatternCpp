// 2_LineEdit - �߿��� �����Դϴ�.
// http://d.pr/n/15k97

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// ���뼺�� �������� �и��ϴ� ��� 2
//	- ���ϴ� ���� (��å�� ���� �͸�) �������̽� ��� Ŭ������ �и��Ѵ�.
//	- ����(Strategy) ����

// 1. ���� �ð��� ��å�� ��ü�ϴ� ���� �����ϴ�.
// 2. ��å�� �����ϴ� ���� �����ϴ�.

// template Ŭ������ ������ Ŭ���� �ʿ���� �����ϰ� ��å���� ����
// ���� ������ ����ð��� ��å���� ����, ���� ��å�� ���� Ŭ������ ���� ����

// Qt���� QValidator ��� �������̽� �ִ�.
struct IValidator
{
	virtual bool validate(string s, char c) = 0;		// ���� ���� �Լ�
	virtual bool isComplete(string s)	{ return true; }	// ���� �Լ�
	virtual ~IValidator() {}
};

// ���� �پ��� Validataor�� �����ϸ� �˴ϴ�.
class LimitDigitValidtor : public IValidator
{
	int value;
public:
	LimitDigitValidtor(int v) : value(v) {}

	virtual bool validate(string s, char c)
	{
		return s.size() < value && isdigit(c);
	}

	virtual bool isComplete(string s)
	{
		return s.size() == value;
	}
};

class LineEdit
{
	string data;
	//------------------------------
	IValidator* pValidator;

public:
	LineEdit() : pValidator(0) {}
	
	void setValidator(IValidator* p) { pValidator = p; }
	//------------------------------


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
			if (c == 13 || pValidator == 0 || pValidator->isComplete(data))	// enter
				break;

			if (pValidator == 0 || pValidator->validate(data, c))
			{
				data.push_back(c);
				cout << c;
			}
		}

		cout << endl;
		return data;
	}
};


int main()
{
	LineEdit edit;
	LimitDigitValidtor v(5);
	edit.setValidator(&v);

	while (1)
	{
		string s = edit.getData();
		cout << "input: " << s << endl;
	}
}
