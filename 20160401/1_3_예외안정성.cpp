// 1. �����ڿ��� ���и� �˸��� ����� ���� �ۿ� ����.
// 2. �����ڿ��� ���ܰ� �߻��ϸ� �Ҹ��ڰ� ȣ����� �ʴ´�.

// ����Ʈ ������ ���
// ���� ������ (Exception safety)
// 1. ���� ����: ���ܰ� ����.
// 2. ���� ����: ���ܰ� �߻��ص� ���� ���(catch), ��ü ���´� ���� �߻������� �����ȴ�.
//				=> STL ������ ��� �̰� ���
// 3. �⺻ ����: ���ܰ� �߻��ص� �ڿ� ������ ����. �� ��ü ���´� �� �� ���� ������ ����� �Ұ����ϴ�.

// ��� ���� - ���� ������
// -Exceptional C++
// -More Exceptional C++
// -Exceptional C++ Style

#include <iostream>
using namespace std;

#include <memory>		// unique_ptr


// uniqe ptr �ƴϸ�? - �Ҹ��� ȣ�� �ȵ�
// p1 �����ϰ� ���ܹ߻��ϸ�??

class Image
{
public:
	Image() { cout << "�̹��� ����" << endl; }
	~Image() { cout << "�̹��� �ı�" << endl; }
};

#if 0
class Test
{
	unique_ptr<Image> p1;
	unique_ptr<Image> p2;
public:

	// ��� ���� Ÿ���� ��ü Ÿ���̶��, �����ڿ��� ���ܰ� �߻��Ͽ��� ���
	// ��� ������ �Ҹ����� ȣ���� ǥ�ؿ����� �����ϰ� �ִ�.
	Test() : p1(new Image), p2(new Image)
	{
		throw std::bad_alloc();	// ���� ���� �߻�

	}

	// �����ڿ��� ���ܰ� �ؼ� ~Test�� ȣ������� ������
	// Image�� ��ü Ÿ���̱� ������ Image�� �Ҹ��ڴ� ȣ��ȴ�.
	~Test()
	{
		cout << "�Ҹ��� ȣ��" << endl;
	}
};
#endif

class Test
{
	Image* p1;
	Image* p2;
public:

	// ��� ���� Ÿ���� ��ü Ÿ���̶��, �����ڿ��� ���ܰ� �߻��Ͽ��� ���
	// ��� ������ �Ҹ����� ȣ���� ǥ�ؿ����� �����ϰ� �ִ�.
	Test() : p1(new Image), p2(new Image)
	{
		throw std::bad_alloc();	// ���� ���� �߻�

	}

	// �����ڿ��� ���ܰ� �ؼ� ~Test�� ȣ������� ������
	// Image�� ��ü Ÿ���̱� ������ Image�� �Ҹ��ڴ� ȣ��ȴ�.
	~Test()
	{
		cout << "�Ҹ��� ȣ��" << endl;
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