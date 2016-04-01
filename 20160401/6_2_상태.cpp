// 6 ����
// State Pattern: ���¿� ���� ������ ����
//	- ���� ���� �� �θ� ���ȴ�.

#include <iostream>
using namespace std;

// 1. �����ۿ� ���� ���� ���� �б�

class Hero
{
	int state;
public:
	// �����ۿ� ���� �޸��� �ӵ��� �޶�����.
	// ������: OCP�� ������ �� ����. ����� �߰��� ������ ���� �ڵ尡 �����Ǿ�� �Ѵ�.
	// - �ű� �������� �߰��� ������ ���Ǻб⹮�� �߰��Ǿ�� �Ѵ�.
	// ������ �������� ��� ����ɰŶ�� ����� ��, ������ ���ٸ� �׳� �̷��� �ص� �ȴ�.
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
