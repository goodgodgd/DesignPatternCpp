// Abstract Factory Pattern
// �ǵ�: ���嵵 �������̽� ������� �����ؼ� ��ü �����ϰ� ����.

// Qt���� �����ϴ� GUI Look & Feel�� ������ ���캾�ô�.
// main ���ڿ� ���� ������ ��Ÿ�� �޶���
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
		// ��Ұ� �þ���� ��� ���� ����� �������.
	}
	else if (strcmp(argv[1], "--style=GTK"))
	{
		p1 = new XPButton;
		p2 = new XPEdit;
		//...
		// ��Ұ� �þ���� ��� ���� ����� �������.
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

// ��Ÿ�Ͽ� ���� ��Ʈ���� ����� ������ ��������.
// XP ��Ÿ�� ����
class XPFactory : public IFactory
{
public:
	IButton* createButton() { return new XPButton; }
	IEdit* createEdit() { return new XPEdit; }
	// ...
};

// GTK ��Ÿ�� ����
class GTKFactory : public IFactory
{
public:
	IButton* createButton() { return new GTKButton; }
	IEdit* createEdit() { return new GTKEdit; }
	// ...
};

int main(int argc, char* argv[])
{
	// ��Ÿ���� ��� �ѹ��� ����
	IFactory* factory;
	if (strcmp(argv[1], "--style=GTK"))
		factory = new GTKFactory;
	else if (strcmp(argv[1], "--style=XP"))
		factory = new XPFactory;

	// ���� ��¥ ��ü ����
	IButton* p1 = factory->createButton();
	IEdit* p2 = factory->createEdit();
	//...
}

