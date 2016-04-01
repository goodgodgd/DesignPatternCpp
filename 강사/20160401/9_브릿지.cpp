// 9_브릿지
//  중요합니다.
#include <iostream>
using namespace std;

struct IMP3
{
  virtual void play() = 0;
  virtual void stop() = 0;

  // virtual void playOneMinute() = 0;
  // 인터페이스를 변경할 경우 인터페이스를 구현한 모든 서브 클래스가
  // 깨지는 문제가 발생한다.


  virtual ~IMP3() {}
};

class iPod
{
public:
  void play() { cout << "play music with iPod" << endl; }
  void stop() { cout << "stop music" << endl; }
};

class Person
{
public:
  void playMusic(IMP3* mp3) { mp3->play(); }

  void playOneMinute(IMP3* mp3) 
  {}

};

int main()
{
  Person person; iPod pod;
  person.playMusic(&pod);
}