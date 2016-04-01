// 2_LineEdit2
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// http://d.pr/n/16QbJ
// �Ѱ���
// 1) ���� �ð��� ��å�� ��ü�ϴ� ���� �Ұ����ϴ�.
//    ��ü�� ������ �ƴ� Ŭ������ ����

// 2) ���ο��� ���Ǵ� ��å�� �ٸ� Ŭ�������� �����ϴ� ���� �Ұ����ϴ�.


class LineEdit
{
  string data;
public:
  // Validation ��å�� ������ �����ؾ� �Ѵ�.
  // - ������ �ʴ� �ڵ�(���뼺)���� ���ؾ� �ϴ� ��(������)�� �ִٸ�
  //   �и��ؾ� �Ѵ�.

  // ��� 1. ���ϴ� ���� �����Լ�ȭ �Ѵ�. - "template method ����"
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