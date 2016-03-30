// 1_메세지맵
// MFC, wsWidget 등에서 많이 쓰이고 잇다.
// : 가상 함수 테이블의 오버헤드를 줄이기 위해 사용자가 직접 테이블을 생성하도록 만드는 기술입니다.
//	메시지 맵은 문법적으로 복잡하다. 사용자가 편하게 쓰려면 코드를 만들어주자
//	-> 복잡한 코드를 매크로로 제공합니다.
//		매크로는 컴파일러 전에 전처리로 코드 만들어

#include "ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

class Window;

struct AFX_MSG
{
	int message;				// 메세지 번호
	void(Window::*handler)();	// 처리할 함수의 주소
};

class Window
{
	static map<int, Window*> this_map;
public:

	// 이제 모든 자식 클래스는 자신이 처리하고자 하는 이벤트와 이벤트 핸들러를 리턴해야 한다.
	virtual AFX_MSG* GetMessageMap() { return 0; }	// 일단 부모는 처리할 이벤트가 없다고 리턴 0

	void create()
	{
		// 윈도우 이벤트 핸들러 등록
		int handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	// 이번 예제의 핵심은 아래 함수입니다. - 이벤트 처리기
	static int foo(int handle, int msg, int param1, int param2)
	{
		Window* self = this_map[handle];

		if (self == 0) return 0;

		// 1. 배열을 얻어온다.
		AFX_MSG* msgArray = self->GetMessageMap();
		if (msgArray == 0)	// 처리할 메시지가 없는 경우
			return 0;

		// 2. 배열에 현재 메세지가 있는지 여부를 확인하고 등록된 핸들러를 호출한다.
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
		// MyWindow::onLButtonDown 을 쓰면 자신의 함수 포인터가 아니기 때문에 쓸수 없다.
		typedef void(Window::*HANDLER)();
		// 여기에 필요한 이벤트들만 연결시켜주면 된다. 모든 이벤트에 대한 가상함수 만들지 않아도 된다.
		// 매번 똑같은 msgMap을 만들지 않기 위해 static 선언
		static AFX_MSG msgMap[] = {
			{ WM_LBUTTONDOWN, static_cast<HANDLER>(&MyWindow::onLButtonDown) },
			{ WM_KEYDOWN, static_cast<HANDLER>(&MyWindow::onKeyDown) },
			{ 0, 0 }
		};
		// 0,0 으로 배열의 끝 표시
		return msgMap;
	}
};
#endif

//----------
// GetMessageMap()을 생성하는 매크로입니다.
// 위의 MyWindow 를 매크로로 구현

// 헤더에서 GetMessageMap() 함수선언
#define DECLARE_MESSAGE_MAP()                   \
  virtual AFX_MSG* GetMessageMap();

// 소스에서 함수 시작부와 배열 선언
#define BEGIN_MESSAGE_MAP(classname)           \
  AFX_MSG* classname::GetMessageMap()           \
  {                                             \
    typedef void(Window::*HANDLER)();           \
    static AFX_MSG msgMap[] = {

// 배열에 메시지와 함수 포인터 쌍 추가
#define ADD_MAP(message, handler)               \
  { message, static_cast<HANDLER>(handler) },

// 배열 종료 표시 및 함수 종료
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
	w.create();       // 이 순간 윈도우가 만들어져야 합니다.
	// 왼쪽 버튼을 누르면 "LBUTTON" 이라고 출력되어야 합니다.
	IoProcessMessage();
}
