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
    const string id_;          // 필수 인자
    const string address_;
    int level_;                // 선택 인자
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
  const string id;          // 필수 인자
  const string address;
  const int level;                // 선택 인자
  const int gold;
  const int cash;
};

// 작성해야 되는 코드는 다소 있지만, 추가적인 객체에 대한 메모리도
// 필요하지만, 객체 일관성이 유지되고, 가독성도 좋다.

// 빌더는 불변 객체를 만드는 데 유용합니다.
//   String -> StringBuilder, StringBuffer

int main()
{
  UserInfo ui = UserInfo::Builder("chansik.yun", "수원")
                .level(10)
                .gold(100)
                .cash(2000).build();
}