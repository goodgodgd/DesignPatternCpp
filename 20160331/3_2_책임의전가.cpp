// GoF�� ������ ���Ͽ����� �̺�Ʈ ó���� ���õ� ������ 2���� �ֽ��ϴ�.
// 1. ������			: �̺�Ʈ �߻��� ��ϵ� ��ü���� �̺�Ʈ�� ����
// 2. å���� ����	: �̺�Ʈ �߻��� ���� ��ü���� ����

// ���� 3���� ����: ����, ����, ����

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

	virtual bool onLButtonDown() { return false; }
	virtual void onKeyDown() {}

	// ������: fireLButtonDown�� ��ӵ� �ʿ䰡 ���� "����"�̹Ƿ� private ���ش�. foo�� ���ο����� ���
private:
	// �Ʒ� �Լ��� å���� ����(Chain of Responsibility) ������ �ٽ��Դϴ�.
	void fireLButtonDown()
	{
		// 1. ���� �ڽ�(�ڽ�)�� ó���� �õ��մϴ�.
		if (onLButtonDown() == true)	// �ڽ��� ó���ؼ� ���� �� ������ ���⼭ ����
			return;
		
		// 2. �ڽ��� ó������ ���� ��� �θ𿡰� ����
		if (parent != 0)
			parent->fireLButtonDown();
	}

	// static �̾�߸� IoMakeWindow�� ���޵� �� �ִ�.
	// �׷� this�� ���� �� �ְ� map�� ��� �Ѵ�.
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			// �� �����Լ��� ȣ���ؼ� ������ �θ��� �Լ��� ȣ��ǰ� �Ѵ�. -> å���� ����
			self->fireLButtonDown();
			//self->onLButtonDown();
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
	virtual bool onLButtonDown() {
		cout << "LButton" << endl;
		return false;
	}
};

class ImageView : public Window
{
public:
	virtual bool onLButtonDown()
	{
		cout << "Image" << endl;
		return false;
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
