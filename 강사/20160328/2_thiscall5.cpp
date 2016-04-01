// 2_thiscall5.cpp
// http://d.pr/f/17nrr
// ioacademy.h
#include <string>
#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

#include <map>

class Clock;  // ���� ���� - ������ ������ ��� �����ʹ� ��� ����

class Clock
{
  string name;
  static map<int, Clock*> this_map;

public:
  Clock(string s) : name(s) {}

  void start(int ms)
  {
    int id = IoSetTimer(ms, timerHandler);

    this_map[id] = this;
    // id ���� �̿��� ��ü�� �ּҸ� �����Ѵ�.
  }

  static void timerHandler(int id)
  {
    Clock* self = this_map[id];

    cout << self->name << endl;
  }
};

// http://d.pr/n/191Lz
// static ��� ������ �ܺ� ���Ǹ� �ؾ� �մϴ�(�ҽ� ����) 
map<int, Clock*> Clock::this_map;



int main()
{
  Clock c1("AAA");
  Clock c2("\tBBB");

  c1.start(1000);   // 1�ʿ� �ѹ��� �̸��� ����ؾ� �մϴ�.
  c2.start(500);

  IoProcessMessage();
}

#if 0
void foo(int id)
{
  cout << "foo: " << id << endl;
}

int main()
{
  int n1 = IoSetTimer(1000, foo);
  int n2 = IoSetTimer(500, foo);

  IoProcessMessage();
}
#endif
