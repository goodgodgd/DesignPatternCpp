#include <iostream>
using namespace std;
// 4_접근변경자3.cpp

#include <list>

// S/W의 재사용은 상속과 포함이 있습니다. => 포함이 좋을 때가 많다.
// stack adapter라고 부릅니다.
#include <stack>
#include <deque>
#if 0
template <typename T, typename C = deque<T> >
class stack
{
  C st;
public:
  void push(const T& a) { st.push_back(a);  }
  void pop()            { st.pop_back();    }
  T&   top()            { return st.back(); }
};
#endif

#include <vector>

// http://d.pr/n/1lgo9
int main()
{
  stack<int> s;
  stack<int, list<int> > s2;
 
  s.push(10);
  s.push(20);

  cout << s.top() << endl;
}
