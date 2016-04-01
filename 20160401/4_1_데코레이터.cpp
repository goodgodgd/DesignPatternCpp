
#include <iostream>
using namespace std;


class Ticket
{
public:
	void print()
	{
		cout << "작은 음악회 - 2016.12.25" << endl;
	}
};

// 티켓에 광고 기능을 추가하고 싶다.
class Ad1 : public Ticket
{
public:
	void print()
	{
		Ticket::print();	// 원래의 기능을 이용
		cout << "자동차 광고" << endl;
	}
};

class Ad2 : public Ad1
{
public:
	void print()
	{
		Ad1::print();	// 원래의 기능을 이용
		cout << "TV 광고" << endl;
	}
};

// 상속을 통한 기능의 추가
// - 계층 구조가 만들어진 후에, 요구 사항의 변경에 대응하기 어렵다.
// - 기능을 실행시간에 변경하는 것이 불가능하다.
//		: 정적인 기능의 추가
// - 객체에 대한 수정 아니라 타입에 대한 수정, 정적 변화

int main()
{
	Ticket t;
	t.print();

	Ad1 a1;
	a1.print();

	Ad2 a2;
	a2.print();
}