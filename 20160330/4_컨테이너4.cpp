// �����̳ʸ� �����ϴ� ���
// ��� 3. Thin Template

// void* �� ����ϸ� �Ϲ� ������ �Ӹ� �ƴ϶� ��ü ������ ��� ���� �� �ִ�.
// �ٵ� void�� �׻� ĳ������ ����� �Ѵ� -> ĳ���� �ڵ�ȭ ���ִ� Ŭ���� ���������.

#include <iostream>
using namespace std;

struct node
{
	(void*) data;
	node* next;
	node(void* a, node* n) : data(a), next(n) {}
};

// ��� ������ �̰����� void* ������� ����
class slistImpl
{
	node* head;
public:
	slistImpl() : head(0) {}

	void push_front(void* a) { head = new node(a, head); }
	void* front() { return head->data; }
};

// slistImpl�� ���� ����ϸ� ĳ���� ������ �����ϴ�.
// ����ڰ� ���ϰ� ����� �� �ֵ��� ������ ���� �޴� �ڽ� Ŭ������ ���ø����� ��������.
// ������ ��� �ް� �������̽��� �����Ѵ� -> private ���
template <typename T>
class slist : private slistImpl
{
public:
	// �̰��� inlineȭ �ϸ� �ڵ� �޸� ���� ����
	// �� �Լ��� ��� �������� ����.
	inline void push_front(const T& a)
	{
		// const T& -> const* T
		// node(void* a, node* n) ������ const�� �ƴϹǷ� const�� �����ֱ� ���� const_cast ����.
		slistImpl::push_front(const_cast<T*>(&a));
	}
	inline T& front()
	{
		// void* -> T* -> T&
		return *static_cast<T*>(slistImpl::front());
	}
};


// const cast�� node�� �Űܵ� �ǳ�?
#if 0
struct node
{
	(void*) data;
	node* next;
	// const cast�� �������� �Űܵ� �ǳ�?
	node(const void* a, node* n) : data(const_cast<void*>(a)), next(n) {}
};

// ��� ������ �̰����� void* ������� ����
class slistImpl
{
	node* head;
public:
	slistImpl() : head(0) {}

	void push_front(const void* a) { head = new node(a, head); }
	void* front() { return head->data; }
};

template <typename T>
class slist : private slistImpl
{
public:
	inline void push_front(const T& a)
	{
		// const T& -> const* T
		slistImpl::push_front(&a);
	}
	inline T& front()
	{
		// void* -> T* -> T&
		return *static_cast<T*>(slistImpl::front());
	}
};
#endif

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

	cout << s.front() << endl;
}
