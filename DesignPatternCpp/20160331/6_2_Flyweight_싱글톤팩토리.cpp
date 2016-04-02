// Flyweight Pattern
// 구현하는 방법
// 1. 팩토리: 객체를 만드는 역할을 수행하는 것

#include <string>
#include <iostream>
using namespace std;
#include <map>

#include <Windows.h>	// Sleep(ms)

class Image
{
	string url;
	// private 생성자 - Image 직접 생성 못해
	Image(const string& s) : url(s)	
	{
		cout << "Load from " << url << endl;
		Sleep(3000);
	}

public:
	void draw()
	{
		cout << "Draw Image : " << url << endl;
	}
	friend class ImageFactory;

};

// Image 객체를 만드는 공장
// - 객체의 생성을 한 곳에서 중앙 집중적으로 관리할 수 있다.
// - 하나만 있으면 되므로 싱글톤으로 만든다.
class ImageFactory
{
	map<string, Image*> cache;
private:
	ImageFactory() {}
	ImageFactory(const ImageFactory*) = delete;
	void operator=(const ImageFactory&) = delete;
		
public:
	// 싱글톤 팩토리
	static ImageFactory& getInstance()
	{
		static ImageFactory instance;
		return instance;
	}

	// 여기가 핵심!!
	// cache를 이용해 기존에 같은 속성을 가진 객체가 있었는지 확인하는 것이 Flyweight Pattern
	Image* createImage(const string& url)
	{
		// 기존에 있는지 확인, 없으면 생성
		if (cache[url] == 0)
			cache[url] = new Image(url);
		return cache[url];
	}
};

int main()
{
	// 같은 이미지를 생성하는데 시간이 두번 들어가게 된다.
	// -> new를 통해 생성하면 안돼, 사용자가 생성방법 정의
	ImageFactory& factory = ImageFactory::getInstance();

	Image* image1 = factory.createImage("http://www.a.com/a.png");
	image1->draw();
	Image* image2 = factory.createImage("http://www.a.com/a.png");
	image2->draw();
}

// - 근데 클래스마다 팩토리 하나씩 만들기 귀찮다. --> 정적 팩토리 메소드 - 다음 코드에...
