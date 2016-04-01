#include <iostream>
using namespace std;
// 4_컨테이너
// 컨테이너를 설계하는 기술
// - 단일 연결리스트 기반의 컨테이너

struct node
{
  int data;
  node* next;
  node(int a, node* n) : data(a), next(n) {}
};

class slist
{
  node* head;
public:
  slist() : head(0) {}

  // node의 생성자를 잘 활용한 코드 입니다.
  void push_front(int a) { head = new node(a, head); }
  int front() { return head->data; }
};

int main()
{
  slist s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  cout << s.front() << endl;
}