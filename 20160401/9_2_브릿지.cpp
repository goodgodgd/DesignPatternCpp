// 9_�긴��
// �߿��մϴ�.

// �긴�� ����	- pImpl idiom (Pointer To Implementation)
//				- Qt(KDE): d pointer, d_ptr(...)
// - �����ο� �������̽��� �и��ؼ� ��ȣ �������� ������ �����ϵ��� �Ѵ�.

// ���������� ����� ����Ǿ�� �Ѵٸ�, �긴���� ��������.
// - �������̽��� ȿ���� ������ ���·�, ������ ���� ��� Ŭ������ ������ �ذ� �����ϴ�.

#include <iostream>
using namespace std;

struct IMP3
{
	virtual void play() = 0;
	virtual void stop() = 0;
	//void stop() = 0;
	virtual ~IMP3() {}

	//virtual void playOneMinute() = 0;
};
class iPod : public IMP3
{
public:
	void play() { cout << "play music with ipod" << endl; }
	void stop() { cout << "stop music with ipod" << endl; }
};

class MP3
{
	IMP3* pImpl;
public:
	MP3(IMP3* p = 0) : pImpl(p)
	{
		if (p = nullptr)
			pImpl = new iPod;		// �⺻ ����
	}
	void play() { pImpl->play(); }
	void stop() { pImpl->stop(); }

	// �������̽� �ǵ帮�� �ʰ� ��� �߰� �����ϴ�.
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
	void playMusic(MP3* mp3) { mp3->play(); }
	// ����߰��Ϸ��� �������̽� ���� -> �ڽĵ��� �� ������!!
	void playOneMinute(MP3* mp3) { mp3->playOneMinute(); }
};

int main()
{
	Person person;
	iPod ipod;
	MP3 mp3(&ipod);			// ���⼭ ��� �߰�
	person.playMusic(&mp3);
	person.playOneMinute(&mp3);
}

// C++ pImpl Idiom
// - �����Ϸ� ��ȭ��

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

// Point �����ΰ� �ٲ���� �� Point�� ����ϴ� ��� �ҽ��� �������ϵǾ�� �Ѵ�.
// PointImpl �� ����ϸ� PointImpl.h�� ���� �����θ� ������ �Ѵ�.
// ��� ���Ͽ� ���� ������ ���� ������ ����ڿ��� ������ ���� �� �ִ�.

// �����ڷ�: http://yesarang.tistory.com/316
