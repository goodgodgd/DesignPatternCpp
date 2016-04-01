// 4_데코레이터 패턴
#include <iostream>
using namespace std;

class Ticket
{
public:
  void print()
  {
    cout << "작은 음악회 - 2016.12.25" << endl;
  }
};

// 상속: 기존 클래스에 기능을 추가할 수 있습니다.
class Ad1 : public Ticket
{
public:
  void print()
  {
    Ticket::print();                 // 원래 기능을 사용
    cout << "자동차 광고" << endl;   // 기능 추가
  }
};

class Ad2 : public Ad1
{
public:
  void print()
  {
    cout << "TV 광고" << endl;
    Ad1::print();
  }
};

// 상속을 통한 기능의 추가
// - 계층 구조가 만들어진 이후에, 요구 사항의 변경에 대응하기 어렵다.
// - 기능을 실행 시간에 변경을 하는 것이 불가능하다.
//    : 정적인 기능의 추가

int main()
{
  Ad2 t;
  t.print();
}


