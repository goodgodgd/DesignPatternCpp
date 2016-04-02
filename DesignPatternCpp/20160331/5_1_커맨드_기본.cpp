// Command 패턴을 이용해 Undo와 Redo를 구현해보자!
// 명령을 stack에 쌓은 다음 최근 명령을 무효화
// 문제: 명령을 저장하는 것이 불가능하다.
// 중간층의 원리: 명령을 객체로 만들자.
// Command Pattern: 명령을 캡슐화
// 다양한 명령이 있지만 공통의 부모로 묶어서 스택에 저장

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

// 사각형을 추가하는 명령
class AddRectCommand : public ICommand
{
	vector<Shape*>& v;
public:
	AddRectCommand(vector<Shape*>& p) : v(p) {}
	virtual void execute() { v.push_back(new Rect); }

	virtual bool canUndo() { return true; }
	virtual void undo()
	{
		Shape* p = v.back();      // 마지막 요소
		v.pop_back();

		delete p;
	}
};

class AddCircleCommand : public ICommand
{
	vector<Shape*>& v;
public:
	AddCircleCommand(vector<Shape*>& p) : v(p) {}
	virtual void execute() { v.push_back(new Circle); }

	virtual bool canUndo() { return true; }
	virtual void undo()
	{
		Shape* p = v.back();      // 마지막 요소
		v.pop_back();

		delete p;
	}
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

			// delete pCommand;
		}
	}
}

// 문제: ICommand 를 상속받는 클래스에 중복코드가 많다.
