// 2_LineEdit3
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// http://d.pr/n/15k97
// ���뼺�� �������� �и��ϴ� ��� 2.
//  - ���ϴ� ���� �������̽� ��� Ŭ������ �и��Ѵ�.
//  - ����(Strategy) ����

// 1. ���� �ð��� ��å�� ��ü�ϴ� ���� �����ϴ�.
// 2. ��å�� �����ϴ� ���� �����ϴ�.

// Qt��� ���� �ҽ� GUI ���̺귯������ QValidator ��� �������̽��� �ֽ��ϴ�.
struct IValidator
{
  virtual bool validate(string s, char c) = 0;
  virtual bool isComplete(string s) { return true; }

  virtual ~IValidator() {}
};

// GUI ������ LineEdit�� ����� ���ô�.
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

// ���� �پ��� Validator�� �����ϸ� �˴ϴ�.
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