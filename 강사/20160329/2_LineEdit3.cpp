// 2_LineEdit3
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// http://d.pr/n/15k97
// 공통성과 가변성을 분리하는 방법 2.
//  - 변하는 것을 인터페이스 기반 클래스로 분리한다.
//  - 전략(Strategy) 패턴

// 1. 실행 시간에 정책을 교체하는 것이 가능하다.
// 2. 정책을 재사용하는 것이 가능하다.

// Qt라는 오픈 소스 GUI 라이브러리에는 QValidator 라는 인터페이스가 있습니다.
struct IValidator
{
  virtual bool validate(string s, char c) = 0;
  virtual bool isComplete(string s) { return true; }

  virtual ~IValidator() {}
};

// GUI 도구인 LineEdit를 만들어 봅시다.
class LineEdit
{
  string data;
//--------------------------
  IValidator* pValidator;

public:
  LineEdit() : pValidator(0) {}

  void setValidator(IValidator* p) { pValidator = p; }
//---------------------------


  string getData()
  {
    data.clear();

    while (1)
    {
      char c = getch();
      if (c == 13 &&
        (pValidator == 0 || pValidator->isComplete(data))
        ) // enter
        break;

      if (pValidator == 0 || pValidator->validate(data, c) )
      {
        data.push_back(c);
        cout << c;
      }
    }

    cout << endl;
    return data;
  }
};

// 이제 다양한 Validator를 제공하면 됩니다.
class LimitDigitValidator : public IValidator
{
  int value;
public:
  LimitDigitValidator(int v) : value(v) {}

  virtual bool validate(string s, char c)
  {
    return s.size() < value && isdigit(c);
  }

  virtual bool isComplete(string s)
  {
    return s.size() == value;
  }
};

// hhttp://d.pr/n/hKtq
int main()
{
  LineEdit edit;
  LimitDigitValidator v(5);

  edit.setValidator(&v);
    
  while (1)
  {
    string s = edit.getData();
    cout << "input: " << s << endl;
  }
}