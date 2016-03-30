// C++ STL에서 반복자를 사용하기 위해서는 반드시 이해해야 합니다.

// 반복자 종류 (iterator category)
//	: 자료구조에 형태에 따라서 내부적으로 지원하는 연산자 오버로딩 형태가 다르다.
//	list<> - 이중연결 리스트 - 인덱스 접근 효율 떨어진다.
//	vector<> - 배열

// 1. 입력 반복자:		=*p, ++ 입력, 이동			=> find() 적용 가능
// 2. 출력 반복자:		*p=, ++
// 3. 전진형 반복자		입출력, ++					=> slist
// 4. 양방향 반복자		입출력, ++, --				=> list
// 5. 임의접근 반복자	입출력, ++, --, +, -, []		=> 연속된 메모리, vector

// 컨테이너에 알고리즘을 적용하기 전에 반복자 종류를 알아야 한다.

// C++는 functional frame으로 만들어져 있다. 기능을 조합해서 문제를 해결하는 방식

#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <iostream>
using namespace std;

#if 0
int main()
{
	int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	sort(x, x + 10);

	for (int i = 0; i < 10; i++)
		cout << x[i] << endl;
}
#endif

#if 0
int main()
{
	// 컨테이너를 바꾸기 위해서는 아래서 iterator를 받아오는 곳도 코드수정을 해야한다.
//	vector<int> v;
	list<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

//	vector<int>::iterator p = find(v.begin(), v.end(), 20);
	list<int>::iterator p = find(v.begin(), v.end(), 20);
	cout << *p << endl;

	// 그래서 auto 를 쓴다.
	auto p1 = find(v.begin(), v.end(), 20);
	cout << *p1 << endl;
}
#endif

#if 0
int main()
{
	// 기본 array를 쓰지말고 iterator 등의 공통 알고리즘을 쓸수 잇는 STL array를 쓰자.
	array<int, 5> v;
	auto p = find(v.begin(), v.end(), 20);
	cout << *p << endl;
}
#endif

int main()
{
	//	vector<int> v;
	list<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	// list는 왜 안될까? 반복자 종류가 안된다.
//	sort(v.begin(), v.end());
	// 그래서 list에서는 내부함수 제공한다.
	v.sort();
}
