// Flyweight Pattern
// �ǵ�: �Ӽ��� ������ ��ü�� ��������!

// �����ϴ� ���
// 1. ���丮			: ��ü ���� ����� Ŭ������ ����
// 2. ���� ���丮 �޼ҵ�: ��ü ���� ����� ���� Ŭ���� ������ ���� �޼ҵ�� ����

#include <string>
#include <iostream>
using namespace std;

#include <Windows.h>	// Sleep(ms)

class Image
{
	string url;
public:
	// ���� ������ ���� �ɸ��� ��ü��� �Ӽ��� ���� ��ü�� ������ �����ϴ°��� �δ㽺����.
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
	// ���� �̹����� �����ϴµ� �ð��� �ι� ���� �ȴ�.
	Image* image1 = new Image("http://www.a.com/a.png");
	image1->draw();

	Image* image2 = new Image("http://www.a.com/a.png");
	image2->draw();
}