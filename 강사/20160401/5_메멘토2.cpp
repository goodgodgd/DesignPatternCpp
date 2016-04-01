// 5_Memento
// 메멘토 패턴: 객체의 상태를 내부적으로 저장하고 복구하는 패턴

// Command: 행위의 캡슐화
// Memento: 객체의 상태를 캡슐화

#include <iostream>
using namespace std;

#include <vector>
class User
{
  int level;
  int exp;
  int gold;

  // 객체의 상태를 결정하는 필드를 캡슐화한다.
  struct Memento
  {
    int level;
    int exp;
    int gold;

    Memento(int l, int g, int e) : level(l), exp(e), gold(g) {}
  };

  vector<Memento*> memento;
public:
  User() : level(1), exp(0), gold(0) {}

  int save()
  {
    Memento* m = new Memento(level, gold, exp);
    memento.push_back(m);

    return memento.size() - 1;
  }

  void load(int token)
  {
    Memento* m = memento[token];
    level = m->level;
    exp = m->exp;
    gold = m->gold;
  }


  void attack()
  {
    ++level;
    exp += 100;
    gold += 1000;
  }
};

int main()
{
  User user;
  user.attack();

  int token = user.save();
  user.attack();

  user.load(token);

}