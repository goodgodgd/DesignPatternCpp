// ��ü�� ������ ��������� �����ϴ� ��찡 �����ϴ�.
// ��ü�� �����ϴµ� ȿ������ ���

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


// Image*�� �ٷ� ����ϸ� ��������� �Ź� �����ؾ� �Ѵ�.
// �����ϹǷ� ��������� �ڵ����� �������ִ� Ŭ������ ������.
class ImageProxy
{
	Image* ptr;
public:
	ImageProxy(Image* p) : ptr(p) { ptr->addRef(); }	// ��Ģ 1.
	ImageProxy(const ImageProxy& p) : ptr(p.ptr)
	{	ptr->addRef();	}								// ��Ģ 2.
	~ImageProxy() { ptr->release(); }					// ��Ģ 3.
};

int main()
{
	ImageProxy p1 = new Image;
	ImageProxy p2 = p1;
}
