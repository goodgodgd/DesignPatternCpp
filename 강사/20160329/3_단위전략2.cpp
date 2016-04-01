#include <iostream>
using namespace std;
// 3_단위전략2

// Effective Java

// API Design on C++

// C++ - 스캇 마이어스
// Effective C++

// More Effective C++
// Modern Effective C++
// Effective STL

// 허브 셔터
// Exceptional C++
// More Exceptional C++
// Exceptional C++ Style

// 허브 셔터 & 안드레이 알렉산드르쿠
// C++ Coding Style

// Modern C++ Design




// 파일질라(FileZilla) - 192.168.2.234
//                    id: cpp
// ioacademy3_2G(5G)

// 단위 전략(Policy-based) Design - "Modern C++ design"
// => 정책을 담은 코드를 컴파일 시간에 생성해 내는 기술
// => C++ 표준 라이브러리의 핵심 디자인 기법

// 장점: 가상함수가 아닌 인라인 함수이다. 호출에 따른 성능 저하가 없다.
// 단점: 정책 클래스가 함수가 아닌 템플릿 인자로 전달되므로, 실행 시에 정책을
//      교체 하는 것이 불가능하다.
//     => 컴파일 할때 정책이 결정된다.!!!

// 상속을 사용한 단위 전략
template <typename T, typename ThreadModel = SingleThread>
class List : public ThreadModel
{
public:
  void push_front(const T& a)
  {
    lock();
    //...
    unlock();
  }
};

class SingleThread
{
public:
  inline void lock() {}
  inline void unlock() {}
};

// http://d.pr/n/1cEbJ
class MultiThread
{
public:
  void lock()   { cout << "mutex lock" << endl; }
  void unlock() { cout << "mutex unlock" << endl; }
};

List<int, MultiThread> st;

int main()
{

}
