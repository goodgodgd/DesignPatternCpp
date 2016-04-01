
#include <iostream>
using namespace std;

#include <memory>

// ��ȯ ����
// => ���� ������ ����� ���� ������ ������ �����ϰ� ������ �� �־�� �Ѵ�.
// ���� ����: ref count �� ���ϴ� ��
// ���� ����: ref count �� ������ �ʴ� ��

#if 0
struct node
{
	~node() { cout << "node �ı�" << endl; }
	shared_ptr<node> next;
};

int main()
{
	shared_ptr<node> p1(new node);
	shared_ptr<node> p2(new node);

	// �̰��ϸ� �ı����� �ʴ´�.
	//p1->next = p2;
	//p2->next = p1;
}
#endif

struct node
{
	~node() { cout << "node �ı�" << endl; }
	// ���� ����
	weak_ptr<node> next;
};

// Java������?
// Node p = new Node();		-> ���� ����
// WeakReference<Node> wp = new WeakReference<>(new Node());
// SoftReference -> ���� ����
// Java������ �⺻������ garbage collection�� �߻��ϰų� ���ų� �޸𸮰� ��� �����ϴµ�
// SoftReference: garbage collection�� �߻��ص� �þ�ٰ� out of memory ���� �����Ѵ�. ���� �ʴ´�.
// WeakReference: garbage collection�� �߻��ϸ� �ٷ� �����Ѵ�.

int main()
{
	shared_ptr<node> p1(new node);
	shared_ptr<node> p2(new node);

	// ���� �ı��ȴ�.
	p1->next = p2;
	p2->next = p1;

	shared_ptr<node> p = p1->next.lock();
	// ������� �������� ���� �Ѵ�.
}
