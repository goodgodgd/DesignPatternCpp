// Command ������ �̿��� Undo�� Redo�� �����غ���!
// �ռ� ������ ����: Ŭ������ �ڵ� �ߺ��� ����
//		excute�� ���� �� �����

#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Shape
{
public:
	virtual void draw() { cout << "Shape draw" << endl; }
};

class Rect : public Shape
{
public:
	void draw() { cout << "Rect draw" << endl; }
};

class Circle : public Shape
{
public:
	void draw() { cout << "Circle draw" << endl; }
};

//--------------------------------------------------
// ��� ����� ��üȭ �Ѵ�.
struct ICommand
{
	virtual void execute() = 0;

	// �������̽� ���ο��� �⺻ ������ ������ �� �ִٸ�
	// �ڵ��� �ߺ��� ������ �� �ִ�. - Java 8�� �߰��Ǿ����ϴ�.
	virtual void undo() {}
	virtual bool canUndo() { return false; }

	virtual ~ICommand() {}
};

// ������ �߰��ϴ� ����� �θ� Ŭ���� ����
class AddCommand : public ICommand
{
	vector<Shape*>& v;
public:
	AddCommand(vector<Shape*>& p) : v(p) {}

	// excute() v�� push_back�ϴ� ���� ���������� ������ �ִ����� �޶�����. - ���뼺�� ������
	// �θ��� ����: AddCommand�̱� ������ ���ϴ� ����� �θ��ؾ��Ѵ�.

	// ���丮 �޼ҵ� ����
	//	- ���ø� �޼ҵ� ������ ����ε�, �ڽ��� �������ϴ� �����Լ��� �˰����� ������ �ƴ� ��ü�� ������ ��
	virtual Shape* createShape() = 0;

	virtual void execute() { v.push_back(createShape()); }
	virtual bool canUndo() { return true; }
	virtual void undo()
	{
		Shape* p = v.back();      // ������ ���
		v.pop_back();
		delete p;
	}
};

// �簢���� �߰��ϴ� ���
class AddRectCommand : public AddCommand
{
public:
	AddRectCommand(vector<Shape*>& p) : AddCommand(p) {}

	// v�� push_back�ϴ� ���� �����ϴ� ������ �ִ����� �޶�����.
	// �θ��� ����: AddCommand�̱� ������ ���ϴ� ����� �θ��ؾ��Ѵ�.
	Shape* createShape() { return new Rect; }
};

class AddCircleCommand : public AddCommand
{
public:
	AddCircleCommand(vector<Shape*>& p) : AddCommand(p) {}
	Shape* createShape() { return new Circle; }
};

class DrawCommand : public ICommand
{
	vector<Shape*>& v;
public:
	DrawCommand(vector<Shape*>& p) : v(p) {}
	virtual void execute()
	{
		for (Shape* e : v)
			e->draw();
	}
};

#if 0
int main()
{
	vector<Shape*> v;
	stack<ICommand*> undo;
	stack<ICommand*> redo;

	while (1)
	{
		int cmd;
		cin >> cmd;

		ICommand* pCommand = 0;

		if (cmd == 1)      pCommand = new AddRectCommand(v);
		else if (cmd == 2) pCommand = new AddCircleCommand(v);
		else if (cmd == 9) pCommand = new DrawCommand(v);
		else if (cmd == 8)
		{
			pCommand = redo.top();
			redo.pop();
		}
		else if (cmd == 0) {
			pCommand = undo.top(); // �޴°Ͱ� ���°��� �и��ϴ� ���� ���ܾ������� ����
			undo.pop();

			pCommand->undo();
			redo.push(pCommand);

			continue;
		}

		if (pCommand) {
			pCommand->execute();
			if (pCommand->canUndo())
				undo.push(pCommand);
		}
	}
}
#endif

// ��ũ�� Ŀ�ǵ� : ���� ����� ���� ���
// �������� Composite ������ Ȱ���
class MacroCommand : public ICommand
{
	vector<ICommand*> v;
public:
	void addCommand(ICommand* p) { v.push_back(p); }
	virtual void excute()
	{
		for (ICommand* e : v)
			e->execute();
	}
};

int main()
{
	vector<Shape*> v;
	stack<ICommand*> undo;
	stack<ICommand*> redo;

	MacroCommand* p = new MacroCommand;
	p->addCommand(new Rect);
	p->addCommand(new Circle);
	p->addCommand(new Rect);

	while (1)
	{
		int cmd;
		cin >> cmd;

		ICommand* pCommand = 0;

		if (cmd == 1)      pCommand = new AddRectCommand(v);
		else if (cmd == 2) pCommand = new AddCircleCommand(v);
		else if (cmd == 9) pCommand = new DrawCommand(v);
		else if (cmd == 8)
		{
			pCommand = redo.top();
			redo.pop();
		}
		else if (cmd == 0) {
			pCommand = undo.top(); // �޴°Ͱ� ���°��� �и��ϴ� ���� ���ܾ������� ����
			undo.pop();

			pCommand->undo();
			redo.push(pCommand);

			continue;
		}

		if (pCommand) {
			pCommand->execute();
			if (pCommand->canUndo())
				undo.push(pCommand);

			// delete pCommand;
		}
	}
}
