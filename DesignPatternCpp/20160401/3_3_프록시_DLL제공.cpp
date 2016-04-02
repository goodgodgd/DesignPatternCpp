// 프록시의 구현체를 제공하기 보다는 인터페이스를 제공하자
// 서버쪽 구현이 달라져도 클라이언트 모듈이 다시 컴파일될 필요 없이 DLL만 바꾸면 되게 하자.
// 이제 서버 개발자에게 2개의 파일을 받아야 합니다.
// 1. ICalc.h : 인터페이스 헤더 - 변하지 않는 것
// 2. CalcProxy.dll: Proxy Class 가 있는 DLL - 변하는 구현부

// 서버 제작자에게서 ICalc.h와 CalcProxy.dll을 받아야 합니다.
// ICalc 라는 인터페이스를 통해 서버 기능을 간편하게 쓰자.

// 이것을 실행하기 전 계산기 서버를 실행해야 합니다.

#include <iostream>
#include "ICalc.h"
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

// 인터페이스 ICalc 적용
#if 0
int main()
{
	// 1. CalcProxy.dll을 로드 합니다.
	void* addr = IoLoadModule("CalcProxy.dll");

	// 2. 객체를 생성하는 함수를 찾아야 합니다.
	typedef ICalc*(*F)();	// 멤버 함수 포인터
	F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

	// 3. Calc 객체 생성
	ICalc* pCalc = f();

	// 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
#endif	// 문제: 프록시 객체 생성이 복잡하다.

// 프록시 객체 생성 CreateInstance()라는 함수 안으로 캡슐화
#if 0
int main()
{
	// 3. Calc 객체 생성
	ICalc* pCalc = CreateInstance();

	// 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;

	// 문제: CreateCalc 에서 new를 쓰기 때문에 메모리 누수 발생 -> 파괴 필요
	delete pCalc;	// 절대 하면 안됩니다.

	// 왜 안되나?
	// 내부적인 new, delete 구현이 컴파일러 버전에 따라 다르기 때문에
	// new가 들어있는 라이브러리 내부와 밖에서 쓰는 delete의 버전이 달라질 수 있다.
	// 라이브러리 내부에서 자동으로 파괴를 시켜줘야 한다.
	// 해답: 객체의 수명을 참조계수 기반으로 관리해야 한다.
}
#endif	// 문제: 생성된 객체의 메모리를 해지할 수 없다.

// 스마트 포인터로 프록시 객체 생성
// CalcProxy.cpp: Calc라는 구체 클래스 구현 -> CalcProxy.dll
// ICalc.h: 인터페이스 및 dll불러와 객체 생성하는 CreateInstance() 제공
int main()
{
	// 참조 계수 기반 Calc 객체 생성
	// sp<> - 모듈의 수명을 관리하기 위해서 입니다.
	Ptr<ICalc> pCalc = CreateInstance();

	// 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
