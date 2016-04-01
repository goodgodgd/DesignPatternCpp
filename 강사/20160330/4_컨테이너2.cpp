// 4_컨테이너2

#include <vector>
#include <iostream>
using namespace std;

// 방법 1. object* 기반의 컨테이너
// Java, C#: Object
// Objecive C: NSObject
// MFC: CObject
// Qt:  QObject
class object {
public:
  virtual ~object() {}
};

// 라이브러리 내의 모든 클래스는 object의 자식이어야 한다.
class Dialog : public object {};
class Point : public object {};
class Rect : public object {};

class Integer : public object
{
  int value;
public:
  Integer(int v) : value(v) {}
  int getValue() { return value; }
};

struct node
{
  object* data;
  node* next;
  node(object* a, node* n) : data(a), next(n) {}
};

class slist
{
  node* head;
public:
  slist() : head(0) {}

  // node의 생성자를 잘 활용한 코드 입니다.
  void push_front(object* a) { head = new node(a, head); }
  object* front() { return head->data; }
};

// 단점:
// 1. 타입 안정성이 떨어진다. 실수로 다른 타입을 넣어도 컴파일 시간에 에러가
//    발생하지 않는다.

// 2. 값을 꺼낼 때 항상 해당 타입으로 캐스팅해야 한다.
// 3. 객체가 아닌 표준 타입(primitive type)은 저장할 수 없다.
//    wrapper class가 필요하다. - 표준 타입의 레퍼런스 타입
//    int - Integer
//    double - Double

// 장점:
//  template 을 사용하게 되면, 코드 메모리 오버 헤드가 있다.

int main()
{
  slist s;
  s.push_front(new Point);
  s.push_front(new Point);
  s.push_front(new Point);

  // s.push_front(3); // ?
  s.push_front(new Integer(3));  // auto-boxing

  // s.push_front(new Dialog);  // ??? 실수!!!!

  // int n = s.front(); - auto unboxing
  int n = static_cast<Integer*>(s.front())->getValue();

}