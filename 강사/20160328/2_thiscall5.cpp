// 2_thiscall5.cpp
// http://d.pr/f/17nrr
// ioacademy.h
#include <string>
#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

#include <map>

class Clock;  // 전방 선언 - 완전한 선언이 없어도 포인터는 사용 가능

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
    // id 값을 이용해 객체의 주소를 저장한다.
  }

  static void timerHandler(int id)
  {
    Clock* self = this_map[id];

    cout << self->name << endl;
  }
};

// http://d.pr/n/191Lz
// static 멤버 변수는 외부 정의를 해야 합니다(소스 파일) 
map<int, Clock*> Clock::this_map;



int main()
{
  Clock c1("AAA");
  Clock c2("\tBBB");

  c1.start(1000);   // 1초에 한번씩 이름을 출력해야 합니다.
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
