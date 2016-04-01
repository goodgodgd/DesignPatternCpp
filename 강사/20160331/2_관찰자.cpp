// 2_관찰자
#include <iostream>
#include <vector>
using namespace std;

// 1. 관찰자 패턴 개념: 하나의 이벤트를 여러 객체에 전파하는 패턴.
struct IObserver
{
  virtual void onUpdate(void* data) = 0;
  virtual ~IObserver() {}
};

// 모든 Table(관찰의 대상)의 특징은 항상 동일하다.
// -> 부모로 제공하자.

// 정리: 달라지는 것은 가상함수화 해서 자식이 변경, 
//       공통적인 것은 부모 클래스로 만들어서 제공

class Subject
{
  vector<IObserver*> v;
public:
  void attach(IObserver* p) { v.push_back(p); }
  void detach(IObserver* p) {}

  void notify(void *p)
  {
    for (IObserver* e : v)
      e->onUpdate(p);
  }
};

// 관찰의 대상: 표 - (모델이라고 부릅니다)
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