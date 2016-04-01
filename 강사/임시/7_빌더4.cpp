#include <iostream>
#include <string>
using namespace std;

// 방법 3. 빌더
// - 점층적 생성자 패턴과 빈즈 패턴의 장점을 결합한 방법이다.

class UserInfo
{
public:
  class Builder // UserInfo를 생성해주는 역활
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
    const string id;          // 필수 인자
    const string address;
    int level;                // 선택 인자
    int gold;
    int cash;
  };



private:
  const string id;          // 필수 인자
  const string address;
  int level;                // 선택 인자
  int gold;
  int cash;
};

int main()
{
  UserInfo ui = UserInfo::Builder("chansik.yun", "수원")
                .level(10)
                .gold(100)
                .cash(2000).build();
}