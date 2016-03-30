// �ڹٽ�Ÿ���� �������̽� �ݺ��ڸ� �����غ���.

#include <iostream>
using namespace std;

// ��� �ݺ����� �������̽��� ���� ��������.	Java		C#
// �ռ� �ڵ��� ��Ģ�� �������̽�ȭ ����
// 1. �ݺ��� �������̽�						- Iterator	- IEnumerator
// 2. �ݺ��� ���(�÷���) �������̽�			- Iterable	- IEnumerable


// �� �ٸ���� ++ ����?

template <typename T>
struct node
{
	T data;
	node* next;
	node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T> 
struct IEnumerator
{
	// java���� operator �ƴ� �޼ҵ�� ����
	virtual bool moveNext() = 0;	// ++
	virtual T& getObject() = 0;		// * (���۷���)
	virtual ~IEnumerator() {}
};


template <typename T>
class slist_enumerator : public IEnumerator<T>
{
	node<T>* current;
public:
	slist_enumerator(node<T>* p = 0) : current(p) {}

	virtual bool moveNext()
	{
		current = current->next;
		return current;
	}

	virtual T& getObject() { return current->data; }
};


// �����̳ʿ��� �ݺ��� ������
// 1. STL: begin()/end() => �Ͻ��� ��� (generic ������) ���� ���ε� ���� �Ⱦ
// 2. C# java: �������̽� ��� �Լ� ���

// ��� �����̳ʴ� �Ʒ� �������̽��� �����ؾ� �Ѵ�.


template <typename T>
struct IEnumerable
{
	virtual IEnumerator<T>* getEnumeratorN() = 0;
	virtual ~IEnumerable() {}
};

template <typename T>
class slist : IEnumerable<T>
{
	node<T>* head;
public:
	virtual IEnumerator<T>* getEnumeratorN()
	{
		return new slist_enumerator<T>(head);
	}
	// �Ϲ������� �Լ� ������ new�� �ؼ� �����ؾ� �Ѵٸ�, ����Ʈ �����͸� ����ϴ� ��찡 ����.
	// Tizen: UniquePtr<>

	// free -> strdup
	// char s[] = "hell";
	// char* p = malloc(strlen(s) + 1);
	// strcpy(p, s);

	// char* p = strdup(s);	// ���� �ڵ��ε� malloc�� �Ⱥ��̴ϱ� free�� ���ؼ� ������ ���� �����.

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

	IEnumerator<int>* p = s.getEnumeratorN();
	do {
		cout << p->getObject() << endl;
	} while (p->moveNext());

	// �ݵ�� delete�� �����ؾ� �մϴ�.
	delete p;
}
