// ��ü�� ������ ��������� �����ϴ� ��찡 �����ϴ�.
// ��ü�� �����ϴµ� ȿ������ ���

// ��ü�� ���� ī��Ʈ ����� �θ�� �ű��, �پ��� ��ü�� ������ �ִ� ���ø� ������ ��ü�� ������.

#include <iostream>
using namespace std;

// ��ü�� ���� �����Ǿ�� �Ѵ�. new�� ����?
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

// �ٵ� ��ӹ��� ��ü�� 
class Image : public RefCountedObject
{
public:
	void draw() { cout << "draw" << endl; }
};


// RefCountedObject*�� �ٷ� ����ϸ� ��������� �Ź� �����ؾ� �Ѵ�.
// �����ϹǷ� ��������� �ڵ����� �������ִ� Ŭ������ ������.
template <typename T>
class Ptr
{
	T* ptr;
public:
	Ptr(T* p) : ptr(p) { ptr->addRef(); }	// ��Ģ 1.
	Ptr(const Ptr& p) : ptr(p.ptr)
	{
		ptr->addRef();
	}								// ��Ģ 2.
	~Ptr() { ptr->release(); }					// ��Ģ 3.

	// ��¥ ������ó�� ������ �Ѵ�. ->, * �����ڸ� �������ؾ� �Ѵ�.
	// => ����Ʈ ������ �⺻
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
