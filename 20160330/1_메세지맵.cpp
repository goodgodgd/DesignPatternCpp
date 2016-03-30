// 1_�޼�����
// MFC, wsWidget ��� ���� ���̰� �մ�.
// : ���� �Լ� ���̺��� ������带 ���̱� ���� ����ڰ� ���� ���̺��� �����ϵ��� ����� ����Դϴ�.
//		-> ������ �� ���� �Լ��� ���ٸ� ���� �Լ��� ���� ���� ����.

#include "ioacademy.h"
using namespace ioacademy;

// �����Լ��� ���� �����Լ��� ������ŭ �����Լ� �����Ͱ� �����.
// �����쿡�� ���� �޽��� ������ õ���� �Ѿ�, ��� �����Լ��� ����� ������ �ϳ� �� 8k �̻��� �޸� �Ҹ�
// �����Լ��� ����� ���̱� ���� "�޽�����"�� �����ߴ�.
// �޽��� ���� ���������� �����ϴ�. ����ڰ� ���ϰ� ������ �ڵ带 ���������->��ũ�� ���

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

	// ���� �ʿ����� �ʾ�
//  virtual void onLButtonDown() {}
//  virtual void onKeyDown() {}

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


int main()
{
  MyWindow w;
  w.create();       // �� ���� �����찡 ��������� �մϴ�.
                    // ���� ��ư�� ������ "LBUTTON" �̶�� ��µǾ�� �մϴ�.
  IoProcessMessage();
}
