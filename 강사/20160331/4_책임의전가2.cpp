// 4_å��������
#include "ioacademy.h"
using namespace ioacademy;

#include <map>
#include <vector>
#include <iostream>
using namespace std;

// ������ ���Ͽ����� �̺�Ʈ ó���� ���õ� ������ 2���� �ֽ��ϴ�.
// 1. ������     : �̺�Ʈ�� �߻��� ��ϵ� ��ü���� �̺�Ʈ�� ����
// 2. å���� ����: �̺�Ʈ �߻��� ���� ��ü���� ����
class Window
{
  static map<int, Window*> this_map;

  int handle;                // C �Լ��� ���� �����츦 ������ �����ϱ� ���ؼ���
                             // �ݵ�� �����ؾ� �Ѵ�.

  Window* parent;            // �θ� ������� 1���̴�.
  vector<Window*> children;  // �ڽ��� �������̴�.
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
    handle = IoMakeWindow(foo);
    this_map[handle] = this;
  }

  virtual bool onLButtonDown() { return false; }
  virtual void onKeyDown() {}

  // �Ʒ� �Լ��� å���� ����(Chain of Responsibility) ������ �ٽ��Դϴ�.
  void fireLButtonDown()
  {
    // 1. ���� �ڽ��� ó���� �õ��մϴ�.
    if (onLButtonDown() == true)
      return;

    // 2. �ڽ��� ó������ ���� ��� �θ𿡰� ����
    if (parent != 0)
      parent->fireLButtonDown();
  }

  static int foo(int handle, int msg, int param1, int param2)
  {
    Window* self = this_map[handle];

    switch (msg)
    {
    case WM_LBUTTONDOWN:
      self->fireLButtonDown();
      // self->onLButtonDown();
      break;

    case WM_KEYDOWN:
      self->onKeyDown();
      break;
    }

    return 0;
  }


};

map<int, Window*> Window::this_map;

class MyWindow : public Window
{
public:
  virtual bool onLButtonDown() {
    cout << "LButton" << endl;
    return false;
  }
};

class ImageView : public Window
{
public:
  virtual bool onLButtonDown() {
    cout << "Image" << endl;
    return false;
  }
};

int main()
{
  MyWindow w;
  w.create();

  ImageView imageView;
  imageView.create();

  w.addChild(&imageView);

  IoProcessMessage();
}
