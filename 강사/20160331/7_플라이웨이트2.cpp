// 7_플라이웨이트2(Flyweight) 
#include <iostream>
#include <string>

using namespace std;

#include <Windows.h>  // Sleep(ms)

// 플라이웨이트 패턴
// 의도 : 속성이 동일한 객체는 공유하자!



class Image
{
  string url;

  Image(const string& s) : url(s)
  {
    cout << "Loading from " << url << endl;
    Sleep(3000);
  }
public:
  void draw()
  {
    cout << "Draw Image : " << url << endl;
  }

  friend class ImageFactory;
};

// 구현하는 방법
// 1. 팩토리: 객체를 만드는 역활을 수행하는 것

// Image 객체를 만드는 공장
// - 객체의 생성을 한 곳에서 중앙 집중적으로 관리할 수 있다.
#include <map>
class ImageFactory
{
  // 공장은 싱글톤인 경우가 많다.
  map<string, Image*> cache;
public:
  Image* createImage(const string& url)
  {
    if (cache[url] == 0)
      cache[url] = new Image(url);

    return cache[url];
  }

  static ImageFactory& getInstance() {
    static ImageFactory instance;
    return instance;
  }


private:
  ImageFactory() {}
  ImageFactory(const ImageFactory&) = delete;
  void operator=(const ImageFactory&) = delete;
};

int main()
{
  ImageFactory& factory = ImageFactory::getInstance();

  Image* image1 = factory.createImage("http://www.a.com/a.png");
  image1->draw();

  Image* image2 = factory.createImage("http://www.a.com/a.png");
  image2->draw();
}



