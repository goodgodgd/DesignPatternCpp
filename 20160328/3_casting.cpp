// ���� �޸� �Ҵ� �� ĳ����
// ĳ������ � ��� �����ϰ� � ��� �׷��� ������?
// http://d.pr/n/16nTT
#include <iostream>
using namespace std;

// 1. C�� ĳ������ �� �̼����δ�.
// 2. �׷��� C++ 4���� ĳ������ ���� �����մϴ�.
//	- static_cast: void* -> �ٸ� Ÿ�� �Ǵ� ������ �ִ� ĳ���ø� ��� (int->long, double->float) ū Ÿ�Կ��� ���� Ÿ������
//	- reinterpret_cast: �޸� ���ؼ�, ���� ���� but ���� �ʿ�
//	- const_cast: ��ü�� �����, �ֹ߼� ����, ����� Ÿ�� ���� �δ�
//	- dynamic_cat: ��ӿ��� �ڽ�Ŭ������ �����͸� �θ�Ŭ������ �����ͷ� ĳ���� �ϴ� ���� �����ϹǷ� �׳� ������ (�θ� is a �ڽ�)
//				�ݴ�� �θ�Ŭ���� �����͸� �ڽ�Ŭ���� �����ͷ� ĳ������ ���� dynamic_cast �ʿ�
//				RTTI ��� �ʿ�, �ٿ� ĳ���� �뵵

#if 0
int main()
{
	// int*�� void* �ѱ��� �� �Ѵ�.
//	int *p1 = malloc(sizeof(100));
	// static_cast
	int *p1 = static_cast<int*>(malloc(sizeof(100)));

	int n = 0;
	// �� �̼��� ĳ����: �޸� �絵 ������ �޶�, ���������� �� �̼���
	double* p2 = (double*)&n;
	// static_cast: �̼��� ĳ���� Ȯ�� -> �Ұ���
//	double* p2 = static_cast<double*>(&n);
	// reinterpre_cast: �� �̼��� ĳ���� ���������� �׻� �����ؼ� ����ؾ� ��
	double* p3 = reinterpret_cast<double*>(&n);
	// �����ϵ����� ����� ���� �߻�
//	*p3 = 3.14;
}
#endif

int main()
{
	const int c = 10;
	// c�� const �̹Ƿ� �Ұ�
//	int* p = &c;
//	int* p = static_cast<int*>(&c);
//	int* p = reinterpret_cast<int*>(&c);
	// ��� �����ͷθ� ����
	const int* p = &c;
	// const_cast�� ���� �Ϲ� �����ͷ� �Ҵ� ����
	// const_cast: ����� ����
	int* p1 = const_cast<int*>(&c);
	*p1 = 20;
	cout << c << endl;	// 10
	cout << *p << endl;	// 20
	cout << *p1 << endl;	// 20
	// const ������ ���� �ٲٸ� �ǵ����� ���� ��� �߻��� �� �ִ�!!

	// const�� "�޸�"�� ������� �ʴ´�.
	// volatile�� "�ֹ߼�" ??
	// ���� ������ �������Ϳ� �ε�� ���� ���µ� volatile�� �׻� �޸𸮿� ���� �����Ͽ� ����Ѵ�.
	// �׸��� volatile ������ ������ ����ȭ ���� �ʰ� �ڵ忡 ���� �״�� �����ϰ� �Ѵ�.
	volatile int c1 = 10;

	// const_cast�� �ֹ߼� ����
	//	int* p = static_cast<int*>(&c);
	int* p2 = const_cast<int*>(&c1);
	*p2 = 20;
	cout << c1 << endl;	// 10
	cout << *p2 << endl;	// 20
}
