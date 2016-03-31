#include "IObserver.h"

#include <iostream>
using namespace std;

class SampleGraph : public IObserver
{
public:
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Sample Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

// DLL 쓸때 구현 클래스 이름을 알아야 한다.
// 기존 클래스를 바꿀려면 컴파일을 다시 해야해
// 헤더에 있는 부모에 접근하면 기능추가 가능

// 반드시 동적 모듈 안에서 객체를 생성하는 방법을 제공해주어야 합니다. - 핵심!!
// - SampleGraph 라는 이름은 현재 DLL을 만드는 사람만 알고 있습니다.
// - 프로그램 내부에서는 절대 이름을 사용하면 안됩니다.
// Table 클래스가 SampleGraph에 의존하면 (강한 결합), SampleGraph가 변하면 Table도 새로 컴파일
// Table이 IObserver에 접근해야 한다.
// 모듈과 모듈사이의 느슨한 결합도 중요
// 그런데 IObserver 객체를 생성할 순 없다. 구체 클래스를 생성해야..


// 반드시 DLL 내부에서 자신이 만든 클래스의 객체를 생성해주어야 합니다.
// - 함수를 하나를 약속합니다.
// 내부에서 구체 클래스 생성하고 인터페이스를 통해 받아오자!

extern "C"					// C 스타일로 짜라, 함수 오버로딩 쓰지마라.
__declspec(dllexport)		// 윈두우에서 DLL 내부 심볼을 공개하는 방법
IObserver* CreateGraph()
{
	return new SampleGraph;
}

// C++에서는 함수 오버로딩 가능 C언어 불가능
// 내부적으로 다른 이름 만들어
//void foo() {}			// foo
//void foo(double) {}		// foo@int
//void foo(int, int) {}	// foo@int@int

// developer command prompt: cl 명령 == gcc
// cl SampleGraph.cpp /LD
// /LD : DLL로 만들라는 옵션