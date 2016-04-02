// Memento
// �޸��� ����: ��ü�� ���¸� �����ϰ� �����ϴ� ����

#include <iostream>
#include <vector>
using namespace std;

// Command: ������ ĸ��ȭ
// Memento: ��ü�� ���¸� ĸ��ȭ, ������ ����
// �ٽ�: ���������� ĸ��ȭ, ���� �ڵ� ���� �߻����� �ʴ´�. (���� struct)

// ���ӿ����� ���� ������ �����غ���
class User
{
	int level;
	int exp;
	int gold;

	// ��ü�� ���¸� ������ �ڷᱸ�� ����
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

	// ���¸� �����ϰ� ��ū ���
	int save()
	{
		Memento* m = new Memento(level, gold, exp);
		memento.push_back(m);
		return memento.size() - 1;
	}
	// ��ū���� ���� ����
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

	// ����������� ������ ��ū �����ʿ�
	int token = user.save();
	user.attack();

	user.load(token);
}
