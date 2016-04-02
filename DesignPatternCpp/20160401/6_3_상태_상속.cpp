// 6 상태
// State Pattern: 상태에 따른 동작의 변경
//	- 게임 만들 때 널리 사용된다.

// 목표: 아이템(상태)에 따라 동작(run, attack)을 변화시키고 싶다.
// 방법 2. 변하는 것을 가상함수로 분리
//			- item에 따라 변하는 동작 -> 가상함수
//			- 상태가 내부 변수에 의존하지 않고, 다른 상태를 다른 객체 타입으로 정의

#include <iostream>
using namespace std;

#if 0
class Hero
{
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

// 문제: 근데 영웅의 상태가 state만 있는 것이 아니라 gold도 있다면??
class Hero
{
public:
	Hero() : gold(0) {}
	int gold;
	virtual void run() { cout << "run" << endl; }
	virtual void attack() { cout << "attack" << endl; }
};

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
	cout << "gold: " << hero->gold << endl;	// gold: 10

	// 아이템 획득
	// 동작 뿐 아니라 상태도 변경된다. gold는 공유되어야 한다.
	// fast의 gold가 덮어써진다.
	hero = &fast;
	hero->run();
	hero->attack();
	cout << "gold: " << hero->gold << endl;	// gold: 0
}
