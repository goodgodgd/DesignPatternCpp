// 2_관찰자2
#include <iostream>
#include <vector>
using namespace std;

#if 0
// IObserver.h 로 이동해야 합니다.
struct IObserver
{
  virtual void onUpdate(void* data) = 0;
  virtual ~IObserver() {}
};
#endif

#include "IObserver.h"
#include "ioacademy.h"
using namespace ioacademy;

class Subject
{
  vector<IObserver*> v;
public:
  //------------------
  Subject()
  {
    // 1. 약속된 폴더의 모든 DLL을 열거한다.
    IoEnumFiles("C:\\plugin", "*.dll", LoadModule, this);
  }

  // 아래 함수가 static 이어야 하는 이유를 이해해야 합니다.
  static int LoadModule(string name, void* param)
  {
    cout << name << endl;

    // 2. DLL을 로드한다.
    void* addr = IoLoadModule(name);        // dlopen

    // 3. 약속된 함수를 찾는다.
    typedef IObserver* (*FP)();

    FP f = (FP)IoGetFunctionAddress(addr, "CreateGraph");

    // 4. 그래프 생성
    IObserver* p = f();

    // 5. 관찰자로 등록한다.
    Subject* self = static_cast<Subject*>(param);
    self->attach(p);

    return 1; // 계속 열거해달라.
  }

  //------------------
  void attach(IObserver* p) { v.push_back(p); }
  void detach(IObserver* p) {}

  void notify(void *p)
  {
    for (IObserver* e : v)
      e->onUpdate(p);
  }
};




class Table : public Subject
{
  int data[5];
public:
  Table() { memset(data, 0, sizeof(data)); }

  void edit()
  {
    while (1)
    {
      int index;
      cout << "index: "; cin >> index;
      cout << "data: ";  cin >> data[index];

      // 모든 관찰자에 알려준다.
      notify(data);
    }
  }

};

class PieGraph : public IObserver
{
public:
  virtual void onUpdate(void* p)
  {
    int* data = static_cast<int*>(p);
    cout << "******** Pie Graph *********" << endl;
    for (int i = 0; i < 5; ++i)
      cout << i << " : " << data[i] << endl;
  }
};

class BarGraph : public IObserver
{
public:
  virtual void onUpdate(void* p)
  {
    int* data = static_cast<int*>(p);
    cout << "******** Bar Graph *********" << endl;
    for (int i = 0; i < 5; ++i)
      cout << i << " : " << data[i] << endl;
  }
};

int main()
{
  Table table;

  PieGraph pg;
  BarGraph bg;

  table.attach(&pg);
  table.attach(&bg);

  table.edit();
}