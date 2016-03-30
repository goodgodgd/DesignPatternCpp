// http://d.pr/n/1hK8e
#include <iostream>
using namespace std;

// 추상 클래스 (abstract class)
// 정의: 순수 가상 함수가 1개 이상 있는 클래스
// 의도: 파생 클래스에게 특정 함수를 반드시 만들라고 지시하는 것
// C++에서는 추상 클래스에 대한 문법(abstract keywork)을 제공하지 않는다.
// 인터페이스 (interface)는 구현이 전혀 없이 명세만 있는 클래스

class Shape
{
public:
	virtual void draaw() = 0;	// 순수 가상 함수 (pure virtual function)
};

class Rect : public Shape	// draw()의 구현부를 제공하지 않으면 역시 추상 클래스이다.
{

};

int main()
{
	Shape s;
	Rect r;
}
