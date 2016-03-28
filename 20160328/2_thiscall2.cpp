#include <iostream>
using namespace std;
// http://d.pr/n/19aU4

class Sample
{
	int data;
public:
	void f1()	// f1(Sample* this = 0) �ε� �޸� ������ ���� ������ ���� ����
	{ cout << "f1" << endl;	}
	int f2()
	{ cout << "f2" << endl; return 0; }
	int f3()
	{
		cout << "f3" << endl; 
		return data;	// this->data �� �ǹǷ� error!
	}

	// MFC, Android ������ ����ϴ� �ڵ�
	// C++ idom: ����� Ư�� �̿� - ���¼ҽ� ���ؿ� �ʿ�
	// �� idiom�� C++ ǥ�ؿ��� �ǵ��� ���� �ƴϹǷ� (undefined) �����Ϸ��� ���� ������ �޶��� �� �ִ�.
	// Android������ �ֽ� ���������� ������
	// �ֽŹ��������� static function(Sample* ptr) ���·� ��������� ������
	// MFC������ �����, ������ ���� 
	// clang�� ���� ��Ʈ�� �����Ϸ��� �Ǿ���, �ֿ� ������Ʈ�� �⺻ �����Ϸ��� ���ǰ� ����. webkit, chromium
	// LLVM������ �ٷ� binary�� ������ �ʰ� intermediate language�� ����� �� ���� binary �����.
	// �׷��� ���� �޽����� ���Ⱑ ����.
	// ���� ������ LLVM clang���� ���� binary�� ������ �� �������µ� �ֱٿ� ���� ������ �ذ��
	// ���������� C++ �ڵ带 �����Ѵٸ� clang�� ����!!
	int call_f3()
	{
		return this ? f3() : NULL;	// this==NULL �� ��� ����ó��
	}
};

int main()
{
	Sample* p = 0;	// new �޸� �Ҵ��� �ϴٰ� �����ؼ� 0�� ���Դٰ� ����
	p->f1();			// f1(p) nullptr �ε��� ���� ����
	p->f2();			// f2(p)
//	p->f3();			// error!
	cout << p->call_f3() << endl;			// ����ó��
}
