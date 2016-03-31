// 컨테이너(복합 객체)에 작용하는 패턴 2가지
//		복합 객체: 자신 내부에 여러 객체를 가지고 있음
// 반복자: 컨테이너나 복합 객체의 내부 구조에 상관없이 요소를 열거
// 방문자: 컨테이나와 복합 객체의 내부 구조에 상관없이 요소를 연산

// 복합 객체를 구성하는 방법 - menu, folder: Composite Pattern (복합 패턴)
// - 방문재 패턴은 Composite 패턴과 연계되어서 많이 사용됩니다. (Composite에 기능을 추가할 때)

// 이 예제에서는 팝업 메뉴와 일반 메뉴를 다르게 보여주자.
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>	// getch();
using namespace std;

class PopupMenu;
class MenuItem;

// 메뉴 시스템에 쓰이는 방문자의 인터페이스
struct IMenuVisitor
{
	virtual void visit(PopupMenu* p) = 0;
	virtual void visit(MenuItem* p) = 0;
	virtual ~IMenuVisitor() {}
};

struct IMenuAcceptor
{
	virtual void accept(IMenuVisitor* visitor) = 0;
	virtual ~IMenuAcceptor() {}
};

// 모든 메뉴의 공통의 부모
// IMenuAcceptor 를 popupmenu에서 다중상속보다 Base에서 
class BaseMenu : public IMenuAcceptor
{
	string title;
public:
	BaseMenu(string s) : title(s) {}
	~BaseMenu() {}

	string getTitle() { return title; }
	//----------------------------------------
	void setTitle(const string& s) { title = s; }
	virtual void command() = 0;
	// 반드시 command()는 부모인 BaseMenu로부터 와야 한다.
	// 부모 입장에서는 구현해줄 내용이 없고, 자식이 반드시 만들어야 한다면 순수 가상함수가 좋다.
};

class MenuItem : public BaseMenu
{
	// 자식의 공통 부분은 부모로 보낸다.
	//	string title;
public:
	MenuItem(string s) : BaseMenu(s) {}

	virtual void accept(IMenuVisitor* visitor)
	{
		visitor->visit(this);
	}

	void command()
	{
		cout << getTitle() << "메뉴가 선택되었음." << endl;
		getch();
	}
};

#define clrscr() system("cls")		// system("clear")

class PopupMenu : public BaseMenu
{
	// 서브 메뉴 아이템 목록에는 MenuItem과 PopupMenu 두 가지 다 들어갈 수 있어야 한다. -> 공통의 부모 필요
	vector<BaseMenu*> v;	// 재귀적 합성: 자기 자신을 포함할 수 있는 설계
	// 자식의 공통 부분은 부모로 보낸다.
	//	string title;
public:
	PopupMenu(string s) : BaseMenu(s) {}

	virtual void accept(IMenuVisitor* visitor)
	{
		visitor->visit(this);
		// 내가 포함하고 있는 모든 메뉴들에 대해서도 방문자를 전달해야 한다. - 핵심!!
		// 그냥 MenuItem과는 다른 기능
		for (BaseMenu* e : v)	// Range-for
			e->accept(visitor);
	}

	void addMenu(BaseMenu* p) { v.push_back(p); }

	void command()
	{
		while (1)
		{
			// 화면 클리어
			clrscr();
			int sz = v.size();
			for (int i = 0; i < sz; i++)
				cout << i + 1 << ", " << v[i]->getTitle() << endl;
			cout << sz + 1 << ". 상위 메뉴로" << endl;

			cout << "메뉴를 선택하세요. >> ";
			int cmd;
			cin >> cmd;

			// 하위 메뉴의 loop을 종료한다.
			if (cmd == sz + 1)
				break;

			if (cmd < 1 || cmd > sz + 1) // 잘못된 입력
				continue;

			// 선택된 메뉴를 실행한다.
			// 하위 메뉴를 보여준다.
			v[cmd - 1]->command();
		}
	}
};

// 메뉴 시스템에 다양한 기능을 추가하는 방문자들을 제공하면 됩니다.
class TitleDecorationVisitor : public IMenuVisitor
{
public:
	virtual void visit(MenuItem* p) {}
	virtual void visit(PopupMenu* p)
	{
		string s = p->getTitle();
		s = s + " >";
		p->setTitle(s);		// 캡슐화 전략 위배
							// 기존에 설계했던 
		// 어? set이 없네? 방문자의 문제는 캡슐화 전략의 위배, 기존 시스템의 설계에서는 메뉴 이름을 바꿀 수 있는 set이 필요없었다.
	}
};

int main()
{
	PopupMenu* menubar = new PopupMenu("MENUBAR");
	PopupMenu* p1 = new PopupMenu("화면 설정");
	PopupMenu* p2 = new PopupMenu("소리 설정");

	menubar->addMenu(p1);
	menubar->addMenu(p2);

	p1->addMenu(new MenuItem("해상도 설정"));
	p1->addMenu(new MenuItem("색상 설정"));
	p1->addMenu(new MenuItem("기타 설정"));

	p2->addMenu(new MenuItem("볼륨 설정"));
	p2->addMenu(new MenuItem("음색 설정"));

	// 기존 Menu관련 클래스를 크게 변화시키지 않고 모든 팝업메뉴에 > 추가
	TitleDecorationVisitor v;
	menubar->accept(&v);

	menubar->command();
}
