// 8_메뉴이벤트6
#include <iostream>
using namespace std;

struct ICommand
{
  virtual void execute() = 0;
  virtual ~ICommand() {}
};

class FunctionCommand : public ICommand
{
  typedef void(*HANDLER)();
  HANDLER handler;
public:
  FunctionCommand(HANDLER h) : handler(h) {}

  void execute() { handler(); }
};

template <typename T>
class MemberCommand : public ICommand
{
  typedef void(T::*HANDLER)();
  HANDLER handler;
  T* object;
public:
  MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}
  void execute() { (object->*handler)(); }
};

template <typename T>
MemberCommand<T>* cmd(void (T::*f)(), T* o)
{
  return new MemberCommand<T>(f, o);
}

FunctionCommand* cmd(void(*f)())
{
  return new FunctionCommand(f);
}
//---------------------------------------
class MenuItem
{
  ICommand* pCommand;
public:
  void setHandler(ICommand* p) { pCommand = p; }

  void command()
  {
    if (pCommand)
      pCommand->execute();
  }
};

class Dialog
{
public:
  void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

int main()
{
  Dialog dialog;

  MenuItem m;
  m.setHandler(cmd(&Dialog::close, &dialog));
  m.command();

  m.setHandler(cmd(&foo));
  m.command();
}