// ��ü�� ������ ��������� �����ϴ� ��찡 �����ϴ�.
// ��ü�� �����ϴµ� ȿ������ ���
// 

#include <iostream>
using namespace std;

// ��ü�� ���� �����Ǿ�� �Ѵ�. new�� ����?
class Image
{
	int mCount;
public:
	Image() : mCount(0) {}
	~Image() { cout << "�̹��� �ı�" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// ��������� 0�Ǹ� �ڽ� �ı�
			delete this;
	}
};

int main()
{
	Image* p1 = new Image;	// ��Ģ1. ��ü�� ����� ���� ��� ����
	p1->addRef();

	Image* p2 = p1;			// ��Ģ2. �����͸� �����ϸ� ���� ��� ����
	p2->addRef();

	p1->release();			// ��Ģ3. ��ü ������ ��� �� ���� ��� ����
	//p2->release();		// release ���� ������ �ڿ����� �߻�!!
}
