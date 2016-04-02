// ���� ��ü�� ���� ��� ����� �����ϰ� �ʹ�. RefCount ��� ���� ��ü
// shared_ptr<>
// shared_ptr<Image> p(new Image)
// ���� �������ش�. ������ �������� ������� ��������
// �׷� �� RefCount ��ü ����? ���ɶ���
// RefCount ��ü�� ���������� ��ü�޸𸮰� �پ��ֱ� ������ ������ �� ����.
// �׷��� shared_ptr �� �޸� ������ �� �־�
// shared_ptr<Image> p = make_shared<Image>();
// �̷��� �ϸ� ����Ʈ�����Ϳ� ��ü�� �ϳ��� ���� �ڵ带 ��������

// ����Ʈ ������ - �ڿ��� ������
// - shared_ptr : ���� ��� ��� - ������ ����
// - unique_ptr : ���� ����		- ȥ�� ����
//				  �ش� �����͸��� ��ü�� ������ �� �־�. ������ ������ ������ �����ϴ�.
// unique_ptr<int> p1(new int);
// unique_ptr<int> p2 = p1;				// ������ ����, ���� ����
// unique_ptr<int> p2 = std::move(p1);	// ������ ����, p1 -> 0
// �̷��� ������ �����ϱ� ���ؼ���
// Effective Modern C++ - �λ���Ʈ, ���� ����
//		Effective C++ �� �ߺ��Ǵ� ���� �ƴ϶� Ȯ��Ǳ� ������ Effective C++�� �̸� �о�� �Ѵ�.

// �׷��� shared_ptr�� ���� ����ϸ� ��������
// ��Ƽ�����忡�� ����� �� refCount�� �����ϴ� ���� ����������ϰ� ����Ǿ��ִ�. -> atomic ����
// atomic ������ ���鼭 CPU�� ���ݾ� ��ԵǾ� ��������
// ���� raw pointer�� unique_ptr�� ���� ���� �� ������.
// ����Ʈ ������: ������ �߻����� ��� ������ �˱� ��ƴ�. �޸� �ι� ������簡...
// ����Ʈ �����͸� �� �� ����Ǵ� �ڷ�
// http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
// ������� ����Ʈ �����Ϳ� ���� �н��� �Ǿ�߸� �� ���� �ִ�.

// ����: ��ȯ ����
// p1-->A, p2=->B
// p1->next==B, p2->next==A
// next�� shared_ptr �̸�?

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
