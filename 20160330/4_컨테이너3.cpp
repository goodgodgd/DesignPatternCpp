// �����̳ʸ� �����ϴ� ���
// ��� 2. template ����� �����̳�
//		- java, C#, ObjC: Generic

#include <iostream>
using namespace std;

// ���ڸ� ����			ǥ�� Ÿ��				��ü Ÿ��
// call by value		void foo(int n)			void foo(AAA n)	- ���� �߻�, ���� ����
// call by reference	void foo(int& n)		void foo(AAA& n)

// T - ǥ�� Ÿ�� �Ǵ� ��ü Ÿ�Ե� �� �� �ִ�.
// ��� ���̺귯������ ��ü�� ũ�Ⱑ �۴ٰ� ��Ȯ���� ���� ���� ��ü�� ������ �� const T& ���� ������.

// template �����̳�
// ����: Ÿ�� �������� �پ�� ǥ�� Ÿ�� �Ӹ� �ƴ϶� ��ü�� ���� �����ϴ�.
//		���� �� ĳ������ �ʿ����.
// ����: template �̹Ƿ� �������� Ÿ�Կ� ����ϸ� list�� ���� �ڵ尡 ��������. �ڵ� �޸� ������尡 �����.
//		����ũž ȯ���� �ڵ� �޸𸮰� ���� ��������� �Ӻ���� ȯ�濡���� ������ ����

// object�� template�� ����� �־� -> ����� ����??

template <typename T>
struct node
{
	T data;
	node* next;
	// ���� �δ� ���ְ� �� ���� ���� ���ֱ� ���� const reference
	node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist
{
	node<T>* head;
public:
	slist() : head(0) {}

	// ����� �����ڸ� �� Ȱ���� �ڵ��Դϴ�.
	// ������ ���� ��� ���� ������ ĸ��ȭ
	void push_front(const T& a) { head = new node<T>(a, head); }

	// T pop_front();	// list���� ���� ������ ���� �� ����
	// T& front();		// ���� ���� �ʰ� �����ϱ� ������ ���۷����� �ش�.
	// ���� ������
	// STL: ���º��� ����, ���� �߻��ϸ� ���� ���·� �������ش�.
	T& front() { return head->data; }
};

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
