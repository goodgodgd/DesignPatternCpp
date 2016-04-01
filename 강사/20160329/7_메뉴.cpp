// 7_메뉴
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>  // getch();
using namespace std;

// Composite Pattern
// : 복합 객체를 구성하는 방법

// 1. 복합 객체(PopupMenu)는 개별 객체(MenuItem)과 복합객체를 모두 보관할 수 있다
//   => 복합 객체와 단일 객체간의 공통의 부모가 존재한다.

// 2. 복합 객체와 개별 객체가 동일시 된다. (사용법이 같다, 모두 command()가 있다)
//   => command() 반드시 부모 클래스로부터 제공되어야 한다. - 다형성


// 모든 메뉴의 공통의 부모
class BaseMenu
{
  string title;
public:
  BaseMenu(string s) : title(s) {}
  virtual ~BaseMenu() {}

  string getTitle() { return title; }

  virtual void command() = 0;
  // 반드시 command()는 부모인 BaseMenu로부터 와야 한다.
  // 부모 입장에서는 구현해줄 내용이 없고, 자식이 반드시 만들어야 한다면
  // 순수 가상함수가 좋다.
};

class MenuItem : public BaseMenu
{
public:
  MenuItem(string s) : BaseMenu(s) {}

  void command()
  {
    cout << getTitle() << " 메뉴가 선택되었음." << endl;
    getch();
  }
};

#define clrscr() system("cls")      // system("clear")

// 아래 클래스가 핵심입니다.
class PopupMenu : public BaseMenu
{
  vector<BaseMenu*> v;  // 재귀적 합성
public:
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

  menubar->command();
}