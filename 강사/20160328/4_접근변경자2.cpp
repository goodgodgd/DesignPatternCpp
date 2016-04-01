// 4_���ٺ�����2.cpp
#include <iostream>
using namespace std;

// list�� �̹� �ֽ��ϴ�.
#include <list>

// �׷��� Ŭ���̾�Ʈ�� stack�� �䱸�մϴ�.
// 1. stack�� �ٽ� ����� ����.
// 2. list�� �������� ����ϸ� stack�̴�. list�� ��������.

// Adapter Pattern: ���� Ŭ������ �������̽�(�Լ� �̸�)�� �����ؼ�
//                  ����ڰ� �䱸�ϴ� ���ο� Ŭ����ó�� ���̰� �ϴ� ����.

// ���̺귯���� ���� ����� �� �ֵ��� ������ �ϰ�,
// �߸� ����ϱ� ��ư� ������ �Ѵ�.

// private ���: �θ� Ŭ�����κ��� ������ ���� ������, (�ڽ��� ���������� ���������)
//              �������̽��� ���� ���� �ʰڴ�.(�θ� �Լ��� �ܺη� �������� �ʰڴ�.)
// http://d.pr/n/OaYa
template <typename T>
class stack : private list<T>
{
public:
  // using list<T>::push_back;

  void push(const T& a) { push_back(a); }  // �θ��� �Լ� ����
  void pop()            { pop_back(); }
  T&   top()            { return back(); }
};

int main()
{
  stack<int> s;
  
  s.push(10);
  s.push(20);
  s.push_back(300);

  cout << s.top() << endl;
}