// 2_������2
#include <iostream>
#include <vector>
using namespace std;

#if 0
// IObserver.h �� �̵��ؾ� �մϴ�.
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
    // 1. ��ӵ� ������ ��� DLL�� �����Ѵ�.
    IoEnumFiles("C:\\plugin", "*.dll", LoadModule, this);
  }

  // �Ʒ� �Լ��� static �̾�� �ϴ� ������ �����ؾ� �մϴ�.
  static int LoadModule(string name, void* param)
  {
    cout << name << endl;

    // 2. DLL�� �ε��Ѵ�.
    void* addr = IoLoadModule(name);        // dlopen

    // 3. ��ӵ� �Լ��� ã�´�.
    typedef IObserver* (*FP)();

    FP f = (FP)IoGetFunctionAddress(addr, "CreateGraph");

    // 4. �׷��� ����
    IObserver* p = f();

    // 5. �����ڷ� ����Ѵ�.
    Subject* self = static_cast<Subject*>(param);
    self->attach(p);

    return 1; // ��� �����ش޶�.
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

      // ��� �����ڿ� �˷��ش�.
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