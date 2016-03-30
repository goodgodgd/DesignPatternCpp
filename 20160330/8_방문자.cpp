// GoF�� ������ ���Ͽ��� �����̳ʿ� �����ϴ� ������ �ΰ��� �ֽ��ϴ�.
// 1. �ݺ���: �����̳��� ���� ������ ������� ��Ҹ� �����Ѵ�.
// 2. �湮��: �����̳��� ���� ������ ������� ��ҿ� ������ �����Ѵ�.

// �����̳� �ȿ� �ִ� ��� ��Ҹ� 2��� �ϰ� �ʹ�.
// 1. ������ �����ϸ鼭 ��� ��Ҹ� 2��� �ؼ� �ٽ� ������ �ȴ�.
// 2. Ư�� �۾��� �����ϰ� �ȴٸ� ��� �Լ��� �߰��ϴ� ���� ����.
//		�׷��� ����ڰ� � �۾��� �����ϴ��� ���̺귯�� �����ڴ� �𸥴�.
// 3. �湮�� ������ �������.
//	=> ��� �����̳ʿ� ���ؼ� ���ϴ� �۾��� ������ �� �ִ�.
// C++ ǥ�ؿ��� �湮�ڰ� ���� java ��Ÿ�� �����غ���!

#include <ppl.h>	// ����ũ�� ����Ʈ���� �����ϴ� �����Լ�
// for_each ��� parallel_for_each�� ���� �ȴ�.

// ����� ���α׷���: ���� ������ ���� ����
// ������ ���α׷���: query�� ����ϰ� ����� �ٸ� �̸����� �����ϰ� ����????


#include <iostream>
using namespace std;

template <typename T>
struct IVisitor
{
	virtual void visit(T& a) = 0;
	virtual ~IVisitor() {}
};

// ��� �湮 ���(�����̳�)�� �������̽�
template < typename T >
struct IAcceptor
{
	virtual void accept(IVisitor<T>* visitor) = 0;
	virtual ~IAcceptor() {}
}

// �����̳ʸ� �ٲ��� �ʰ� �湮�ڸ� ���� ����� �߰��� �� �ִ�.
// ��� ��Ҹ� �ι�� �ϴ� �湮��
template < typename T >
struct TwiceVisitor : public IVisitor < T >
{
public:
	virtual void visit(T& a) { a *= 2; }
};

// ��� ��Ҹ� �����ִ� �湮��
template < typename T >
struct ShowVisitor : public IVisitor < T >
{
public:
	virtual void visit(T& a) { cout << a << endl; }
};


template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};


template <typename T>
class slist : public IAcceptor<T>
{
	node<T>* head;
public:
	// �Ʒ� �Լ��� ��Ȯ�ϰ� �����ϸ� �˴ϴ�.
	virtual void accept(IVisitor<T>* visitor)
	{
		node<T>* current = head;
		while (current)
		{
			visitor->visit(current->data);
			current = current->next;
		}
	}

	slist() : head(0) {}
	void push_front(const T& a) { head = new node<T>(a, head); }
	T& front() { return head->data; }
};

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	TwiceVisitor<int> tv;
	ShowVisitor<int> sv;

	s.accept(&tv);
	s.accept(&sv);

	cout << s.front() << endl;
}


