// 9_�긴��
//  �߿��մϴ�.
#include <iostream>
using namespace std;

struct IMP3
{
  virtual void play() = 0;
  virtual void stop() = 0;

  // virtual void playOneMinute() = 0;
  // �������̽��� ������ ��� �������̽��� ������ ��� ���� Ŭ������
  // ������ ������ �߻��Ѵ�.


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