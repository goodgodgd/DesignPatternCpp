// Flyweight Pattern
// �Ӽ��� ������ ��ü�� �ߺ��ؼ� ������ ���� ���� ��ü�� �����ϵ��� �����ڸ� �����Ѵ�.

// �����ϴ� ���
// 2. ���� ���丮 �޼ҵ� - Effective Java
//	: ���� ��� ���� ���丮 �޼ҵ带 ���ؼ� �ش��ϴ� ������ �ذᰡ���ϴ�.
//	ObjectiveC - ���� ������


// ���� ���丮 �޼ҵ� - �������� �Ѱ� �غ�
// 1. �������� �̸��� ������ Ŭ���� �̸��� �����ϴ�.
//		Image(String path), Image(String url) - �����ε��� �ȵȴ�
//		- �����ε��� �Ѱ踦 �غ��� �� �ִ�. ���� �޼ҵ� �̸��� �ٲ��� �� �ִ�.
// 2. ���� ������ ������ �� �ִ�.
//		Color(int r, int g, int b) {}
//		Color* red = new Color(255,0,0);
//		���� �Ʒ��� ����.
//		static Color* newRedColor()
//		{ return new Color(255,0,0) }
//		Color* red = Color::newRedColor();
// 3. ��ü�� �����ϴ� ��å�� ������ �� �ִ�.
//		- new: ���ο� ��ü�� ������ �� �ִ�.
//		- ���� ���丮 �޼ҵ�: �̱���, �ö��̿���Ʈ, ������ �̱���
// 4. Ȱ��
//		List<Integer> arr = new ArrayList();
//		for(int i=0; i<100; ++i)
//			arr.add(i);		->  �����Ϸ��ؼ� arr.add(Integer.valueOf(i));  
//								valueOf: ���� ���丮 �޼ҵ�, ���� ���̴� ���� ���� ���� �̸� �����س��� �װ��� �ش�.

// �߿�: ��ü�� "�Һ� ��ü"�� �����ؾ� �Ѵ�.
// Flyweight���� ���� ��ü�� �����ϰ� �ִ� �ټ��� �����Ͱ� �ִµ� ��ü�� ���� �ٲٸ� ��� �������� ���� �ٲ��.
// �Һ� ��ü: ���������� ��� ���� ������ �ְ� set()�� �������� �ʴ´�.
// ��Ƽ �����忡�� ����ȭ �̽� ���� ��ü
// �Һ� ��ü�� �����ϰ� �ʹٸ� ����� �� ��ü�� �������� �Ѵ�.

#include <string>
#include <iostream>
using namespace std;
#include <map>

#include <Windows.h>	// Sleep(ms)

// �̹��� Ŭ���� �ϳ��� ���丮 ����� ������, ���� ��å�� ���ο� �־� ������ �� Image�� �������� ��
class Image
{
	string url;
	static map<string, Image*> cache;
public:
	static Image* imageWithURL(const string& url)
	{
		if (cache[url] == 0)
			cache[url] = new Image(url);
		return cache[url];
	}
	void draw()
	{
		cout << "Draw Image : " << url << endl;
	}

private:
	// private ������ - Image ���� ���� ����
	Image(const string& s) : url(s)
	{
		cout << "Load from " << url << endl;
		Sleep(3000);
	}
};

map<string, Image*> Image::cache;

int main()
{
	// ���� �̹����� �����ϴµ� �ð��� �ι� ���� �ȴ�.
	Image* image1 = Image::imageWithURL("http://www.a.com/a.png");
	image1->draw();

	Image* image2 = Image::imageWithURL("http://www.a.com/a.png");
	image2->draw();
}