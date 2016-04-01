// 1_방문자
// 컨테이너(복합 객체)에 작용하는 패턴 2가지
// 반복자: 컨테이너나 복합 객체의 내부 구조에 상관없이 요소를 열거
// 방문자: 컨테이너와 복합 객체의 내부 구조에 상관없이 요소에 연산

// 복합 객체를 구성하는 방법 - menu, folder: Composite Pattern
// - 방문자 패턴은 Composite 패턴과 연계되어서 많이 사용됩니다.
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>  // getch();
using namespace std;

// 메뉴 시스템에 적용되는 방문자의 인터페이스
class PopupMenu;
class MenuItem;
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

class BaseMenu : public IMenuAcceptor
{
  string title;
public:
  BaseMenu(string s) : title(s) {}
  virtual ~BaseMenu() {}

  string getTitle() { return title; }
  //---------
  void setTitle(const string& s) { title = s; }
  //---------

  virtual void command() = 0;
};

class MenuItem : public BaseMenu
{
public:
  MenuItem(string s) : BaseMenu(s) {}

  virtual void accept(IMenuVisitor* visitor)
  {
    visitor->visit(this);   // 자신을 전달한다.
  }

  void command()
  {
    cout << getTitle() << " 메뉴가 선택되었음." << endl;
    getch();
  }
};

#define clrscr() system("cls")      // system("clear")

class PopupMenu : public BaseMenu
{
  vector<BaseMenu*> v;  // 재귀적 합성
public:

  virtual void accept(IMenuVisitor* visitor)
  {
    visitor->visit(this);

    // 내가 포함하고 있는 모든 메뉴들에 대해서도 방문자를 전달해야 한다. - 핵심!!!
    for (BaseMenu* e : v) // Range-for
      e->accept(visitor);
  }
  
  PopupMenu(string s) : BaseMenu(s) {}

  void addMenu(BaseMenu* p) { v.push_back(p); }

  void command()
  {
    while (1)
    {
      clrscr();

      int sz = v.size();
      for (int i = 0; i < sz; i++)
        cout << i + 1 << ". " << v[i]->getTitle() << endl;
      cout << sz + 1 << ". 상위 메뉴로" << endl;

      cout << "메뉴를 선택하세요. >> ";
      int cmd;
      cin >> cmd;

      if (cmd == sz + 1)
        break;

      if (cmd < 1 || cmd > sz + 1)  // 잘못된 입력
        continue;

      // 선택된 메뉴를 실행한다.
      v[cmd - 1]->command();
    }
  }
};

//--------------------------------------
// 메뉴 시스템에 다양한 기능을 추가하는 방문자들을 제공하면 됩니다.
class TitleDecorationVisitor : public IMenuVisitor
{
public:
  virtual void visit(MenuItem* p) {}
  virtual void visit(PopupMenu* p) 
  {
    string s = p->getTitle();
    s = s + "  >";
    p->setTitle(s);  // 캡슐화 전략 위배
                     // 기존에 설계했던 정책을 바꿔야 한다.
  }
};






int main()
{
  PopupMenu* menubar = new PopupMenu("MENUBAR");
  PopupMenu* p1 = new PopupMenu("화면 설정");
  PopupMenu* p2 = new PopupMenu("소리 설정");

  menubar->addMenu(p1);
  p1->addMenu(p2);

  p1->addMenu(new MenuItem("해상도 설정"));
  p1->addMenu(new MenuItem("색상 설정"));
  p1->addMenu(new MenuItem("기타 설정"));

  p2->addMenu(new MenuItem("볼륨 설정"));
  p2->addMenu(new MenuItem("음색 설정"));

  TitleDecorationVisitor v;
  menubar->accept(&v);
  menubar->command();
}