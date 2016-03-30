// C++ STL���� �ݺ��ڸ� ����ϱ� ���ؼ��� �ݵ�� �����ؾ� �մϴ�.

// �ݺ��� ���� (iterator category)
//	: �ڷᱸ���� ���¿� ���� ���������� �����ϴ� ������ �����ε� ���°� �ٸ���.
//	list<> - ���߿��� ����Ʈ - �ε��� ���� ȿ�� ��������.
//	vector<> - �迭

// 1. �Է� �ݺ���:		=*p, ++ �Է�, �̵�			=> find() ���� ����
// 2. ��� �ݺ���:		*p=, ++
// 3. ������ �ݺ���		�����, ++					=> slist
// 4. ����� �ݺ���		�����, ++, --				=> list
// 5. �������� �ݺ���	�����, ++, --, +, -, []		=> ���ӵ� �޸�, vector

// �����̳ʿ� �˰����� �����ϱ� ���� �ݺ��� ������ �˾ƾ� �Ѵ�.

// C++�� functional frame���� ������� �ִ�. ����� �����ؼ� ������ �ذ��ϴ� ���

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
	// �����̳ʸ� �ٲٱ� ���ؼ��� �Ʒ��� iterator�� �޾ƿ��� ���� �ڵ������ �ؾ��Ѵ�.
//	vector<int> v;
	list<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

//	vector<int>::iterator p = find(v.begin(), v.end(), 20);
	list<int>::iterator p = find(v.begin(), v.end(), 20);
	cout << *p << endl;

	// �׷��� auto �� ����.
	auto p1 = find(v.begin(), v.end(), 20);
	cout << *p1 << endl;
}
#endif

#if 0
int main()
{
	// �⺻ array�� �������� iterator ���� ���� �˰����� ���� �մ� STL array�� ����.
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

	// list�� �� �ȵɱ�? �ݺ��� ������ �ȵȴ�.
//	sort(v.begin(), v.end());
	// �׷��� list������ �����Լ� �����Ѵ�.
	v.sort();
}
