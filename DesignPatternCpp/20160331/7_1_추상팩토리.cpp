// Abstract Factory Pattern
// 의도: 공장도 인터페이스 기반으로 설계해서 교체 가능하게 하자.

// Qt에서 제공하는 GUI Look & Feel의 원리를 살펴봅시다.
// main 인자에 따라 윈도우 스타일 달라짐
// a.exe --style=GTK --style=XP

#include <string>

#if 0
struct IButton {};

class XPButton : public IButton {};
class GTKButton : public IButton {};

struct IEdit {};
class XPEdit : public IEdit {};
class GTKEdit : public IEdit {};


int main(int argc, char* argv[])
{
	IButton* p1;
	IEdit* p2;
	//...
	if (strcmp(argv[1], "--style=GTK"))
	{
		p1 = new GTKButton;
		p2 = new GTKEdit;
		//...
		// 요소가 늘어날수록 계속 생성 목록이 길어진다.
	}
	else if (strcmp(argv[1], "--style=GTK"))
	{
		p1 = new XPButton;
		p2 = new XPEdit;
		//...
		// 요소가 늘어날수록 계속 생성 목록이 길어진다.
	}
}
#endif

struct IButton {};

class XPButton : public IButton {};
class GTKButton : public IButton {};

struct IEdit {};
class XPEdit : public IEdit {};
class GTKEdit : public IEdit {};


struct IFactory
{
	virtual IButton* createButton() = 0;
	virtual IEdit* createEdit() = 0;
};

// 스타일에 따라 컨트롤을 만드는 공장을 도입하자.
// XP 스타일 공장
class XPFactory : public IFactory
{
public:
	IButton* createButton() { return new XPButton; }
	IEdit* createEdit() { return new XPEdit; }
	// ...
};

// GTK 스타일 공장
class GTKFactory : public IFactory
{
public:
	IButton* createButton() { return new GTKButton; }
	IEdit* createEdit() { return new GTKEdit; }
	// ...
};

int main(int argc, char* argv[])
{
	// 스타일을 묶어서 한번에 선택
	IFactory* factory;
	if (strcmp(argv[1], "--style=GTK"))
		factory = new GTKFactory;
	else if (strcmp(argv[1], "--style=XP"))
		factory = new XPFactory;

	// 이제 진짜 객체 생성
	IButton* p1 = factory->createButton();
	IEdit* p2 = factory->createEdit();
	//...
}

