// Flyweight Pattern
// 속성이 동일한 객체를 중복해서 만들지 말고 같은 객체를 참조하도록 생성자를 제어한다.

// 구현하는 방법
// 2. 정적 팩토리 메소드 - Effective Java
//	: 공장 대신 정적 팩토리 메소드를 통해서 해당하는 문제를 해결가능하다.
//	ObjectiveC - 편의 생성자


// 정적 팩토리 메소드 - 생성자의 한계 극복
// 1. 생성자의 이름은 무조건 클래스 이름과 동일하다.
//		Image(String path), Image(String url) - 오버로딩이 안된다
//		- 오버로딩의 한계를 극복할 수 있다. 생성 메소드 이름을 바꿔줄 수 있다.
// 2. 좋은 가독성 제공할 수 있다.
//		Color(int r, int g, int b) {}
//		Color* red = new Color(255,0,0);
//		보다 아래가 낫다.
//		static Color* newRedColor()
//		{ return new Color(255,0,0) }
//		Color* red = Color::newRedColor();
// 3. 객체를 생성하는 정책을 변경할 수 있다.
//		- new: 새로운 객체를 생성할 수 있다.
//		- 정적 팩토리 메소드: 싱글톤, 플라이웨이트, 스레드 싱글톤
// 4. 활용
//		List<Integer> arr = new ArrayList();
//		for(int i=0; i<100; ++i)
//			arr.add(i);		->  컴파일러해석 arr.add(Integer.valueOf(i));  
//								valueOf: 정적 팩토리 메소드, 자주 쓰이는 작은 값에 대해 미리 생성해놓고 그것을 준다.

// 중요: 객체를 "불변 객체"로 설계해야 한다.
// Flyweight에서 같은 객체를 참조하고 있는 다수의 포인터가 있는데 객체의 값을 바꾸면 모든 포인터의 값이 바뀐다.
// 불변 객체: 내부적으로 모든 값이 정해져 있고 set()을 제공하지 않는다.
// 멀티 스레드에서 동기화 이슈 없는 객체
// 불변 객체를 변경하고 싶다면 변경된 새 객체를 만들어줘야 한다.

#include <string>
#include <iostream>
using namespace std;
#include <map>

#include <Windows.h>	// Sleep(ms)

// 이미지 클래스 하나로 팩토리 기능이 응집됨, 생성 정책이 내부에 있어 재사용할 때 Image만 가져가면 됨
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
	// private 생성자 - Image 직접 생성 못해
	Image(const string& s) : url(s)
	{
		cout << "Load from " << url << endl;
		Sleep(3000);
	}
};

map<string, Image*> Image::cache;

int main()
{
	// 같은 이미지를 생성하는데 시간이 두번 들어가게 된다.
	Image* image1 = Image::imageWithURL("http://www.a.com/a.png");
	image1->draw();

	Image* image2 = Image::imageWithURL("http://www.a.com/a.png");
	image2->draw();
}