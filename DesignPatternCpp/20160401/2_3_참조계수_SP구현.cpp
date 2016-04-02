// ��ü�� ������ ��������� �����ϴ� ��찡 �����ϴ�.
// ��ü�� �����ϴµ� ȿ������ ���

// ��ü�� ���� ī��Ʈ ����� �θ�� �ű��, �پ��� ��ü�� ������ �ִ� ���ø� ������ ��ü�� ������.

#include <iostream>
using namespace std;

// ���� ��� ī��Ʈ ��ɴ��� �θ� Ŭ����
class RefCountedObject
{
	int mCount;
public:
	RefCountedObject() : mCount(0) { cout << "��ü ����" << endl; }
	~RefCountedObject() { cout << "��ü �ı�" << endl; }

	void addRef() { ++mCount; }
	void release()
	{
		if (--mCount == 0)	// ��������� 0�Ǹ� �ڽ� �ı�
			delete this;
	}

};

// ������ ��ɸ� ������ �ڽ� Ŭ����
class Image : public RefCountedObject
{
public:
	void draw() { cout << "draw" << endl; }
};


// ���� ��� ����� �ִ� �پ��� ��ü�� ���� ���� ��� ���� ����� ĸ��ȭ�� Ŭ����
// ����, ����, �Ҹ�� ���� ��� ����
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p)				{ ptr->addRef(); }	// ��Ģ 1. ��ü�� ����� ���� ��� ����
	Ptr(const Ptr& p) : ptr(p.ptr)	{ ptr->addRef(); }	// ��Ģ 2. �����͸� �����ϸ� ���� ��� ����
	~Ptr()							{ ptr->release(); }	// ��Ģ 3. ��ü ������ ��� �� ���� ��� ����
	
	// ��¥ ������ó�� ������ �Ѵ�: ->, * �����ڸ� �������ؾ� �Ѵ�.
	// - ����Ʈ ������ �⺻
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
};

int main()
{
	Ptr<Image> p1 = new Image;	// ��ü ����
	Ptr<Image> p2 = p1;
	p1->draw();					// draw
								// ��ü �ı�
}
