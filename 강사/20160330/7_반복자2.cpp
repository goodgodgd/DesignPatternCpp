// 7_반복자2
// 컨테이너3
#include <iostream>
using namespace std;

template <typename T>
struct node
{
  T data;
  node* next;
  node(const T& a, node* n) : data(a), next(n) {}
};

// 모든 반복자의 인터페이스를 먼저 설계하자.      Java           C#
// 1. 반복자 인터페이스.                       - Iterator      IEnumerator
// 2. 반복의 대상(컬렉션) 인터페이스           - Iterable      IEnumerable

template <typename T> struct IEnumerator
{
  virtual bool moveNext() = 0;        // ++
  virtual T&   getObject() = 0;       // *

  virtual ~IEnumerator() {}
};

template <typename T>
class slist_enumerator : public IEnumerator<T>
{
  node<T>* current;
public:
  slist_enumerator(node<T>* p = 0) : current(p) {}

  virtual bool moveNext()
  {
    current = current->next;
    return current;
  }

  virtual T& getObject()  { return current->data; }
}; 

// 컨테이너에서 반복자 꺼내기
// 1. STL:  begin()/end() => 암시적 약속 (generic 다형성)
// 2. C#,JAVA: 인터페이스 기반 함수 약속
//    Tizen

// 모든 컨테이너는 아래 인터페이스를 구현해야 한다.
template <typename T> struct IEnumerable
{
  virtual IEnumerator<T>* getEnumeratorN() = 0;
  virtual ~IEnumerable() {}
};

template <typename T>
class slist : public IEnumerable<T>
{
  node<T>* head;
public:
  virtual IEnumerator<T>* getEnumeratorN()
  { return new slist_enumerator<T>(head);  }
  // 일반적으로 함수 내에서 new를 해서 리턴해야 한다면, 스마트 포인터를
  // 사용하는 경우가 많다.
  // Tizen: UniquePtr<>

  // free -> strdup(s);
  // char* p = strdup(s);
  
  // char* s = "hello";
  // char* p = malloc(strlen(s) + 1);
  // strcpy(p, s);

  slist() : head(0) {}

  void push_front(const T& a) { head = new node<T>(a, head); }
  T& front() { return head->data; }
};

int main()
{
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  IEnumerator<int>* p = s.getEnumeratorN();
  // 반드시 delete를 수행해야 합니다.
  delete p;

  do {
    cout << p->getObject() << endl;
  } while (p->moveNext());

}