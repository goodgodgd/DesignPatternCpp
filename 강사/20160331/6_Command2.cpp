// 6_Command2
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Command 패턴: 명령을 캡슐화
class Shape {
public:
  virtual void draw() { cout << "Shape draw" << endl; }
};

class Rect : public Shape
{
public:
  virtual void draw() { cout << "Rect draw" << endl; }
};

class Circle : public Shape
{
public:
  virtual void draw() { cout << "Circle draw" << endl; }
};

struct ICommand
{
  virtual void execute() = 0;
  virtual void undo() {}
  virtual bool canUndo() { return false; }

  virtual ~ICommand() {}
};

// 도형을 추가하는 명령의 부모 클래스
class AddCommand : public ICommand
{
  vector<Shape*>& v;
public:
  AddCommand(vector<Shape*>& p) : v(p) {}

  // 팩토리 메소드 패턴
  // - 템플릿 메소드 패턴의 모양인데, 자식이 재정의하는 가상함수가
  //   알고리즘의 변경이 아닌 객체의 생성일 때.
  virtual Shape* createShape() = 0;

  virtual void execute() { v.push_back(createShape()); }
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

// 매크로 커맨드 : 여러 명령을 묶는 명령 - Composite
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
    else if (cmd == 8) {
      pCommand = redo.top();
      redo.pop();
    }
    else if (cmd == 0) {
      pCommand = undo.top();
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