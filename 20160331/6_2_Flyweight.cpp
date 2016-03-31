// Flyweight Pattern
// �����ϴ� ���
// 1. ���丮: ��ü�� ����� ������ �����ϴ� ��, ������ ���� �ƴϴ�.

#include <string>
#include <iostream>
using namespace std;
#include <map>

#include <Windows.h>	// Sleep(ms)

class Image
{
	string url;
	// private ������ - Image ���� ���� ����
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

// Image ��ü�� ����� ����
// - ��ü�� ������ �� ������ �߾� ���������� ������ �� �ִ�.
// - �ϳ��� ������ �ǹǷ� �̱������� �����.
// - �̱��� ���丮�� ����: ���丮�� ����Ǹ� �̰����� ��ü�� �����ϴ� �ٸ� ��� Ŭ������ �ٲ���Ѵ�.?????
//		--> ���� ���丮 �޼ҵ�
class ImageFactory
{
	map<string, Image*> cache;
private:
	ImageFactory() {}
	ImageFactory(const ImageFactory*) = delete;
	void operator=(const ImageFactory&) = delete;
		
public:
	// Image ������ ĸ��ȭ
	static ImageFactory& getInstance()
	{
		static ImageFactory instance;
		return instance;
	}

	Image* createImage(const string& url)
	{
		// ������ �ִ��� Ȯ��, ������ ����
		if (cache[url] == 0)
			cache[url] = new Image(url);
		return cache[url];
	}
};


int main()
{
	// ���� �̹����� �����ϴµ� �ð��� �ι� ���� �ȴ�.
	// -> new�� ���� �����ϸ� �ȵ�, ����ڰ� ������� ����

	ImageFactory& factory = ImageFactory::getInstance();

	Image* image1 = factory.createImage("http://www.a.com/a.png");
	image1->draw();
	Image* image2 = factory.createImage("http://www.a.com/a.png");
	image2->draw();
}