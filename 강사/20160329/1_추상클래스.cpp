// 1_�߻�Ŭ����
// \\192.168.2.234 - ���� ����
#include <iostream>
using namespace std;

// http://d.pr/n/1hK8e
// �߻� Ŭ����(abstract class)
// ����: ���� ���� �Լ��� 1�� �̻� �ִ� Ŭ����
// �ǵ�: �Ļ� Ŭ�������� Ư�� �Լ��� �ݵ�� ������ �����ϴ� ��
class Shape
{
public:
  virtual void draw() = 0; // ���� ���� �Լ�(pure virtual function)
};

class Rect : public Shape // draw()�� �����θ� �������� ������
{                         // ���� �߻� Ŭ�����̴�.
};

int main()
{
  Shape s;
  // Rect r;
}