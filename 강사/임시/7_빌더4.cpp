#include <iostream>
#include <string>
using namespace std;

// ��� 3. ����
// - ������ ������ ���ϰ� ���� ������ ������ ������ ����̴�.

class UserInfo
{
public:
  class Builder // UserInfo�� �������ִ� ��Ȱ
  {
  public:
    Builder(string i, string a) : id(i), address(a) {}

    Builder& level(int a)
    { 
      level = a;
      return *this;
    }

    Builder& gold(int a)
    {
      gold = a;
      return *this;
    }

    Builder& cash(int a)
    {
      cash = a;
      return *this;
    }

    UserInfo build()
    {
      return UserInfo(*this);
    }
  private:
    const string id;          // �ʼ� ����
    const string address;
    int level;                // ���� ����
    int gold;
    int cash;
  };



private:
  const string id;          // �ʼ� ����
  const string address;
  int level;                // ���� ����
  int gold;
  int cash;
};

int main()
{
  UserInfo ui = UserInfo::Builder("chansik.yun", "����")
                .level(10)
                .gold(100)
                .cash(2000).build();
}