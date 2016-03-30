// 1. 인터페이스 기반의 리스너 개념: Java, Android
// Observe Pattern, 관찰자 패턴

#include <vector>
#include <iostream>
using namespace std;

// 메뉴를 처리하고 싶은 모든 클래스는 아래 인터페이스를 구현해야 한다.
struct IMenuListener
{
	virtual void onCommand(int id) = 0;
	virtual ~IMenuListener() {}
};

class MenuItem
{
	int id;
	vector<IMenuListener*> v;
public:
	MenuItem(int i) : id(i) {}

	void addListener(IMenuListener* p)
	{
		v.push_back(p);
	}
	virtual void command()
	{
		// 등록된 모든 객체에게 알려준다. -> 관찰자 패턴
		for (int i = 0; i< v.size(); i++)
			v[i]->onCommand(id);
	}
};

class Window : public IMenuListener
{
public:
	virtual void onCommand(int id)
	{ cout << "window onCommand" << endl; }

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
	Window window;

	MenuItem m1(11);
	m1.addListener(&dialog);
	m1.addListener(&window);
	m1.command();
}
