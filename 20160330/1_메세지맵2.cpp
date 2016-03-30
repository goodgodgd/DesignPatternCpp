// 1_�޼�����
// MFC, wsWidget ��� ���� ���̰� �մ�.
// : ���� �Լ� ���̺��� ������带 ���̱� ���� ����ڰ� ���� ���̺��� �����ϵ��� ����� ����Դϴ�.
//	�޽��� ���� ���������� �����ϴ�. ����ڰ� ���ϰ� ������ �ڵ带 ���������
//	-> ������ �ڵ带 ��ũ�η� �����մϴ�.
//		��ũ�δ� �����Ϸ� ���� ��ó���� �ڵ� �����

#include "ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

class Window;

struct AFX_MSG
{
	int message;				// �޼��� ��ȣ
	void(Window::*handler)();	// ó���� �Լ��� �ּ�
};

class Window
{
	static map<int, Window*> this_map;
public:

	// ���� ��� �ڽ� Ŭ������ �ڽ��� ó���ϰ��� �ϴ� �̺�Ʈ�� �̺�Ʈ �ڵ鷯�� �����ؾ� �Ѵ�.
	virtual AFX_MSG* GetMessageMap() { return 0; }	// �ϴ� �θ�� ó���� �̺�Ʈ�� ���ٰ� ���� 0

	void create()
	{
		// ������ �̺�Ʈ �ڵ鷯 ���
		int handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	// �̹� ������ �ٽ��� �Ʒ� �Լ��Դϴ�. - �̺�Ʈ ó����
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];

		if (self == 0) return 0;

		// 1. �迭�� ���´�.
		AFX_MSG* msgArray = self->GetMessageMap();
		if (msgArray == 0)	// ó���� �޽����� ���� ���
			return 0;

		// 2. �迭�� ���� �޼����� �ִ��� ���θ� Ȯ���ϰ� ��ϵ� �ڵ鷯�� ȣ���Ѵ�.
		for (; msgArray->message != 0; msgArray++)
			if (msgArray->message == msg)
			{
				void(Window::*f)() = msgArray->handler;
				(self->*f)();
			}
		return 0;
	}
};

map<int, Window*> Window::this_map;

#if 0
class MyWindow : public Window
{
public:
	void onLButtonDown() {
		cout << "LButton" << endl;
	}

	void onKeyDown() {
		cout << "Key Down" << endl;
	}

	virtual AFX_MSG* GetMessageMap()
	{
		// MyWindow::onLButtonDown �� ���� �ڽ��� �Լ� �����Ͱ� �ƴϱ� ������ ���� ����.
		typedef void(Window::*HANDLER)();
		// ���⿡ �ʿ��� �̺�Ʈ�鸸 ��������ָ� �ȴ�. ��� �̺�Ʈ�� ���� �����Լ� ������ �ʾƵ� �ȴ�.
		// �Ź� �Ȱ��� msgMap�� ������ �ʱ� ���� static ����
		static AFX_MSG msgMap[] = {
			{ WM_LBUTTONDOWN, static_cast<HANDLER>(&MyWindow::onLButtonDown) },
			{ WM_KEYDOWN, static_cast<HANDLER>(&MyWindow::onKeyDown) },
			{ 0, 0 }
		};
		// 0,0 ���� �迭�� �� ǥ��
		return msgMap;
	}
};
#endif

//----------
// GetMessageMap()�� �����ϴ� ��ũ���Դϴ�.
// ���� MyWindow �� ��ũ�η� ����

// ������� GetMessageMap() �Լ�����
#define DECLARE_MESSAGE_MAP()                   \
  virtual AFX_MSG* GetMessageMap();

// �ҽ����� �Լ� ���ۺο� �迭 ����
#define BEGIN_MESSAGE_MAP(classname)           \
  AFX_MSG* classname::GetMessageMap()           \
  {                                             \
    typedef void(Window::*HANDLER)();           \
    static AFX_MSG msgMap[] = {

// �迭�� �޽����� �Լ� ������ �� �߰�
#define ADD_MAP(message, handler)               \
  { message, static_cast<HANDLER>(handler) },

// �迭 ���� ǥ�� �� �Լ� ����
#define END_MESSAGE_MAP()                       \
      { 0, 0 }                                  \
  };                                            \
  return msgMap;                                \
}

// .h
class MyWindow : public Window
{
public:
	void onLButtonDown() {
		cout << "LButton" << endl;
	}
	void onKeyDown() {
		cout << "Key Down" << endl;
	}

	DECLARE_MESSAGE_MAP()
};

// .cpp
BEGIN_MESSAGE_MAP(MyWindow)
	ADD_MAP(WM_LBUTTONDOWN, &MyWindow::onLButtonDown)
	ADD_MAP(WM_KEYDOWN, &MyWindow::onKeyDown)
END_MESSAGE_MAP()

/*
BEGIN_MESSAGE_MAP(MyWindow)
	ADD_MAP(WM_LBUTTONDOWN &MyWindow::onLButtonDown)
	ADD_MAP(WM_KEYDOWN, &MyWindow::onKeyDown)
END_MESSAGE_MAP()
*/

int main()
{
	MyWindow w;
	w.create();       // �� ���� �����찡 ��������� �մϴ�.
	// ���� ��ư�� ������ "LBUTTON" �̶�� ��µǾ�� �մϴ�.
	IoProcessMessage();
}
