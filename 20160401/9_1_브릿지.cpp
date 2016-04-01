// 9_브릿지
// 중요합니다.

// 지금까지 패턴에서 가장 중요한 문법: 인터페이스
// 그런데 인터페이스도 결국 변한다. 그것에 대응하는 것이 브릿지

#include <iostream>
using namespace std;

// 인터페이스 왜 도입됐나?
// 두 클래스의 강한 결합때문
#if 0
class iPod
{
public:
	void play() { cout << "play music with ipod" << endl; }
};

class Person
{
public:
	void playMusic(iPod* mp3) { mp3->play(); }
};

int main()
{
	Person person;
	iPod ipod;
	person.playMusic(&ipod);
}
#endif

struct IMP3
{
	virtual void play() = 0;
	//void stop() = 0;
	virtual ~IMP3() {}

	//virtual void playOneMinute() = 0;
	// 인터페이스를 변경할 경우 인터페이스를 구현한 모든 서브 클래스가 깨지는 문제가 발생한다.
	// 중간층을 삽입해주자. -> 브릿지
};
class iPod : public IMP3
{
public:
	void play() { cout << "play music with ipod" << endl; }
};

class Person
{
public:
	void playMusic(IMP3* mp3) { mp3->play(); }
	// 기능추가하려면 인터페이스 변경 -> 자식들이 다 깨진다!!
	//void playOneMinute(IMP3* mp3) { mp3->playOneMinute(); }
};

int main()
{
	Person person;
	iPod ipod;
	person.playMusic(&ipod);
}

