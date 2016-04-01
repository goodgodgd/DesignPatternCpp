// 6 상태
// State Pattern: 상태에 따른 동작의 변경
//	- 게임 만들 때 널리 사용된다.

// 방법 2. 변하는 것을 가상함수로 분리
//			- item에 따라 변하는 동작 -> 가상함수
#include <iostream>
using namespace std;

#if 0
class Hero
{
	int state;
public:
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
	Hero normal;
	FastItemHero fast;
	Hero* hero = &normal; // 초기 상태

	hero->run();
	hero->attack();

	// 아이템 획득
	hero = &fast;
	hero->run();
	hero->attack();
	
}
#endif
// 근데 영웅의 상태가 state만 있는 것이 아니라 gold도 있다면??

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
	Hero normal;
	FastItemHero fast;
	Hero* hero = &normal; // 초기 상태

	hero->run();
	hero->attack();

	hero->gold += 10;

	// 아이템 획득
	// 동작 뿐 아니라 상태도 변경된다. gold는 공유되어야 한다.
	// fast의 gold가 덮어써진다.
	hero = &fast;
	hero->run();
	hero->attack();

	// 근데 영웅의 상태가 state만 있는 것이 아니라 gold도 있다면??
}
