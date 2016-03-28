// http://d.pr/n/0aYa

#include <iostream>
using namespace std;

// list�� �̹� �ֽ��ϴ�.
#include <list>

// �׷��� Ŭ���̾�Ʈ�� stack�� �䱸�մϴ�.
// 1. stack�� �ٽ� ���������. - �����
// 2. list�� �������� ����ϸ� stack�̴�. list�� ��������. - Better, �̹� �����Ǿ��� ȿ����

// Adapter Pattern: ���� Ŭ������ �������̽�(�Լ� �̸�)�� �����ؼ�
//					����ڰ� �䱸�ϴ� ���ο� Ŭ����ó�� ���̰� �ϴ� ����

// ���̺귯���� ���� ����� �� �ֵ��� ������ �ϰ�,
// �߸� ����ϱ� ��ư� ������ �Ѵ�.
// �Ʒ� stack�� ������ stack ������ push, pop, top �Ӹ� �ƴ϶�
// list�� ��� ��ɵ� ����.
// private ���: �θ� Ŭ�����κ��� ������ ���� ������, (�ڽ��� ���������� ���������)
//				�������̽��� ���� ���� �ʰڴ�. (�θ� �Լ��� �ܺη� �������� �ʰڴ�.)

// list�� ����� �̿��ؼ� stack ����
template <typename T>
//class stack : public list < T >
class stack : private list < T >	
{
public:
	// private���� �޾Ƶ� using�� ���� ���� ����
	using list<T>::push_back;

	void push(const T& a)	{ push_back(a); }	// �θ��� �Լ� ����
	void pop()				{ pop_back(); }
	T& top()				{ return back(); }
};

int main()
{
	stack<int> s;
	s.push(10);
	s.push(20);
	// �θ𿡰Լ� �ް� ���� ���� �͵� �ް� ��.
//	s.push_back(300);
	// top = 20;
	cout << s.top() << endl;
}
