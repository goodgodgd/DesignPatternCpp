// MS 라이브리러 중 WTL, ATL가 아래와 같이 설계 되어 있습니다. (window / active template library)
// 가상함수를 만들지 않고

// CRTP: Curiously Recurring Template Pattern - C++ idioms
// 가장 많이 쓰이는 idom
// : 부모 클래스가 템플릿인데 자식에서 템플릿의 인자로 자신의 타입을 전달하는 기술

// 예전 이름은 mixin template
// 참고: 이디엄 정리된 싸이트 https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
// C++ 특징: 코드를 보고 의도를 파악하기 어렵다.

// 여러가지 활용이 가능한다, 아래 코드는 비가상함수를 가상함수처럼 동작하게 만드는 기법.
// onClick()이 가상함수가 아닌데 가상함수처럼 사용된다. -> 가상함수 테이블이 필요없다.
// 템플릿을 쓰기 때문에 런타임에 이벤트 처리기가 실행시간에 사용할 필요가 없다면 좋은 방법
// inline도 적용가능

#include <iostream>
using namespace std;

#if 0
class Window
{
public:
	void msgLoop()
	{
		onClick();
	}

	void onClick()	{ cout << "Window on Click" << endl; }
};

//class MyWindow : public Window
class MyWindow : public Window
{
public:
	void onClick()
	{
		cout << "My Window on Click" << endl;
	}
};

int main()
{
	MyWindow w;
	// 이렇게 쓰면 부모 윈도우의 메시지만 처리하게 되서 Window::onClick 이 실행된다.
	// 내가 원하는 것은 MyWindow::onClick
	w.msgLoop();
}
#endif

// 템플릿으로 자식 클래스 타입 받아옴
template <typename T>
class Window
{
public:
	void msgLoop()
	{
//		onClick();
// 이것은 다음과 같다. 그래서 Window::onClick()
//		this->onClick();
// 그런데 MyWindow의 것을 호출하고 싶다면
//		static_cast<MyWindow*>(this)->onClick();

		// 이렇게 강한 결합을 하지 않고 템플릿으로 유연하게 호출할 수 있다.
		static_cast<T*>(this)->onClick();
	}

	void onClick()	{ cout << "Window on Click" << endl; }
};

class MyWindow : public Window<MyWindow>
{
public:
	void onClick()
	{
		cout << "My Window on Click" << endl;
	}
};

int main()
{
	MyWindow w;
	// 이제는 MyWindow::onClick 이 실행된다.
	w.msgLoop();
}
