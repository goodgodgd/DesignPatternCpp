// C++�� �����ӿ�ũ���� ����ϴ� ����

// ���̺귯��: ���α׷� ���߿� �ʿ��� ������ �����ϴ� �� (Ư�� ������)
//				(class, function)
//				���� ������ ����
// �����ӿ�ũ: ���� + �̸� ���ǵ� ���� �帧 (e.g. main���� ����)
//				���� ��뿡 ���� �帧�� �����ؾ� �Ѵ�.
//				MFC ���� ��� main�� ����. ���ǵ� �帧�� ���� ����ؾ�

// MFC ��Ÿ�� �����ӿ�ũ ����

// ##### �ڵ��帧 #####
// 1. ���� ��ü�� ���� theApp
// 2. �θ�Ŭ���� ������ ȣ��
// 3. ������ü g_app�� ��ü ��
// 4. main���� pApp �޼ҵ� �����
// 5. �ڽ��� �������̵� �� CMyApp�� �޼ҵ� ����

#include <iostream>
using namespace std;

//--------------------------------------------
// ���⼭���ʹ� ���̺귯�� ���� �ڵ��Դϴ�. dll�� ������ �ֽ��ϴ�.
class CWinApp;
CWinApp* g_app;

class CWinApp
{
public:
	CWinApp() { g_app = this;  }
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

//--------------------------------------------
// ���⼭���ʹ� ���̺귯�� ����� �ڵ�
// ��Ģ 1. CWinApp�� �Ļ� �÷����� ������ �մϴ�.
// ��Ģ 2. InitINstance() �����Լ��� �������ؼ� �ʱ�ȭ �۾��� �����ؾ� �մϴ�.
// ��Ģ 3. ����ڰ� ���� Ŭ������ ���������� �ݵ�� �� �� �����ؾ� �մϴ�.

// �̸� ���ǵ� �帧 - "template method" ������ ����Ǵ� ��찡 ����.
//					=> ��ü���� �帧�� ���̺귯�� �ȿ� �ΰ�, �� �ܰ踦 �����Լ�ȭ�ؼ� �ڽ��� ������ �� �� �ֵ���

// GUI
// ������:	C# �� ����� ���� ����
// ������:	Qt - C++
//			GTK - C (��ü���� C - ��Ʈ����!!)
// Qt�� ũ�ν� �÷����̶�� ������ ������������ �ߵǰ� �����쿡���� ������ �ִ�.
// ũ�ν� �÷����� "ȯ��"�̴�. - �÷��� ����Ƽ�� �� ���� ���� ���� ���۷����� ����.
// xamarin: C#�� �ڹ�ó�� ũ�ν� �÷������� ������� (MS�� �ȸ�)


class CMyApp : public CWinApp
{
public:
	virtual bool InitInstance()
	{
		cout << "���α׷� ����" << endl;
		return false;
	}

	virtual int ExitInstance()
	{
		cout << "���α׷� ����" << endl;
		return 0;
	}
};

// ���� ��ü�� ���� theApp -> �θ�Ŭ���� ������ ȣ�� -> ������ü g_app�� ��ü �� -> main���� pApp �޼ҵ� ����� -> �ڽ��� �������̵� �� CMyApp�� �޼ҵ� ����
CMyApp theApp;
