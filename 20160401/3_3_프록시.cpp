// 서버 제작자에게서 ICalc.h와 CalcProxy.dll을 받아야 합니다.
// ICalc 라는 인터페이스를 통해 서버 기능을 간편하게 쓰자.

#include <iostream>
#include "ICalc.h"
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

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
#endif

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
#endif

int main()
{
	// 참조 계수 기반 Calc 객체 생성
	// sp<> - 모듈의 수명을 관리하기 위해서 입니다.
	Ptr<ICalc> pCalc = CreateInstance();

	// 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
	cout << pCalc->add(10, 20) << endl;
	cout << pCalc->sub(10, 20) << endl;
}
