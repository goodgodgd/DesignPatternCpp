// 7_반복자4
// C++ STL에서 반복자를 사용하기 위해서는 반드시 이해해야 합니다.

// 반복자 종류(interator category)
//  : 자료구조의 형태에 따라서 내부적으로 지원하는 
//    연산자 오버로딩의 형태가
//    다르다.
// 1. 입력 반복자:       =*p, ++
// 2. 출력 반복자:       *p=, ++
// 3. 전진형 반복자:  입출력, ++                => slist
// 4. 양방향 반복자:  입출력, ++, --            => list
// 5. 임의접근 반복자: 입출력, ++, --, +, -, [] => 연속된 메모리


// list<>   - 이중 연결 리스트
// vector<> - 배열                     []

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <array>
using namespace std;

int main()
{
  list<int> s;

  s.sort();
  // sort(s.begin(), s.end());
}


#if 0
// List<Integer> s = new LinkedList<>();
// ....
int main()
{
  array<int, 5> v;
  // v.push_back(10);
  // v.push_back(20);
  // v.push_back(30);

  auto p = find(v.begin(), v.end(), 20);
  cout << *p << endl;
}
#endif


#if 0
int main()
{

}
#endif
