// Memento
// 메멘토 패턴: 객체의 상태를 저장하고 복구하는 패턴

#include <iostream>
#include <vector>
using namespace std;

// Command: 행위의 캡술화
// Memento: 객체의 상태를 캡슐화, 스냅샷 제공
// 핵심: 내부적으로 캡슐화, 기존 코드 수정 발생하지 않는다. (내부 struct)


// 게임에서의 저장 복원을 생각해보자
class User
{
	int level;
	int exp;
	int gold;

	// 객체의 상태를 결정하는 필드를 캡슐화 한다.
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

	// 어느시점으로 가는지 토큰 제공필요
	int token = user.save();
	user.attack();

	user.load(token);
}
