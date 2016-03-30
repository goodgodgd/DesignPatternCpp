// C++�� ���� �����ӿ�ũ���� ��ü������ RTTI�� ������ ���� �����ؼ� ����ϰ� �ֽ��ϴ�.
// MFC, Qt, Android ...
// Reflection => ���ڿ� => ��ü����

// ��ü�� Ŭ������ ������ ������ �����ؾ� �Ѵٸ� -> ���� ���� static int a;
// RTTI�� �M���� type_info�Դϴ�. => ���� ��� ����

#include <iostream>
#include <string>
using namespace std;

struct CRuntimeClass
{
	string name;
	// �ϱ⿡ ���� �߰����� ������ ���� �� �ִ�.
};

// �������� ��� Ŭ������ �Ʒ� ��Ģ�� ���Ѿ� �մϴ�.
// 1. ��� Ŭ�������� ���� ��� ������ CRuntimeClass �� �־�� �Ѵ�.
// 2. ���� �̸��� "classŬ�����̸�" ���� �Ѵ�.
// 3. ���� ������ �����ϴ� �����Լ� GetRuntimeClass()�� �־�� �Ѵ�.

// ��ũ�� ����
// 1. ## : ��ū �ձ�
// 2. # : ��ū ���ڿ�ȭ

// �������� ��ũ�� �Լ��� �����ؾ� �Ѵ�.
// => ��ũ�� ġȯ�� ���� ����ϱ� ���ԟ�.
// => Linux Kernel ���� MODULE_LICENSE ��ũ�θ� �м��ϸ� �˴ϴ�.


// ���� ��ũ�η� �����غ���!!
// �� ��Ģ�� ��ũ��ȭ �մϴ�.

// ## : ��ũ�ο��� ��ū�� �̾��ش�.!!
/*
#define DECLARE_DYNAMIC(classname)					\
	public:											\
	static CRuntimeClass class##className;			\
	virtual CRuntimeClass* GetRuntimeClass();

// # : ��ū�� ���ڿ��� �ٲ��ش�.
#define IMPLEMENT_DYNAMIC(classname)							\
	CRuntimeClass classname::class##classname = { #classname };	\
	CRuntimeClass* classname::GetRuntimeClass()					\
	{ return &class##classname; }

// Ŭ���� �̸����� static ������ RuntimeClass ��� ��ũ��
#define RUNTIME_CLASS(classname)		&(class::class##classname)
*/

#define DECLARE_DYNAMIC(classname)                                \
  public:                                                         \
  static CRuntimeClass class##classname;                          \
  virtual CRuntimeClass* GetRuntimeClass();

#define IMPLEMENT_DYNAMIC(classname)                              \
  CRuntimeClass classname::class##classname = { #classname };     \
  CRuntimeClass* classname::GetRuntimeClass()                     \
  { return &class##classname; }

// Ŭ���� �̸����� static ������ RuntimeClass ��� ��ũ��
#define RUNTIME_CLASS(classname)    &(classname::class##classname)


class Animal
{
	DECLARE_DYNAMIC(Animal);
};
IMPLEMENT_DYNAMIC(Animal)

class Dog : public Animal
{
	DECLARE_DYNAMIC(Dog);
};
IMPLEMENT_DYNAMIC(Dog)

//---------------------------------------------

void foo(Animal* p)
{
	if (p->GetRuntimeClass() == RUNTIME_CLASS(Dog))
		cout << "p�� Dog�Դϴ�." << endl;
	if (p->GetRuntimeClass() == RUNTIME_CLASS(Animal))
		cout << "p�� Animal�Դϴ�." << endl;
}

int main()
{
	Animal ani;
	foo(&ani);
	Dog dog;
	foo(&dog);
}
