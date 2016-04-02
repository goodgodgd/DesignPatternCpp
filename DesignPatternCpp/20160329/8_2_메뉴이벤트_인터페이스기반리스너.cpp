// 1. 인터페이스 기반의 리스너 개념: Java, Android

//	인터페이스: 분기문 필요 => 객체마다 직접 함수 매핑하는 핸들러가 낫다.

#include <iostream>
using namespace std;

// 메뉴를 처리하고 싶은 모든 클래스는 아래 인터페이스를 구현해야 한다.
// 라는 약속이 필요
struct IMenuListener
{
	virtual void onCommand(int id) = 0;
	virtual ~IMenuListener() {}
};

// 가변성을 외부 인터페이스 기반 클래스로 빼놓은 것 => 전략 패턴
class MenuItem
{
	int id;
	IMenuListener* pListener;
public:
	MenuItem(int i) : pListener(0), id(i) {}

	void setListener(IMenuListener* p) { pListener = p; }
	// addListener

	// 이것은 라이브러리 이므로 여기다 구현할 수는 없다.
	virtual void command()
	{
		// 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
		// "객체가 외부로 이벤트를 발생한다." 라고 표현
		if (pListener)
			pListener->onCommand(id);	// 객체를 구별하는 ID를 보내야 한다.
	}
};

class Dialog : public IMenuListener
{
public:
	virtual void onCommand(int id)
	{
		// 인터페이스 단점: 어떤 객체로부터 이벤트가 발생했는지 여부를 반드시 분기하는 코드가 필요하다.
		// 따라서 핸들러가 인터페이스가 훨 낫다.
		// Java8에서는 핸들러를 처리하기위 method reference 라는 것을 제공한다.
		switch (id)
		{
		case 11: open(); break;
		case 12: close(); break;
		}
	}

	void open() { cout << "Dialog open" << endl; }
	void close() { cout << "Dialog close" << endl; }
};

int main()
{
	Dialog dialog;

	MenuItem m1(11);	// 객체 ID 지정
	MenuItem m2(12);
	m1.setListener(&dialog);
	m2.setListener(&dialog);
	m1.command();
	m2.command();
}
