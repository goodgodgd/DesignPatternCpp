// 2_LineEdit - 중요한 예제 입니다.
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
      if (c == 13) // enter
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

// http://d.pr/n/1lpcI
int main()
{
  LineEdit edit;
  while (1)
  {
    string s = edit.getData();
    cout << "input: " << s << endl;
  }
}