// ������� Composite Pattern���� �����Ǿ� �ִ�. ������ �ȿ� ������ ���� �� �־�.
// A������ �ȿ� B������ ���� �� B�����츦 Ŭ�������� A���� å���� ������ ���� �־�� �Ѵ�.

// MVC ��
// View: ȭ��, Model: ������, App(control): ���ð�ü����
// view���� �̺�Ʈ�� ������ app���ε� å���� �����Ǿ�� �Ѵ�. (���ᴩ���� app ����Ǿ��)

// å���� ���� ����
// - �̺�Ʈ �߻��� ó������ ���� ��� ���� ��ü�� �����Ѵ�.
// - ó���� �� ���� �� ���� ���� ���� �̺�Ʈ�� �����Ѵ�.

// ���
// 1) ��Ų��� �迭 - ���ھ�, ���ھ� ��ġ: Reponder Chain
//		: View -> ViewController -> AppDelegate
// 2) MFC���� �޴� �޽��� - å���� ��
//		: View -> Document -> Frame(�ֻ��� ������) -> App

// �ѹ��� ��� ��ü�� �̺�Ʈ �߻��ϸ� �ȵǳ�? �ڽĿ��� å���� ó���� �� ������ �ű⼭ ������

#include <iostream>
using namespace std;

#include <map>
#include <vector>
#include "ioacademy.h"
using namespace ioacademy;

class Window
{
	static map<int, Window*> this_map;

	int handle;					// C�Լ��� ���� �����츦 ������ �����ϱ� ���ؼ��� �ݵ�� �����ؾ� �Ѵ�.
	Window* parent;				// �θ� ������� 1���̴�.
	vector<Window*> children;	// �ڽ��� �������̴�.
	// composit �Ƴ�?
public:
	Window() : parent(0) {}

	void addChild(Window* p)
	{
		p->parent = this;
		children.push_back(p);
		
		// C �Լ��� �ڽ� �����츦 ���δ�.
		IoAddChild(this->handle, p->handle);
	}

	void create()
	{
		// �Ϲ� ��� �Լ� �� �޴´�.
		handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	virtual void onLButtonDown() {}
	virtual void onKeyDown() {}

	// static �̾�߸� IoMakeWindow�� ���޵� �� �ִ�.
	// �׷� this�� ���� �� �ְ� map�� ��� �Ѵ�.
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			self->onLButtonDown();
			break;
		case WM_KEYDOWN:
			self->onKeyDown();
			break;

		}
		// ���� �߻����� ����
		return 0;
	}
};

// static�� �ܺ� ���� �ʿ�
map<int, Window*> Window::this_map;

class MyWindow : public Window
{
public:
	// Window �޽��� �ڵ鷯 �߿��� �ڽ��� �ʿ��� �κ��� �����Լ��� ����
	virtual void onLButtonDown() {
		cout << "LButton" << endl;
	}
};

class ImageView : public Window
{
public:
	virtual void onLButtonDown()
	{
		cout << "Image" << endl;
	}
};

int main()
{
	MyWindow w;
	w.create();		// �� ���� �����찡 ��������� �մϴ�.

	ImageView imageView;
	imageView.create();

	w.addChild(&imageView);

	IoProcessMessage();
}
