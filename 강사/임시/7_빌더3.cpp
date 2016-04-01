// 빌더
// -> 공정은 동일하지만 표현이 달라지는 객체를 만들 때
// -> 객체 생성

// -> 생성자의 인자가 많을때
#include <iostream>
#include <string>
using namespace std;

// 방법 2. Beans Pattern
//    
class UserInfo
{
public:
  UserInfo() {}

  void setId(string s) { id = s; }
  void setAddress(string s) { address = s; }
  void setLevel(int a) { level = a; }
  void setGold(int a) { gold = a; }
  void setCash(int a) { cash = a; }

private:
  const string id;          // 필수 인자
  const string address;
  int level;                // 선택 인자
  int gold;
  int cash;
};

int main()
{
  UserInfo ui;
  ui.setId("chansik.yun");
  ui.setAddress("수원");
  ui.setLevel(10);
  ui.setGold(1000);
  ui.setCash(100);

}