// �����̳ʸ� �����ϴ� ���
// ��� 1. object* ����� �����̳� (�ֻ��� �θ�Ŭ����
//		java, C#: Object
//		Objective C: NSObject
//		MFC: CObject
//		Qt: QObject

#include <iostream>
using namespace std;

class object{
public:
	virtual ~object() {}
};

// ���̺귯�� ���� ��� Ŭ������ object�� �ڽ��̾�� �Ѵ�.
class Dialog : public object {};
class Point : public object {};
class Rect : public object {};

struct node
{
	// C++�� ���۷����� ������ C++������ ���۷����� ���� �Ұ���.
	// ������ ����.
	object* data;
	node* next;
	// ���λ����ڸ� ���� ��� ����
	node(object* a, node* n) : data(a), next(n) {}
};

class slist
{
	node* head;
public:
	slist() : head(0) {}

	// ����� �����ڸ� �� Ȱ���� �ڵ��Դϴ�.
	// ������ ���� ��� ���� ������ ĸ��ȭ
	void push_front(object* a) { head = new node(a, head); }
	object* front() { return head->data; }
};
/*
class Interger : public object
{
	node* head;
public:
	slist() : head(0) {}

	// ����� �����ڸ� �� Ȱ���� �ڵ��Դϴ�.
	// ������ ���� ��� ���� ������ ĸ��ȭ
	void push_front(object* a) { head = new node(a, head); }
	object* front() { return head->data; }
};
*/

// object ��� �����̳��� ����? ����?
// ����:
//	1. Ÿ�� �������� ��������. �Ǽ��� �ٸ� Ÿ���� �־ ������ �ð��� ������ �߻����� �ʴ´�.
//	2. ���� ���� �� �׻� �ش� Ÿ������ ĳ�����ؾ� �Ѵ�.
//	3. ��ü�� �ƴ� ǥ�� Ÿ��(primitive type)�� ������ �� ����.
//		s.push_front(3);  // error
//		wrapper class�� �ʿ��ϴ� - ǥ�� Ÿ���� ���۷��� Ÿ��
//		int - integer
//		double - Double
//		java�� autoboxing, autounboxing�̶�� ������� �ذ�

// ����:
// template�� ����ϰ� �Ǹ�, �ڵ� �޸� ���� ��尡 ����.
// �ϳ��� �������� ��� Ÿ�� �ٷ�� �ִ�.

// ����: �������� Ÿ���� �ְ� ������ �ִ�.
// ����: ������ object* �������� ������ �Ѵ�. -> �ٿ� ĳ�����ؾ� �Ѵ�.

int main()
{
	slist s;
	s.push_front(new Point);
	s.push_front(new Dialog);
	s.push_front(new Rect);		// ���� �ƴϰ� �Ǽ�!!

//	s.push_front(3);		// �Ұ�
//	Point* p = s.front();		// error


	Point* p = dynamic_cast<Point*>(s.front());	// ��������, �׷��� �߸��� ĳ������ ������
//	Point* p =  static_cast<Point*>(s.front());	// static �� ���������� �Ҿ���
}
