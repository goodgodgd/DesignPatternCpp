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
    Builder(string i, string a) : id_(i), address_(a) {}

    Builder& level(int a)
    { 
      level_ = a;
      return *this;
    }

    Builder& gold(int a)
    {
      gold_ = a;
      return *this;
    }

    Builder& cash(int a)
    {
      cash_ = a;
      return *this;
    }

    UserInfo build()
    {
      return UserInfo(*this);
    }

    friend class UserInfo; // !!!
  private:
    const string id_;          // �ʼ� ����
    const string address_;
    int level_;                // ���� ����
    int gold_;
    int cash_;
  };

  UserInfo(const Builder& builder) 
    : id(builder.id_),
    address(builder.address_),
    level(builder.level_),
    gold(builder.gold_),
    cash(builder.cash_)
  {}
private:
  const string id;          // �ʼ� ����
  const string address;
  const int level;                // ���� ����
  const int gold;
  const int cash;
};

// �ۼ��ؾ� �Ǵ� �ڵ�� �ټ� ������, �߰����� ��ü�� ���� �޸𸮵�
// �ʿ�������, ��ü �ϰ����� �����ǰ�, �������� ����.

// ������ �Һ� ��ü�� ����� �� �����մϴ�.
//   String -> StringBuilder, StringBuffer

int main()
{
  UserInfo ui = UserInfo::Builder("chansik.yun", "����")
                .level(10)
                .gold(100)
                .cash(2000).build();
}