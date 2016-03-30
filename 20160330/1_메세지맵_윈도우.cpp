// 1_메세지맵
// MFC, wsWidget 등에서 많이 쓰이고 잇다.
// : 가상 함수 테이블의 오버헤드를 줄이기 위해 사용자가 직접 테이블을 생성하도록 만드는 기술입니다.
//		-> 만들어야 할 가상 함수가 적다면 가상 함수를 쓰는 것이 낫다.

#include "ioacademy.h"
using namespace ioacademy;

// 가상함수를 쓰면 가상함수의 개수만큼 가상함수 포인터가 생긴다.
// 윈도우에서 쓰는 메시지 종류가 천개가 넘어, 모두 가상함수로 만들면 윈도우 하나 당 8k 이상의 메모리 소모
// 가상함수의 비용을 줄이기 위해 "메시지맵"을 구현했다.
// 메시지 맵은 문법적으로 복잡하다. 사용자가 편하게 쓰려면 코드를 만들어주자->매크로 사용

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
	virtual AFX_MSG* GetMessageMap() { return 0; }
	void create()
	{
		// 윈도우 이벤트 핸들러 등록하고 handle (클래스 ID) 받음
		int handle = IoMakeWindow(foo);
		// static foo에 this를 전달하기 위해 (handle, this) 쌍을 static map에 등록
		this_map[handle] = this;
	}
	// 이번 예제의 핵심은 아래 함수입니다. - 이벤트 처리기
	static int foo(int handle, int msg, int param1, int param2)
	{
		// handle: 이벤트 발생한 클래스 번호, msg: 이벤트 번호 (WM_KEYDOWN 등)
		// map 통해 this 얻어옴
		Window* self = this_map[handle];
		if (self == 0) return 0;
		
		// 1. 배열을 얻어온다. (자식에서 배열 정의)
		AFX_MSG* msgArray = self->GetMessageMap();
		if (msgArray == 0)	// 처리할 메시지가 없는 경우
			return 0;
		
		// 2. 배열에 현재 메세지가 있는지 여부를 확인하고 등록된 핸들러를 호출한다.
		// 자식에서 정의한 배열에서 현재 들어온 msg와 같은 것이 있는지 확인하고 연결된 함수를 self 통해 호출
		for (; msgArray->message != 0; msgArray++)	// 마지막은 0이라고 약속!
			if (msgArray->message == msg)
			{
				void(Window::*f)() = msgArray->handler;
				(self->*f)();
			}
		return 0;
	}
  	// 이제 필요하지 않아. 자식 클래스에서 원하는 함수로 매핑
	//  virtual void onLButtonDown() {}
	//  virtual void onKeyDown() {}
};

map<int, Window*> Window::this_map;

// Window에서 메시지맵 구현은 다 해놨고 여기선 이벤트 처리기(함수)와 Map만 만들면 돼.
class MyWindow : public Window
{
public:
  void onLButtonDown() { cout << "LButton" << endl; }
  void onKeyDown() { cout << "Key Down" << endl; }

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
		};	// {0,0} 으로 배열의 끝 표시
		return msgMap;
	}
};

int main()
{
  MyWindow w;
  w.create();       // 이 순간 윈도우가 만들어져야 합니다.
                    // 왼쪽 버튼을 누르면 "LBUTTON" 이라고 출력되어야 합니다.
  IoProcessMessage();
}
