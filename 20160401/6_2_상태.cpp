// 6 상태
// State Pattern: 상태에 따른 동작의 변경
//	- 게임 만들 때 널리 사용된다.

#include <iostream>
using namespace std;

// 1. 아이템에 종류 따른 조건 분기

class Hero
{
	int state;
public:
	// 아이템에 따라 달리는 속도가 달라진다.
	// 문제점: OCP를 만족할 수 없다. 기능이 추가될 때마다 기존 코드가 수정되어야 한다.
	// - 신규 아이템이 추가될 때마다 조건분기문이 추가되어야 한다.
	// 문제는 아이템이 계속 변경될거라고 예상될 때, 변경이 없다면 그냥 이렇게 해도 된다.
	void run() 
	{
		if (state == 1)
			cout << "run" << endl;
		else if (state == 2)
			cout << "fast run" << endl;
	}
	void attack() { cout << "attack" << endl; }
};

int main()
{
	Hero hero;
	hero.run();
	hero.attack();
}
