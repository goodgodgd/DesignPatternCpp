// 1_추상클래스
// \\192.168.2.234 - 공유 폴더
#include <iostream>
using namespace std;

// http://d.pr/n/1hK8e
// 추상 클래스(abstract class)
// 정의: 순수 가상 함수가 1개 이상 있는 클래스
// 의도: 파생 클래스에게 특정 함수를 반드시 만들라고 지시하는 것
class Shape
{
public:
  virtual void draw() = 0; // 순수 가상 함수(pure virtual function)
};

class Rect : public Shape // draw()의 구현부를 제공하지 않으면
{                         // 역시 추상 클래스이다.
};

int main()
{
  Shape s;
  // Rect r;
}