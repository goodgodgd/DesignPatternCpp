// 2_LineEdit2
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// http://d.pr/n/16QbJ
// 한계점
// 1) 실행 시간에 정책을 교체하는 것이 불가능하다.
//    객체의 변경이 아닌 클래스의 변경

// 2) 내부에서 사용되는 정책을 다른 클래스에서 재사용하는 것이 불가능하다.


class LineEdit
{
  string data;
public:
  // Validation 정책은 변경이 가능해야 한다.
  // - 변하지 않는 코드(공통성)에서 변해야 하는 것(가변성)이 있다면
  //   분리해야 한다.

  // 방법 1. 변하는 것을 가상함수화 한다. - "template method 패턴"
  virtual bool validate(char c) { return isdigit(c); }

  string getData()
  {
    data.clear();

    while (1)
    {
      char c = getch();
      if (c == 13) // enter
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

// http://d.pr/n/1awoW
// 이제 정책을 변경하고 싶다면 파생 클래스에서 가상함수를 재정의하면 된다.
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