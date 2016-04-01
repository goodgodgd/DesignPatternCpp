#include <iostream>
using namespace std;
// 8_메뉴이벤트5

// 일반 함수와 모든 클래스의 멤버 함수를 보관하는 범용적 함수 포인터 타입을
// 만들어보자.

// 3. A와 B를 묶기 위해서는 공통의 부모를 제공해야 한다.
//   => FunctionCommand와 MemberCommand의 공통의 부모를 설계하자.
struct ICommand
{
  virtual void execute() = 0;
  virtual ~ICommand() {}
};

// 1. 함수 포인터 개념을 클래스로 래핑해 봅시다.
class FunctionCommand : public ICommand
{
  typedef void(*HANDLER)();
  HANDLER handler;
public:
  FunctionCommand(HANDLER h) : handler(h) {}

  void execute() { handler(); }
};

// 2. 모든 클래스의 멤버 함수의 주소를 담을 수 있는 클래스를 설계해보자.
template <typename T>
class MemberCommand : public ICommand
{
  typedef void(T::*HANDLER)();
  HANDLER handler;
  T* object;
public:
  MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}
  void execute() { (object->*handler)();  }
};

class Dialog
{
public:
  void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

// 4. 클래스 템플릿은 암시적 추론이 불가능하기 때문에 항상 복잡해 보입니다.
//    암시적 추론이 가능한 함수 템플릿으로 헬퍼를 제공합니다.
template <typename T>
MemberCommand<T>* cmd(void (T::*f)(), T* o)
{
  return new MemberCommand<T>(f, o);
}

// 5. 라이브러리 일관성을 위해서 FunctionCommand를 만드는 cmd도 제공합니다.
FunctionCommand* cmd(void(*f)())
{
  return new FunctionCommand(f);
}

int main()
{
  // ICommand* p = new FunctionCommand(&foo);
  ICommand* p = cmd(&foo);
  p->execute();

  Dialog dialog;
  p = cmd(&Dialog::close, &dialog);
  // p = new MemberCommand<Dialog>(&Dialog::close, &dialog);
  p->execute();
}


#if 0
int main()
{
  Dialog dialog;
  MemberCommand<Dialog> mc(&Dialog::close, &dialog);
  mc.execute();

  FunctionCommand fc(&foo);
  fc.execute();
}
#endif

#if 0
// C++에서는 함수 템플릿은 암시적 추론이 가능하지만, 클래스 템플릿은
// 암시적 추론이 불가능합니다.
template<typename T>
void hoo(T a) {}        // 함수 템플릿 - 명시적 추론, 암시적 추론

template <typename T>
class AAA               // 클래스 템플릿 - 명시적 추론
{};

int main()
{
  hoo(10); hoo(3.14);
  AAA<int> aaa;  AAA<double> aaa2;
}
#endif



















