// 8_방문자

// GoF의 디자인 패턴에는 컨테이너에 작용하는 패턴이 두가지 있습니다.
// 1. 반복자: 컨테이너의 내부 구조에 상관없이 요소를 열거한다.
// 2. 방문자: 컨테이너의 내부 구조에 상관없이 요소에 연산을 수행한다.

// 컨테이너3
#include <iostream>
using namespace std;

// 모든 방문자 객체 인터페이스
template <typename T> struct IVisitor
{
  virtual void visit(T& a) = 0;
  virtual ~IVisitor() {}
};

// 모든 방문의 대상(컨테이너)의 인터페이스
template <typename T> struct IAcceptor
{
  virtual void accept(IVisitor<T>* visitor) = 0;
  virtual ~IAcceptor() {}
};

template <typename T>
struct node
{
  T data;
  node* next;
  node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist : public IAcceptor<T>
{
  node<T>* head;
public:
  // 아래 함수만 정확하게 이해하면 됩니다.
  virtual void accept(IVisitor<T>* visitor)
  {
    node<T>* current = head;
    while (current)
    {
      visitor->visit(current->data);
      current = current->next;
    }
  }
  
  slist() : head(0) {}

  void push_front(const T& a) { head = new node<T>(a, head); }
  T& front() { return head->data; }
};

// 모든 요소를 두배로 하는 방문자
template <typename T>
struct TwiceVisitor : public IVisitor<T>
{
public:
  virtual void visit(T& a) { a *= 2; }
};

template <typename T>
struct ShowVisitor : public IVisitor<T>
{
public:
  virtual void visit(T& a) { cout << a << endl; }
};

#include <algorithm>  // for_each
#include <list>

#include <ppl.h>
using namespace concurrency;

int main()
{
  list<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  auto tw = [](int& n) {
    n *= 2;
  };
  
  // 명령적 프로그래밍
  // 선언적 프로그래밍
  parallel_for_each(s.begin(), s.end(), tw);
  parallel_for_each(s.begin(), s.end(), [](int n) {
    cout << n << endl;
  });
}



#if 0
int main()
{
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  TwiceVisitor<int> tv;
  ShowVisitor<int> sv;

  s.accept(&tv);
  s.accept(&sv);
  // s안에 있는 모든 요소를 2배로 하고 싶다.
  // 1. 루프를 수행하면서 모든 요소를 2배로 해서 다시 넣으면 된다.
  // 2. 특정 작업을 자주 하게 된다면 멤버 함수로 추가하는 것이 좋다.
  //   s.twiceAll()
  // 3. 방문자 패턴을 사용하자.
  //  => 모든 컨테이너에 대해서 원하는 작업을 수행할 수 있다.
}
#endif