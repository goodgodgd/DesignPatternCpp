// ����
// -> ������ ���������� ǥ���� �޶����� ��ü�� ���� ��
// -> ��ü ����

// -> �������� ���ڰ� ������
#include <iostream>
#include <string>
using namespace std;

// ��� 1. Telescoping Constructor Pattern
//    : ������ ������ ����
class UserInfo
{
public:
  UserInfo(string i, string a) 
    : UserInfo(i, a, 0, 0, 0) {}
  UserInfo(string i, string a, int l)
    : UserInfo(i, a, l, 0, 0) {}
  UserInfo(string i, string a, int l, int g)
    : UserInfo(i, a, l, g, 0) // C++11 Delegating Constructor
  {}
  // this(i, a, l, g, 0); - ������ ����

  UserInfo(string i, string a, int l, int g, int c)
    : id(i), address(a), level(l), gold(g), cash(c) {}

private:
  const string id;          // �ʼ� ����
  const string address;
  int level;                // ���� ����
  int gold;
  int cash;
};

int main()
{

}