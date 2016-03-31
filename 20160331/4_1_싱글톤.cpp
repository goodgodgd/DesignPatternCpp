
#include <iostream>
using namespace std;

// 개념: 오직 한개의 객체를 만들 수 있고 어디에서도 동일한 방법으로 객체를 얻을 수 잇게 하는 패턴
// 전역변수를 객체로 캡슐화 한 것
// 전역 객체를 사용하면 안되는 이유
// A.cpp: Cursor c; B.cpp: extern Cursor c;
// 컴파일은 파일단위로 하는데 선언이 여러곳에 있으면 객체가 생성되는 순서가 C++ 표준에 정의되어 있지 않다.
// 파괴도 어디서 일어날지 몰라. 즉 생성과 소멸 시점이 명확하지 않다. -> 생성과 소멸을 명확화 할 수 있는 싱글톤 패턴

// Cursor c;
// 생성과 소멸의 시점이 명확하게 정의되어 있지 않다.

// Effective C++ 의 저자인 스캇 마이어스에 의해 유명해졌기 때문에 
// - 마이어스의 싱글톤 이라고도 불린다.

class Cursor
{
private:
	Cursor() {}		// 규칙 1. private 생성자
					// 밖에서 객체를 생성할 수 없다.
	// 규칙 3. 복사와 대입 금지
	// 선언만 한다. 구현이 없다!
	// 복사와 관련되 것을 private으로 선언: 밖에서 복사 못해
	// 혹시 내부에서 실수로 복사할수도 있으니 구현을 없애 버리자.
	// 그런데 이렇게 만들면 내부에서 복사를 시도했을 때 컴파일은 되는데 링킹 에러 발생!! 
	// 근데 어디서 에러나는지 에러메시지 없어, 기계어로 바뀐 다음 에러나기 때문에
//	Cursor(const Cursor&);
//	void operator=(const Cursor&);

	// 위의 복사 금지 기법은 C++11에서 문법화 되었습니다.
	// "delete function" 이라는 문법
	// 이제 내부에서 생성하면 링크에러가 아닌 컴파일 에러가 난다!! -> 오류를 찾을 수 잇다!!
	Cursor(const Cursor&) = delete;
	void operator=(const Cursor&) = delete;

public:
	// 규칙 2. 오직 한 개만 만드는 정적 멤버 함수, 보편적으로 쓰이는 이름 getInstance
	static Cursor& getInstance()
	{
		// 생성: getInstance()가 처음 불릴 때
		// 파괴: Cursor가 더 이상 사용되지 않는것이 명확해질 때
		static Cursor instance;

		// 컴파일은 되는데 링킹 에러 발생!!
		// delete function을 이용해 컴파일 에러로 변환
//		Cursor s = instance;

		return instance;
	}
};

int main()
{
	Cursor& c1 = Cursor::getInstance();
	// 레퍼런스를 빼먹어도 컴파일 잘된다.
	// C++의 복사생성자에 의해 의도하지 않게 새로운 객체가 만들어질 수 있다.
//	Cursor c2 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}

// 여전히 남은 문제
// 멀티스레드에서 동시에 생성할 수 있다. Thread Safety 보장 없음
// C++이 원래 멀티스레드 안정성 보장 안해
// 해법: 멀티스레드 시작되기 전에 main() 시작하자마자 getInstance() 부터 실행하자.
// C++11 에서부터는 정적 객체의 초기화에 대해 thread safety 보장된다. 컴파일러를 업그레이드 하자!
// gcc에서는 컴파일 옵션 -fthreadsafe-static 을 통해 안정성 보장
// gcc 4.5 이상에서는 디폴트 옵션됨. 그냥 쓰면 돼
// Java 1.5 이상
// static final Cursor instance = new Cursor();
// Java 문제: 초기화가 끝날 때까지 윈도우가 뜨지 않는다.
// -> lazy initialization
// 하이젠버그: 하이젠베르크의 불확정성 원리 - 현상을 관찰하는 행위가 현상을 바꾼다.
// 멀티스레드의 문제를 디버깅하려고 보면 문제가 안 생긴다. 재현이 어렵다.