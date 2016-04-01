// 9_�긴�� - ������(pImpl idiom)
//  �߿��մϴ�. (http://yesarang.tistory.com/316 ����)
#include <iostream>
using namespace std;

// �긴�� ���� - pImpl idiom(Pointer To Implementation)
//             - Qt(KDE): d pointer - d_ptr(...)
// : �����ο� �������̽��� �и��ؼ� ��ȣ �������� ������
//   �����ϵ��� �Ѵ�.

// ���������� ����� ����Ǿ�� �Ѵٸ�, �긴���� ��������.
// - �������̽��� ȿ���� ������ ���·�, ������ ���� ��� Ŭ������
//   ������ �ذ� �����ϴ�.




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
// - �����Ϸ� ��ȭ��

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

// pImpl idiom - ��� ���Ͽ� ���� �������� ������ �� �����Ƿ�, ������ �ð���
//               ������ �� �ִ�.
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


