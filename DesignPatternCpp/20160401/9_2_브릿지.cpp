// 9_브릿지
// 중요합니다.

// 브릿지 패턴	- pImpl idiom (Pointer To Implementation)
//				- Qt(KDE): d pointer, d_ptr(...)
// - 구현부와 인터페이스를 분리해서 상호 독립적인 변경이 가능하도록 한다.

// 지속적으로 기능이 변경되어야 한다면, 브릿지를 도입하자.
// - 인터페이스의 효과를 누리는 형태로, 깨지기 쉬운 기반 클래스의 문제를 해결 가능하다.

#include <iostream>
using namespace std;

// 인터페이스에는 playOneMinute()이 없다.
struct IMP3
{
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual ~IMP3() {}
	//virtual void playOneMinute() = 0;
};

// 만약 여기에 playOneMinute()을 추가하면 인터페이스에 없기 때문에 Person에서 사용 못함
// Person에서 iPod을 직접 사용하면 강한 결합되어 교체 불가
class iPod : public IMP3
{
public:
	void play() { cout << "play music with ipod" << endl; }
	void stop() { cout << "stop music with ipod" << endl; }
};

// 기능을 마음대로 추가할 수 있는 중간층을 도입하자.
class MP3
{
	IMP3* pImpl;
public:
	//
	MP3(IMP3* p = 0) : pImpl(p)
	{
		if (p = nullptr)
			pImpl = new iPod;		// 기본 구현
	}
	void play() { pImpl->play(); }
	void stop() { pImpl->stop(); }

	// 인터페이스 건드리지 않고 기능 추가 가능하다.
	void playOneMinute()
	{
		pImpl->play();
		//...
		pImpl->stop();
	}
};

// IMP3가 아닌 중간층 클래스인 MP3를 사용하자.
class Person
{
public:
	void playMusic(MP3* mp3) { mp3->play(); }
	void playOneMinute(MP3* mp3) { mp3->playOneMinute(); }
};

int main()
{
	Person person;
	iPod ipod;
	MP3 mp3(&ipod);			// 여기서 기능 추가
	person.playMusic(&mp3);
	person.playOneMinute(&mp3);
}

// C++ pImpl Idiom
// - 컴파일러 방화벽

#if 0
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

#if 0
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
{
	pImpl = new PointImpl;
}

void Point::foo()
{
	pImpl->foo();
}

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
#endif

// Point 구현부가 바뀌었을 때 Point를 사용하는 모든 소스가 재컴파일되어야 한다.
// PointImpl 을 사용하면 PointImpl.h를 쓰는 구현부만 컴파일 한다.
// 헤더 파일에 구현 내용이 없기 때문에 사용자에게 구현을 감출 수 있다.

// 참고자료: http://yesarang.tistory.com/316
