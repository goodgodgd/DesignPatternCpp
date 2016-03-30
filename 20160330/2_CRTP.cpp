// MS ���̺긮�� �� WTL, ATL�� �Ʒ��� ���� ���� �Ǿ� �ֽ��ϴ�. (window / active template library)
// �����Լ��� ������ �ʰ�

// CRTP: Curiously Recurring Template Pattern - C++ idioms
// ���� ���� ���̴� idom
// : �θ� Ŭ������ ���ø��ε� �ڽĿ��� ���ø��� ���ڷ� �ڽ��� Ÿ���� �����ϴ� ���

// ���� �̸��� mixin template
// ����: �̵�� ������ ����Ʈ https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
// C++ Ư¡: �ڵ带 ���� �ǵ��� �ľ��ϱ� ��ƴ�.

// �������� Ȱ���� �����Ѵ�, �Ʒ� �ڵ�� �񰡻��Լ��� �����Լ�ó�� �����ϰ� ����� ���.
// onClick()�� �����Լ��� �ƴѵ� �����Լ�ó�� ���ȴ�. -> �����Լ� ���̺��� �ʿ����.
// ���ø��� ���� ������ ��Ÿ�ӿ� �̺�Ʈ ó���Ⱑ ����ð��� ����� �ʿ䰡 ���ٸ� ���� ���
// inline�� ���밡��

#include <iostream>
using namespace std;

#if 0
class Window
{
public:
	void msgLoop()
	{
		onClick();
	}

	void onClick()	{ cout << "Window on Click" << endl; }
};

//class MyWindow : public Window
class MyWindow : public Window
{
public:
	void onClick()
	{
		cout << "My Window on Click" << endl;
	}
};

int main()
{
	MyWindow w;
	// �̷��� ���� �θ� �������� �޽����� ó���ϰ� �Ǽ� Window::onClick �� ����ȴ�.
	// ���� ���ϴ� ���� MyWindow::onClick
	w.msgLoop();
}
#endif

// ���ø����� �ڽ� Ŭ���� Ÿ�� �޾ƿ�
template <typename T>
class Window
{
public:
	void msgLoop()
	{
//		onClick();
// �̰��� ������ ����. �׷��� Window::onClick()
//		this->onClick();
// �׷��� MyWindow�� ���� ȣ���ϰ� �ʹٸ�
//		static_cast<MyWindow*>(this)->onClick();

		// �̷��� ���� ������ ���� �ʰ� ���ø����� �����ϰ� ȣ���� �� �ִ�.
		static_cast<T*>(this)->onClick();
	}

	void onClick()	{ cout << "Window on Click" << endl; }
};

class MyWindow : public Window<MyWindow>
{
public:
	void onClick()
	{
		cout << "My Window on Click" << endl;
	}
};

int main()
{
	MyWindow w;
	// ������ MyWindow::onClick �� ����ȴ�.
	w.msgLoop();
}
