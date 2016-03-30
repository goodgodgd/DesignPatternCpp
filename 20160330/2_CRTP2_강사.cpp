
#include <iostream>
using namespace std;

// LimitMaxObject<5>
// LimitMaxObject<5>

// �Ʒ��� ������ CRTP�� �̿��ؼ� ���� �ٸ� ���� ������
// ����ϴ� ����Դϴ�.

// ��ü�� ������ N���� �����ϴ� ���
template <typename T, int N>
class LimitMaxObject
{
  static int n;
public:
  LimitMaxObject()
  {
    if (++n > N)
      throw 1;
  }
};

template <int N>
int LimitMaxObject<N>::n = 0;

class Mouse : public LimitMaxObject<Mouse, 5>
{
};

class Keyboard : public LimitMaxObject<Keyboard, 5>
{
};


int main()
{
  try {
    Mouse m[3];
    Keyboard k[3];
  } catch (...) {
    cout << "��ü ���� ����" << endl;
  }
}