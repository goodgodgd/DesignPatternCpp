#include <iostream>
using namespace std;
// http://d.pr/n/19aU4

class Sample
{
	int data;
public:
	void f1()	// f1(Sample* this = 0) 인데 메모리 접근이 없기 때문에 동작 가능
	{ cout << "f1" << endl;	}
	int f2()
	{ cout << "f2" << endl; return 0; }
	int f3()
	{
		cout << "f3" << endl; 
		return data;	// this->data 가 되므로 error!
	}

	// MFC, Android 에서도 사용하는 코드
	// C++ idom: 언어의 특성 이용 - 오픈소스 이해에 필요
	// 이 idiom은 C++ 표준에서 의도한 것이 아니므로 (undefined) 컴파일러에 따라 동작이 달라질 수 있다.
	// Android에서도 최신 버전에서는 없어짐
	// 최신버전에서는 static function(Sample* ptr) 형태로 명시적으로 구현함
	// MFC에서도 사라짐, 이제는 쓰면 
	// clang이 메인 스트림 컴파일러가 되었음, 주요 프로젝트의 기본 컴파일러로 사용되고 있음. webkit, chromium
	// LLVM에서는 바로 binary를 만들지 않고 intermediate language를 만들고 그 다음 binary 만든다.
	// 그래서 에러 메시지를 보기가 쉽다.
	// 기존 문제는 LLVM clang으로 만든 binary가 성능이 안 좋아졌는데 최근엔 성능 문제가 해결됨
	// 리눅스에서 C++ 코드를 개발한다면 clang을 쓰자!!
	int call_f3()
	{
		return this ? f3() : NULL;	// this==NULL 일 경우 예외처리
	}
};

int main()
{
	Sample* p = 0;	// new 메모리 할당을 하다가 실패해서 0이 나왔다고 가정
	p->f1();			// f1(p) nullptr 인데도 동작 가능
	p->f2();			// f2(p)
//	p->f3();			// error!
	cout << p->call_f3() << endl;			// 예외처리
}
