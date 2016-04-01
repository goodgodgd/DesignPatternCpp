// 6_상태3
// State Pattern: 상태에 따른 동작의 변경
//   - 게임 만들 때 널리 사용된다.
#include <iostream>
using namespace std;


// 방법 2. 변하는 것을 가상함수로 분리
//       - item에 따라 변하는 동작 -> 가상 함수
class Hero
{
  int state;
public:
  int gold;

  virtual void run() { cout << "run" << endl; }
  virtual void attack() { cout << "attack" << endl; }
};

// 아이템의 획득에 따라 동작을 변경하기 위해 상속을 적용하면 된다.
class FastItemHero : public Hero
{
public:
  virtual void run() { cout << "Fast run" << endl; }
  virtual void attack() { cout << "Fast attack" << endl; }
};

int main()
{
  Hero normal; FastItemHero fast;
  Hero* hero = &normal;  // 초기 상태
  hero->attack();
  hero->run();
  
  hero->gold += 100;

  //..... 아이템 획득
  // 동작 뿐 아니라 상태도 변경된다. gold는 공유 되어야 한다.
  hero = &fast;

  hero->attack();
  hero->run();
}