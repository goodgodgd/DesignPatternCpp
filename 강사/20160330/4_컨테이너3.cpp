// �����̳�3
#include <iostream>
using namespace std;


// 2. template ����� �����̳�
//  - Java, C#, ObjC: Generic
// ���ڸ� ����             ǥ�� Ÿ��                 ��ü Ÿ��
// call by value           void foo(int n)          void foo(const AAA& n)
// call by reference       void foo(int& n)         void foo(AAA& n)

//                          T - ǥ�� Ÿ�� �Ǵ� ��ü Ÿ�Ե� �� �� �ִ�.
//                          void foo(const T&)
template <typename T>
struct node
{
  T data;
  node* next;
  node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist
{
  node<T>* head;
public:
  slist() : head(0) {}

  void push_front(const T& a) { head = new node<T>(a, head); }
  T& front() { return head->data; }
};

// ����: Ÿ�� �������� �پ�� ǥ�� Ÿ�Ի� �ƴ϶� ��ü�� ���� �����ϴ�.
//       ���� �� ĳ������ �ʿ����.

// ����: template �̹Ƿ� ���� ���� Ÿ�Կ� ����ϸ� list�� ���� �ڵ尡
//       ��������. �ڵ� �޸� ������尡 �ִ�.


int main()
{
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  cout << s.front() << endl;
}