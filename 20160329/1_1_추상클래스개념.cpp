// http://d.pr/n/1hK8e
#include <iostream>
using namespace std;

// �߻� Ŭ���� (abstract class)
// ����: ���� ���� �Լ��� 1�� �̻� �ִ� Ŭ����
// �ǵ�: �Ļ� Ŭ�������� Ư�� �Լ��� �ݵ�� ������ �����ϴ� ��
// C++������ �߻� Ŭ������ ���� ����(abstract keywork)�� �������� �ʴ´�.
// �������̽� (interface)�� ������ ���� ���� ���� �ִ� Ŭ����

class Shape
{
public:
	virtual void draaw() = 0;	// ���� ���� �Լ� (pure virtual function)
};

class Rect : public Shape	// draw()�� �����θ� �������� ������ ���� �߻� Ŭ�����̴�.
{

};

int main()
{
	Shape s;
	Rect r;
}
