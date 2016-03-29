// 2_LineEdit - 중요한 예제입니다.
// http://d.pr/n/1lpcI

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// GUI 도구인 LineEdit를 만들어 봅시다.

class LineEdit
{
	string data;
public:
	string getData()
	{
		data.clear();
		while (1)
		{
			char c = getch();
			if (c == 13)	// enter
				break;

			if (isdigit(c))
			{
				data.push_back(c);
				cout << c;
			}
		}

		cout << endl;
		return data;
	}
};

// 문제 LineEdit 라는 클래스를 만드는 이유는 재사용 위해서
// 그러나 LineEdit은 숫자만 받게 되어있다. 사용자마다 사용하고자하는 정책이 다를수 있어서 재사용 어렵다.

int main()
{
	LineEdit edit;
	while (1)
	{
		string s = edit.getData();
		cout << "input: " << s << endl;
	}
}
