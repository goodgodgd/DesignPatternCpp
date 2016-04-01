// 3_통보센터(NotificationCenter)

#include <functional> // function
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// C++ 에서 callback 을 등록하는 방법은 2가지 형태
// 1. 인터페이스 기반의 객체 등록
//   - 전통적인 디자인 패턴 (객체 지향), 관찰자
// 2. 함수 포인터(function<>)으로 함수 등록
//   - 통보 센터


void foo() { cout << "foo" << endl; }
void goo(int n) { cout << "goo : " << n << endl; }
class Dialog {
public:
  void warning() { cout << "Warning Dialog" << endl; }
};


// 아이폰(맥)에 있는 통보 센터를 만들어 봅시다.
class NotificationCenter
{
  typedef function<void()> HANDLER;

  map<string, vector<HANDLER>> notifi_map;
public:
  void addObserver(string key, HANDLER handler)
  {
    notifi_map[key].push_back(handler);
  }

  void postNotificationWithName(string key)
  {
    vector<HANDLER>& v = notifi_map[key];
    for (HANDLER e : v)
      e();
  }

  // global 센터의 개념을 도입하자.
  // Singleton: 오직 한개의 객체를 생성하고 어디서든 동일한 방법으로 접근할 수 있도록
  //            한다.
  static NotificationCenter& defaultCenter()
  {
    static NotificationCenter instance;
    return instance;
  }
};

// 중재자(Mediator) 패턴
// - 복잡한 객체간의 관계를 단순화 시켜주는 클래스
int main()
{
  NotificationCenter& globalCenter = NotificationCenter::defaultCenter();

  NotificationCenter nc;
  nc.addObserver("LOWBATTERY", &foo);
  nc.addObserver("LOWBATTERY", bind(&goo, 5));

  Dialog dialog;
  nc.addObserver("LOWBATTERY", bind(&Dialog::warning, &dialog));


  // 이제 배터리를 체크하는 모듈에서
  nc.postNotificationWithName("LOWBATTERY");
}











