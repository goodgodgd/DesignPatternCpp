// 6_Application Framework
#if 0
#include <iostream>
using namespace std;

// ���̺귯��: ���α׷� ���߿� �ʿ��� ������ �����ϴ� ��
//            (class, function)
// �����ӿ�ũ: ���� + �̸� ���ǵ� ���� �帧

// ���⼭���ʹ� ���̺귯�� ���� �ڵ� �Դϴ�. dll�� ������ �ֽ��ϴ�.
class CWinApp;
CWinApp* g_app;

class CWinApp
{
public:
  CWinApp() { g_app = this; }
  virtual bool InitInstance() { return false; }
  virtual int ExitInstance() { return 0; }
  virtual int Run() { return 0; }
};

CWinApp* AfxGetApp() { return g_app; }

int main()
{
  CWinApp* pApp = AfxGetApp();

  if (pApp->InitInstance())
    pApp->Run();

  pApp->ExitInstance();
}
#endif
//----------------------------------
// ���⼭���ʹ� ���̺귯�� ����� �ڵ�
// ��Ģ 1. CWinApp�� �Ļ� Ŭ������ ������ �մϴ�.
// ��Ģ 2. InitInstance() �����Լ��� �������ؼ� �ʱ�ȭ �۾��� �����մϴ�.
// ��Ģ 3. ����ڰ� ���� Ŭ������ ���������� �ݵ�� �Ѱ� �����ؾ� �մϴ�.

// �̸� ���ǵ� �帧 - "template method" ������ ����Ǵ� ��찡 ����.
//                => ��ü���� �帧�� ���̺귯�� �ȿ� �ΰ�, �� �ܰ踦 �����Լ�ȭ�ؼ�
//                   �ڽ��� �������� �� �ֵ���

// Qt  - C++
// GTK - C (��ü ���� C)

#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
  virtual BOOL InitInstance()
  {
    AfxMessageBox(L"���α׷� ����");
    return false;
  }

  virtual int ExitInstance()
  {
    AfxMessageBox(L"���α׷� ����");
    return 0;
  }
};

CMyApp theApp;