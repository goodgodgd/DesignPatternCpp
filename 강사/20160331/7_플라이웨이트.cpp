// 7_플라이웨이트(Flyweight) 
#include <iostream>
#include <string>

using namespace std;

#include <Windows.h>  // Sleep(ms)

// 플라이웨이트 패턴
// 의도 : 속성이 동일한 객체는 공유하자!

// 구현하는 방법
// 1. 팩토리
// 2. 정적 팩토리 메소드


class Image
{
  string url;
public:
  Image(const string& s) : url(s)
  {
    cout << "Loading from " << url << endl;
    Sleep(3000);
  }

  void draw()
  {
    cout << "Draw Image : " << url << endl;
  }
};

int main()
{
  Image* image1 = new Image("http://www.a.com/a.png");
  image1->draw();

  Image* image2 = new Image("http://www.a.com/a.png");
  image2->draw();
}



