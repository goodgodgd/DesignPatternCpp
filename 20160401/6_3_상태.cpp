// 6 ����
// State Pattern: ���¿� ���� ������ ����
//	- ���� ���� �� �θ� ���ȴ�.

// ��� 2. ���ϴ� ���� �����Լ��� �и�
//			- item�� ���� ���ϴ� ���� -> �����Լ�
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

// �������� ȹ�濡 ���� ������ �����ϱ� ���� ����� �����ϸ� �ȴ�.
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
	Hero* hero = &normal; // �ʱ� ����

	hero->run();
	hero->attack();

	// ������ ȹ��
	hero = &fast;
	hero->run();
	hero->attack();
	
}
#endif
// �ٵ� ������ ���°� state�� �ִ� ���� �ƴ϶� gold�� �ִٸ�??

class Hero
{
	int state;
public:
	int gold;
	virtual void run() { cout << "run" << endl; }
	virtual void attack() { cout << "attack" << endl; }
};

// �������� ȹ�濡 ���� ������ �����ϱ� ���� ����� �����ϸ� �ȴ�.
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
	Hero* hero = &normal; // �ʱ� ����

	hero->run();
	hero->attack();

	hero->gold += 10;

	// ������ ȹ��
	// ���� �� �ƴ϶� ���µ� ����ȴ�. gold�� �����Ǿ�� �Ѵ�.
	// fast�� gold�� ���������.
	hero = &fast;
	hero->run();
	hero->attack();

	// �ٵ� ������ ���°� state�� �ִ� ���� �ƴ϶� gold�� �ִٸ�??
}
