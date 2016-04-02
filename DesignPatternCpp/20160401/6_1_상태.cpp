// 6 상태
// State Pattern: 상태에 따른 동작의 변경
//	- 게임 만들 때 널리 사용된다.

#include <iostream>
using namespace std;

class Hero
{
	int state;
public:
	void run() { cout << "run" << endl; }
	void attack() { cout << "attack" << endl; }
};

int main()
{
	Hero hero;
	hero.run();
	hero.attack();
}
