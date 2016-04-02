// Flyweight Pattern
// 의도: 속성이 동일한 객체는 공유하자!

// 구현하는 방법
// 1. 팩토리			: 객체 생성 기능을 클래스로 구현
// 2. 정적 팩토리 메소드: 객체 생성 기능을 생성 클래스 내부의 정적 메소드로 구현

#include <string>
#include <iostream>
using namespace std;

#include <Windows.h>	// Sleep(ms)

class Image
{
	string url;
public:
	// 만약 생성이 오래 걸리는 객체라면 속성이 같은 객체를 여러번 생성하는것이 부담스럽다.
	Image(const string& s) : url(s)
	{
		cout << "Load from " << url << endl;
		Sleep(3000);
	}

	void draw()
	{
		cout << "Draw Image : " << url << endl;
	}
};

int main()
{
	// 같은 이미지를 생성하는데 시간이 두번 들어가게 된다.
	Image* image1 = new Image("http://www.a.com/a.png");
	image1->draw();

	Image* image2 = new Image("http://www.a.com/a.png");
	image2->draw();
}