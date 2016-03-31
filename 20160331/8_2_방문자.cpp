// �����̳�(���� ��ü)�� �ۿ��ϴ� ���� 2����
//		���� ��ü: �ڽ� ���ο� ���� ��ü�� ������ ����
// �ݺ���: �����̳ʳ� ���� ��ü�� ���� ������ ������� ��Ҹ� ����
// �湮��: �����̳��� ���� ��ü�� ���� ������ ������� ��Ҹ� ����

// ���� ��ü�� �����ϴ� ��� - menu, folder: Composite Pattern (���� ����)
// - �湮�� ������ Composite ���ϰ� ����Ǿ ���� ���˴ϴ�. (Composite�� ����� �߰��� ��)

// �� ���������� �˾� �޴��� �Ϲ� �޴��� �ٸ��� ��������.
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>	// getch();
using namespace std;

class PopupMenu;
class MenuItem;

// �޴� �ý��ۿ� ���̴� �湮���� �������̽�
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

// ��� �޴��� ������ �θ�
// IMenuAcceptor �� popupmenu���� ���߻�Ӻ��� Base���� 
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
	// �ݵ�� command()�� �θ��� BaseMenu�κ��� �;� �Ѵ�.
	// �θ� ���忡���� �������� ������ ����, �ڽ��� �ݵ�� ������ �Ѵٸ� ���� �����Լ��� ����.
};

class MenuItem : public BaseMenu
{
	// �ڽ��� ���� �κ��� �θ�� ������.
	//	string title;
public:
	MenuItem(string s) : BaseMenu(s) {}

	virtual void accept(IMenuVisitor* visitor)
	{
		visitor->visit(this);
	}

	void command()
	{
		cout << getTitle() << "�޴��� ���õǾ���." << endl;
		getch();
	}
};

#define clrscr() system("cls")		// system("clear")

class PopupMenu : public BaseMenu
{
	// ���� �޴� ������ ��Ͽ��� MenuItem�� PopupMenu �� ���� �� �� �� �־�� �Ѵ�. -> ������ �θ� �ʿ�
	vector<BaseMenu*> v;	// ����� �ռ�: �ڱ� �ڽ��� ������ �� �ִ� ����
	// �ڽ��� ���� �κ��� �θ�� ������.
	//	string title;
public:
	PopupMenu(string s) : BaseMenu(s) {}

	virtual void accept(IMenuVisitor* visitor)
	{
		visitor->visit(this);
		// ���� �����ϰ� �ִ� ��� �޴��鿡 ���ؼ��� �湮�ڸ� �����ؾ� �Ѵ�. - �ٽ�!!
		// �׳� MenuItem���� �ٸ� ���
		for (BaseMenu* e : v)	// Range-for
			e->accept(visitor);
	}

	void addMenu(BaseMenu* p) { v.push_back(p); }

	void command()
	{
		while (1)
		{
			// ȭ�� Ŭ����
			clrscr();
			int sz = v.size();
			for (int i = 0; i < sz; i++)
				cout << i + 1 << ", " << v[i]->getTitle() << endl;
			cout << sz + 1 << ". ���� �޴���" << endl;

			cout << "�޴��� �����ϼ���. >> ";
			int cmd;
			cin >> cmd;

			// ���� �޴��� loop�� �����Ѵ�.
			if (cmd == sz + 1)
				break;

			if (cmd < 1 || cmd > sz + 1) // �߸��� �Է�
				continue;

			// ���õ� �޴��� �����Ѵ�.
			// ���� �޴��� �����ش�.
			v[cmd - 1]->command();
		}
	}
};

// �޴� �ý��ۿ� �پ��� ����� �߰��ϴ� �湮�ڵ��� �����ϸ� �˴ϴ�.
class TitleDecorationVisitor : public IMenuVisitor
{
public:
	virtual void visit(MenuItem* p) {}
	virtual void visit(PopupMenu* p)
	{
		string s = p->getTitle();
		s = s + " >";
		p->setTitle(s);		// ĸ��ȭ ���� ����
							// ������ �����ߴ� 
		// ��? set�� ����? �湮���� ������ ĸ��ȭ ������ ����, ���� �ý����� ���迡���� �޴� �̸��� �ٲ� �� �ִ� set�� �ʿ������.
	}
};

int main()
{
	PopupMenu* menubar = new PopupMenu("MENUBAR");
	PopupMenu* p1 = new PopupMenu("ȭ�� ����");
	PopupMenu* p2 = new PopupMenu("�Ҹ� ����");

	menubar->addMenu(p1);
	menubar->addMenu(p2);

	p1->addMenu(new MenuItem("�ػ� ����"));
	p1->addMenu(new MenuItem("���� ����"));
	p1->addMenu(new MenuItem("��Ÿ ����"));

	p2->addMenu(new MenuItem("���� ����"));
	p2->addMenu(new MenuItem("���� ����"));

	// ���� Menu���� Ŭ������ ũ�� ��ȭ��Ű�� �ʰ� ��� �˾��޴��� > �߰�
	TitleDecorationVisitor v;
	menubar->accept(&v);

	menubar->command();
}
