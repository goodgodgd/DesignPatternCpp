
#include <iostream>
using namespace std;

template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};

// slist�� �ݺ��ڸ� �����غ��ô�.
// - �ݺ���: �����̳��� ������ ǥ���ϴ� Ÿ�� (�̸鼭 ����Ʈ ������)
// iterator�� vector�� list�� �迭ó�� ���� ���ִ� ���� ������ ���ش�.

template <typename T>
class slist_iterator
{
	node<T>* current;
public:
	// ��Ģ2. (C++ document)
	// ��� �����̳� �����ڴ� �ڽ��� �ݺ��� �̸��� �̸� ��ӵ� ���·� �ܺο� �˷��� �Ѵ�.
	slist_iterator(node<T>* p = 0) : current(p) {}

	// ==, != �� �����Ѵ�.
	inline bool operator==(const slist_iterator& t)	{ return t.current == current; }
	inline bool operator!=(const slist_iterator& t)	{ return t.current != current; }

	// ���� ��� ����
	inline T& operator*() { return current->data; }

	// �̵��ϴ� ����
	inline slist_iterator& operator++()
	{
		current = current->next;
		return *this;
	}
};



// ��Ģ1. (C++ document)
// ��� �����̳��� �����ڴ� �ڽ��� ó���� �� ������ ����Ű�� �ݺ��ڸ� ���� �� �ִ� ������ �����ؾ� �Ѵ�.
// begin() / end()

template <typename T>
class slist
{
	node<T>* head;
public:
	typedef slist_iterator<T> iterator;

	slist() : head(0) {}	// -> list�� �� �������� '0'�̵ȴ�. -> end()���� 0 ����

	void push_front(const T& a) { head = new node<T>(a, head); }
	T& front() { return head->data; }

	// �ݺ��ڸ� ������ �Լ�
	slist_iterator<T> begin() { return slist_iterator<T>(head); }
	slist_iterator<T> end() { return slist_iterator<T>(0); }	// �� 0? ������ ����

};

template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (first != last && *first != value)
		++first;

	//	return first == last ? 0 : first;
	return first;	// first == last �̸� �����ٴ� ���
}

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

//	slist_iterator<int> p = xfind(s.begin(), s.end(), 20);
	slist<int>::iterator p = xfind(s.begin(), s.end(), 20);
	if (p != s.end())
		cout << *p << endl;
}

