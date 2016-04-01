
#include <iostream>
using namespace std;

// LimitMaxObject<5>
// LimitMaxObject<5>

// 아래의 예제는 CRTP를 이용해서 서로 다른 정적 변수를
// 사용하는 기술입니다.

// 객체의 생성을 N개로 제한하는 기술
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
    cout << "객체 생성 실패" << endl;
  }
}