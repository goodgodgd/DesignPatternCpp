// �����̳ʸ� �����ϴ� ���
// - ���� ���� ����Ʈ ����� �����̳�

// �پ��� Ÿ���� ��� ���ؼ��� template�� ������ �ְ� object pointer�� �� ���� �ִ�.(���� �θ� ���)

#include <iostream>
using namespace std;

struct node
{
	int data;
	node* next;
	// ���λ����ڸ� ���� ��� ����
	node(int a, node* n) : data(a), next(n) {}
};

class slist
{
	node* head;
public:
	slist() : head(0) {}

	// ����� �����ڸ� �� Ȱ���� �ڵ��Դϴ�.
	// ������ ���� ��� ���� ������ ĸ��ȭ
	void push_front(int a) { head = new node(a, head); }
	int front() { return head->data; }
};

int main()
{
	slist s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
