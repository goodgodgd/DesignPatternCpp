// 2_LineEdit - 중요한 예제입니다.
// http://d.pr/n/16QbJ

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// 한계점
// 1) 실행 시간에 정책을 교체하는 것이 불가능하다.
//		객체의 변경이 아닌 클래스의 변경
// 2) 내부에서 사용되는 정책을 다른 클래스에서 재사용하는 것이 불가능하다.
//		TextEdit이라는 새 클래스가 있을 때 같은 정책을 사용해도 코드가 공유되지 않는다.

// Template method 패턴의 단점
//		정책의 변경이 실행시간에 변경되는 것이 불가하다. AddressEdit으로 "선언"해야 한다.

class LineEdit
{
	string data;
public:
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

// 이제 정책을 변경하고 싶다면 파생 클래서에서 가상함수를 재정의하면 된다.
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
