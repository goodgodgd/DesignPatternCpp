// 9_�긴��
// �߿��մϴ�.

// ���ݱ��� ���Ͽ��� ���� �߿��� ����: �������̽�
// �׷��� �������̽��� �ᱹ ���Ѵ�. �װͿ� �����ϴ� ���� �긴��

#include <iostream>
using namespace std;

// �������̽� �� ���ԵƳ�?
// �� Ŭ������ ���� ���ն���
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
	// �������̽��� ������ ��� �������̽��� ������ ��� ���� Ŭ������ ������ ������ �߻��Ѵ�.
	// �߰����� ����������. -> �긴��
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
	// ����߰��Ϸ��� �������̽� ���� -> �ڽĵ��� �� ������!!
	//void playOneMinute(IMP3* mp3) { mp3->playOneMinute(); }
};

int main()
{
	Person person;
	iPod ipod;
	person.playMusic(&ipod);
}

