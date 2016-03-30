// 2_LineEdit - 중요한 예제입니다.
// http://d.pr/n/15k97

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// 공통성과 가변성을 분리하는 방법 2
//	- 변하는 것을 (정책에 관한 것만) 인터페이스 기반 클래스로 분리한다.
//	- 전략(Strategy) 패턴

// 1. 실행 시간에 정책을 교체하는 것이 가능하다.
// 2. 정책을 재사용하는 것이 가능하다.

// template 클래스는 별도의 클래스 필요없이 간단하게 정책변경 가능
// 전략 패턴은 실행시간에 정책변경 가능, 같은 정책을 여러 클래스에 적용 가능

// Qt에도 QValidator 라는 인터페이스 있다.
struct IValidator
{
	virtual bool validate(string s, char c) = 0;		// 순수 가상 함수
	virtual bool isComplete(string s)	{ return true; }	// 가상 함수
	virtual ~IValidator() {}
};

// 이제 다양한 Validataor를 제공하면 됩니다.
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


	// Validataion 정책은 변경이 가능해야 한다.
	// 변하지 않는 코드(공통성)에서 변해야 하는 것(가변성)이 있다면 분리해야 한다.
	// 방법 1. 변하는 것을 가상함수화 한다. - "template method 패턴"
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
