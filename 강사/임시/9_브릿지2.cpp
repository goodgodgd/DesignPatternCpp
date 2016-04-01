// 9_브릿지 - 김윤수(pImpl idiom)
//  중요합니다. (http://yesarang.tistory.com/316 참고)
#include <iostream>
using namespace std;

// 브릿지 패턴 - pImpl idiom(Pointer To Implementation)
//             - Qt(KDE): d pointer - d_ptr(...)
// : 구현부와 인터페이스를 분리해서 상호 독립적인 변경이
//   가능하도록 한다.

// 지속적으로 기능이 변경되어야 한다면, 브릿지를 도입하자.
// - 인터페이스의 효과를 누리는 형태로, 깨지기 쉬운 기반 클래스의
//   문제를 해결 가능하다.




struct IMP3
{
  virtual void play() = 0;
  virtual void stop() = 0;
  virtual ~IMP3() {}
};

class iPod
{
public:
  void play() { cout << "play music with iPod" << endl; }
  void stop() { cout << "stop music" << endl; }
};

class MP3
{
  IMP3* pImpl;
public:
  MP3(IMP3* p = 0) : pImpl(p)
  {
    if (pImpl == 0)
      pImpl = new iPod;
  }

  void play() { pImpl->play(); }
  void stop() { pImpl->stop(); }

  void playOneMinute()
  {
    pImpl->play();
    //...
    pImpl->stop();
  }
  

};


class Person
{
public:
  void playMusic(MP3* mp3) { mp3->playOneMinute(); }
};

int main()
{
  Person person; iPod pod;
  person.playMusic(&pod);
}

// C++ pImpl Idiom
// - 컴파일러 방화벽

#if 1
// Point.h
class Point
{
public:
  Point();
  void foo();

private:
  int x;
  int y;
  int z;
};

// Point.cpp
#include "Point.h"
Point::Point() {}
Point::foo() {}

// main.cpp
#include "Point.h"
int main()
{
  Point p;
}
#endif

// pImpl idiom - 헤더 파일에 대한 의존성을 제거할 수 있으므로, 컴파일 시간을
//               단축할 수 있다.
// Point.h
class Point
{
public:
  Point();
  void foo();

private:
  PointImpl* pImpl;
};

// Point.cpp
#include "PointImpl.h"

Point::Point()
{ pImpl = new PointImpl;}

void Point::foo()
{ pImpl->foo(); }

// PointImpl.h
class PointImpl
{
public:
  void foo();

private:
  int x;
  int y;
  int z;
};

// PointImpl.cpp
#include "PointImpl.h"

void PointImpl::foo()
{ }

// main.cpp
#include "Point.h"

int main()
{
  Point p;
  p.foo();
}


