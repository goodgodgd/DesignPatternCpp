// Command 패턴을 이용해 Undo와 Redo를 구현해보자!
// 앞선 예제의 문제: 클래스에 코드 중복이 많다
//		execute만 빼고 다 비슷해

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
// 모든 명령을 객체화 한다.
struct ICommand
{
	virtual void execute() = 0;

	// 인터페이스 내부에서 기본 구현을 제공할 수 있다면
	// 코드의 중복을 방지할 수 있다. - Java 8에 추가되었습니다.
	virtual void undo() {}
	virtual bool canUndo() { return false; }

	virtual ~ICommand() {}
};

// 도형을 추가하는 명령의 부모 클래스 설계
// AddRectCommand와 AddCircleCommand의 공통적인 부분을 부모클래스로 묶는다.
class AddCommand : public ICommand
{
	vector<Shape*>& v;
public:
	AddCommand(vector<Shape*>& p) : v(p) {}

	// execute() 에서 v에 push_back하는 것은 동일하지만 무엇을 넣는지는 달라진다. - 공통성과 가변성
	// execute()는 부모에서만 구현하고 생성 메소드만 순수 가상함수 createShape()으로 만들어 자식으로 뺀다.
	virtual void execute() { v.push_back(createShape()); }
	// 팩토리 메소드 패턴
	//	- 템플릿 메소드 패턴의 모양인데, 자식이 재정의하는 가상함수가 알고리즘의 변경이 아닌 객체의 생성일 때
	virtual Shape* createShape() = 0;

	virtual bool canUndo() { return true; }
	virtual void undo()
	{
		Shape* p = v.back();      // 마지막 요소
		v.pop_back();
		delete p;
	}
};

// 사각형을 추가하는 명령
class AddRectCommand : public AddCommand
{
public:
	AddRectCommand(vector<Shape*>& p) : AddCommand(p) {}
	Shape* createShape() { return new Rect; }
};

// 원을 추가하는 명령
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
			pCommand = undo.top(); // 받는것과 빼는것을 분리하는 것은 예외안정성을 위해
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

#if 0
// 매크로 커맨드 : 여러 명령을 묶는 명령
// 내부적으로 Composite 패턴이 활용됨
class MacroCommand : public ICommand
{
	vector<ICommand*> v;
public:
	void addCommand(ICommand* p) { v.push_back(p); }
	virtual void execute()
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
	p->addCommand(new AddRectCommand(v));
	p->addCommand(new AddCircleCommand(v));
	p->addCommand(new DrawCommand(v));

	p->execute();

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
			pCommand = undo.top(); // 받는것과 빼는것을 분리하는 것은 예외안정성을 위해
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
#endif
