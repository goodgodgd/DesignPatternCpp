// Window�� ĸ��ȭ �غ��ô�.
// Window�� ����Ѵٴ� ���� event-driven method ����, Ŭ��, Ű���忡 ���� message handler ����

// http://d.pr/n/mDpc

#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

// �⺻���� message handler�� ����ϱ� ���� ���ڵ� ���� �˾ƾ� �� ���� ����.
#if 0
int foo(int handle, int msg, int param1, int param2)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		cout << "left button down" << endl;
		break;
	case WM_KEYDOWN:
		cout << "key down" << endl;
		break;

	}
	// ���� �߻����� ����
	return 0;
}

int main()
{
	int h1 = IoMakeWindow(foo);	// window ����� �̺�Ʈ �ڵ鷯 ����
	IoProcessMessage();	// message loop ������
}
#endif

#include <map>

class Window
{
	static map<int, Window*> this_map;
public:
	void create()
	{
		// �Ϲ� ��� �Լ� �� �޴´�.
		int handle = IoMakeWindow(foo);
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
	virtual void onKeyDown() {
		cout << "Key Down" << endl;
	}

};

int main()
{
	MyWindow w;
	w.create();		// �� ���� �����찡 ��������� �մϴ�.
					// ���� ��ư�� ������ "LButton" �̶�� ��µǾ�� �մϴ�.
	IoProcessMessage();
}
