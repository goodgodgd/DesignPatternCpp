// 4_접근변경자2.cpp
#include <iostream>
using namespace std;

// list가 이미 있습니다.
#include <list>

// 그런데 클라이언트가 stack을 요구합니다.
// 1. stack을 다시 만들어 주자.
// 2. list를 한쪽으로 사용하면 stack이다. list를 재사용하자.

// Adapter Pattern: 기존 클래스의 인터페이스(함수 이름)을 변경해서
//                  사용자가 요구하는 새로운 클래스처럼 보이게 하는 패턴.

// 라이브러리는 쉽게 사용할 수 있도록 만들어야 하고,
// 잘못 사용하기 어렵게 만들어야 한다.

// private 상속: 부모 클래스로부터 구현은 물려 받지만, (자식이 내부적으로 사용하지만)
//              인터페이스는 물려 받지 않겠다.(부모 함수를 외부로 노출하지 않겠다.)
// http://d.pr/n/OaYa
template <typename T>
class stack : private list<T>
{
public:
  // using list<T>::push_back;

  void push(const T& a) { push_back(a); }  // 부모의 함수 재사용
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