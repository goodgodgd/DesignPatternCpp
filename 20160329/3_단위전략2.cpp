// 1cEbJ
#include <iostream>
using namespace std;

// 단위 전략(Policy-based) Design - "Modern C++ design"
// => 정책을 담은 코드를 컴파일 시간에 생성해 내는 기술
// => C++ 표준 라이브러리의 핵심 디자인 기법
//		단위 전략에서는 명세가 인터페이스로 정의되지 않고 내부적인 "문서"로 정리하여 관리한다.

// java, C#에서 기능을 확장하려면 인터페이스를 상속하면 되는데 "C++표준 라이브러리를 확장해서 사용하기" 위해서는 단위전략을 이해해야 한다.
// "Modern C++ design" 저자 - C++ 표준위원, Template의 천재, 이후 C++의 디자인이 바뀌었다. 현재 Facebook의 라이브러리 구현 folly, C++17에도 반영
// folly: 문자열 다루는데 좋아 (unicode), vector 재설계

// 장점: 가상함수가 아닌 인라인 함수이다. 호출에 따른 성능 저하가 없다.
// 단점: 정책 클래스가 함수가 아닌 템플릿 인자로 전달되므로, 실행 시에 정책을 교체하는 것이 불가능하다.
//		=> 컴파일 할 때 정책이 결정된다!!

// 상속을 사용한 단위 전략
template <typename T, typename ThreadModel>
class List : public ThreadModel
{
public:
	void push_front(const T& a)
	{
		// 상속 받은 lock, unlock
		lock();
		//...
		unlock();
	}
};

class MultiThread
{
public:
	void lock() { cout << "mutex lock" << endl; }
	void unlock() { cout << "mutex unlock" << endl; }
};

class SingleThread
{
public:
	// inline으로 만들면 내부가 비었으므로 lock(); unlock(); 줄을 컴파일러가 지워버린다.
	// 싱글 스레드와 동일한 성능!!
	inline void lock() {}
	inline void unlock() {}
};

// 멀티 스레드라는 "타입"이 넘어간다.

List<int, MultiThread> st;

int main()
{
	st.push_front(10);
}
