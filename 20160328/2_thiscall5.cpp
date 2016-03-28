// Ÿ�̸Ӹ� ĸ��ȭ �غ��ô�.
// C��� �Լ��� Ŭ������ �����ϴ� ������ thread�� ���
// static ��� �Լ� �����Ϳ� 

// http://d.pr/n/ZBH
// http://d.pr/n/191Lz

// ioacademy.h
// http://d.pr/n/17nrr

#include <string>
#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;


#if 0	// �Ϲ� �Լ� Ÿ�̸� ȣ��
void foo(int id)
{
	cout << "foo: " << id << endl;
}

int main()
{
	// �̷��� �Ǹ� Ÿ�̸Ӱ� ��� ���� �ʰ� �ٷ� ����, Ÿ�̸Ӱ� ���� ���ؼ� �޽��� ������ ���ƾ� ��
	int n1 = IoSetTimer(1000, foo);
	int n2 = IoSetTimer(500, foo);
	// �޽��� ������ ���� ��
	IoProcessMessage();
}
#endif

#include <map>
class Clock;	// ���� ���� - ������ ������ ��� �����ʹ� ��� ����
// Ŭ���� �ۿ� �־� �ϳ��� ���� �ȵ�. -> Ŭ���� static ��� ����
//map<int, Clock*> this_map;

class Clock
{
	string name;
public:
	Clock(string s) : name(s) {}
	// static �Լ����� �ҷ����� ���� static ���� -> �ܺ� ���� �ʿ�
	static map<int, Clock*> this_map;

	void start(int ms)
	{	
		// C��� �Լ��̱� ������ �Ϲ� ��� �Լ� ���� �ȵ�, static ��� �Լ� �޾ƾ�
//		IoSetTimer(ms, timerHandler);

		int id = IoSetTimer(ms, timerHandler);
		this_map[id] = this;
	}

	// static �̾�� IoSetTimer�� ���ް���
	// �׷��� �� static ������ ��� ���� ���� �Ұ�, ��� �Լ� ���� �Ұ�
	// ������ �� �ִ� ���� ���� id ��
	// ��� id�� ���ؼ� this �����͸� �����ұ�? => key-value ���� map ���
	static void timerHandler(int id)
	{
		Clock* self = this_map[id]; 
		cout << self->name << endl;
	}
};

// static ��� ������ �ܺ� ���Ǹ� �ؾ� �մϴ�. (�ҽ�����)
map<int, Clock*> Clock::this_map;

int main()
{
	Clock c1("AAA");
	Clock c2("\tBBB");
	
	c1.start(1000);	// 1�ʿ� �ѹ��� �̸��� ���
	c2.start(500);

	IoProcessMessage();
}


