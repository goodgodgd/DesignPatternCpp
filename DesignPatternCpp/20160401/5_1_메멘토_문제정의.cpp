// Memento
// 메멘토 패턴: 객체의 상태를 저장하고 복구하는 패턴

#include <iostream>
using namespace std;

// 게임에서의 저장 복원을 생각해보자
class User
{
	int level;
	int exp;
	int gold;

public:
	User() : level(1), exp(0), gold(0) {}


	int getLevel() { return level; }
	int getExp() { return exp; }
	int getGold() { return gold; }

	void load(int l, int e, int g)
	{
		level = l;
		exp = e;
		gold = g;
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
	User usr;
	usr.attack();

	//....
	int l = usr.getLevel();
	int g = usr.getGold();
	int e = usr.getExp();

	//
	usr.load(l, g, e);

}

// 자신의 상태를 외부로 노출하는 것은 구현이 바뀔때마다 load도 바뀌어야 한다.
// 내부 상태를 모아서 캡슐화
