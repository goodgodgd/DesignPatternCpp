// 1. �����ڿ��� ���и� �˸��� ����� ���� �ۿ� ����.
// 2. �����ڿ��� ���ܰ� �߻��ϸ� �Ҹ��ڰ� ȣ����� �ʴ´�.

#include <iostream>
using namespace std;

class Test
{
	int* p1;
	int* p2;
public:
	Test()
	{
		// new�� ���ܸ� ���� �� �ִ�.
		p1 = new int;
		throw std::bad_alloc();	// ���� ���� �߻�
		p2 = new int;	// �� ���� �޸𸮰� �����߽��ϴ�. � ������ �������?
						// new�� �޸𸮰� �����ϸ� bad_alloc �̶�� ���ܰ� �߻��մϴ�.
						// �׷��� p1�� �Ҵ��� �ƴµ� �Ҹ��ڰ� ȣ���� �ȵȴ�. -> p1�� ���� �޸� ����
						// �ذ���? ���� �ڵ忡...
	}

	~Test()
	{
		cout << "�Ҹ��� ȣ��" << endl;
		delete p1;
		delete p2;
	}
};

int main()
{
	try
	{
		Test t;
	}
	catch (...)
	{

	}
}