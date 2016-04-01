#include <iostream>
using namespace std;

#include <memory>

// 순환 참조
// => 강한 참조의 개념과 약한 참조의 개념을 이해하고 구현할 수 있어야
//    한다. => 소유권

// Node p = new Node();  ->  강한 참조
// WeakReference<Node> wp = new WeakReference<>(new Node()); 
// -> 약한 참조

struct node
{
  ~node() { cout << "node 파괴" << endl; }
  weak_ptr<node> next;
};

int main()
{
  shared_ptr<node> p1(new node);
  shared_ptr<node> p2(new node);

  p1->next = p2;
  p2->next = p1;

  shared_ptr<node> p = p1->next.lock(); 
  // 사용전에 소유권을 얻어야 한다.


}