// 4_컨테이너4
#include <iostream>
using namespace std;

struct node
{
  void* data;
  node* next;
  node(void* a, node* n) : data(a), next(n) {}
};

class slistImpl
{
  node* head;
public:
  slistImpl() : head(0) {}

  void push_front(void* a) { head = new node(a, head); }
  void* front() { return head->data; }
};

// 방법 3. Thin Template

// slistImpl을 직접 사용하면 캐스팅 때문에 불편하다.
// 사용자가 편리하게 사용할 수 있도록 구현을 물려 받는 자식 클래스를 
// 템플릿으로 제공하자.
template <typename T>
class slist : private slistImpl
{
public:
  inline void push_front(const T& a)
  {
    //  const T& -> const T*
    slistImpl::push_front(const_cast<T*>(&a));
  }

  inline T& front()
  {
    // void* -> T* -> T&
    return *static_cast<T*>(slistImpl::front());
  }
};

int main()
{
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  cout << s.front() << endl;
}