// C++의 프레임워크들이 사용하는 개념

// 라이브러리: 프로그램 개발에 필요한 도구를 제공하는 것 (특정 도메인)
//				(class, function)
//				도구 사용법은 자유
// 프레임워크: 도구 + 미리 정의된 실행 흐름 (e.g. main부터 실행)
//				도구 사용에 대한 흐름을 이해해야 한다.
//				MFC 같은 경우 main이 없다. 정의된 흐름에 따라 사용해야

// MFC 스타일 프레임워크 예시

// ##### 코드흐름 #####
// 1. 전역 객체를 선언 theApp
// 2. 부모클래스 생성자 호출
// 3. 전역객체 g_app에 객체 들어감
// 4. main에서 pApp 메소드 실행됨
// 5. 자식이 오버라이딩 한 CMyApp의 메소드 실행

#include <iostream>
using namespace std;

//--------------------------------------------
// 여기서부터는 라이브러리 내부 코드입니다. dll로 숨겨져 있습니다.
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
// 여기서부터는 라이브러리 사용자 코드
// 규칙 1. CWinApp의 파생 플래스를 만들어야 합니다.
// 규칙 2. InitINstance() 가상함수를 재정의해서 초기화 작업을 수행해야 합니다.
// 규칙 3. 사용자가 만든 클래스를 전역적으로 반드시 한 개 생성해야 합니다.

// 미리 정의된 흐름 - "template method" 패턴이 적용되는 경우가 많다.
//					=> 전체적인 흐름을 라이브러리 안에 두고, 각 단계를 가상함수화해서 자식이 재정의 할 수 있도록

// GUI
// 윈도우:	C# 젤 만들기 쉽고 빨라
// 리눅스:	Qt - C++
//			GTK - C (객체지향 C - 스트레스!!)
// Qt가 크로스 플랫폼이라고 했지만 리눅스에서만 잘되고 윈도우에서는 문제가 있다.
// 크로스 플랫폼은 "환상"이다. - 플랫폼 네이티브 언어가 가장 성능 좋고 레퍼런스도 많다.
// xamarin: C#을 자바처럼 크로스 플랫폼으로 만들어줌 (MS에 팔림)


class CMyApp : public CWinApp
{
public:
	virtual bool InitInstance()
	{
		cout << "프로그램 시작" << endl;
		return false;
	}

	virtual int ExitInstance()
	{
		cout << "프로그램 종료" << endl;
		return 0;
	}
};

// 전역 객체를 선언 theApp -> 부모클래스 생성자 호출 -> 전역객체 g_app에 객체 들어감 -> main에서 pApp 메소드 실행됨 -> 자식이 오버라이딩 한 CMyApp의 메소드 실행
CMyApp theApp;
