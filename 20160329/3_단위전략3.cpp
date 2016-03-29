// eYbJ

#include <iostream>
#include <string>
using namespace std;

// Stephan T. Lavavej - STL 강의자료
// MS에서 일하면서 STL 구현자
// https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Introduction-to-STL-with-Stephan-T-Lavavej
// cppcon.org - C++ conference에 관한 모든 자료 공개
// 14년부터 C++ 컨퍼런스들이 통합,  MS에서 주도 - 유투브와 github 공개

// vector, list등의 STL은 동기화 정책이 없다.
// 동기화의 가장 좋은 방법은 lock이 필요없는 lock free container를 사용하는 것이 좋다.
// TBB: lock free container 제공, but 라이센스 이슈
// boost: 무료 사용 가능

// 요즘 가장 핫한 이슈: 객체 지향 -> Funtional Frame, C++에서 구현됨

// string 은 typedef다
// typedef basic_string<char, char_traits<char>, allocator<char> > string;
// char_traits: 문자열 비교기능
// allocator: 메모리 할당

class my_traits : public char_traits < char >
{
public:
	// document로 약속된 형식
	static bool compare(const char* a, const char* b, size_t sz)
	{
		return strcmpi(a, b);
	}
};

// 대소문자를 구별하지 않는 비교 연산자를 쓰고 싶다.
// 따로 string 전체를 구현하지 않아도 
typedef basic_string<char, my_traits> mystring;

int main()
{
	mystring s1 = "abcd";
	mystring s2 = "ABCD";

	if (s1 == s2)
		cout << "same" << endl;
	else
		cout << "not same" << endl;
}
