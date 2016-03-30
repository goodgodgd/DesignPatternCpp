// 타이머를 캡슐화 해봅시다.
// C언어 함수를 클래스로 래핑하는 패턴은 thread와 비슷
// static 멤버 함수 포인터와 

// http://d.pr/n/ZBH
// http://d.pr/n/191Lz

// ioacademy.h
// http://d.pr/n/17nrr

#include <string>
#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;


#if 0	// 일반 함수 타이머 호출
void foo(int id)
{
	cout << "foo: " << id << endl;
}

int main()
{
	// 이렇게 되면 타이머가 계속 돌지 않고 바로 종료, 타이머가 돌기 위해서 메시지 루프가 돌아야 함
	int n1 = IoSetTimer(1000, foo);
	int n2 = IoSetTimer(500, foo);
	// 메시지 루프가 실행 됨
	IoProcessMessage();
}
#endif

#include <map>
class Clock;	// 전방 선언 - 완전한 선언이 없어도 포인터는 사용 가능
// 클래스 밖에 있어 하나로 관리 안됨. -> 클래스 static 멤버 변수
//map<int, Clock*> this_map;

class Clock
{
	string name;
public:
	Clock(string s) : name(s) {}
	// static 함수에서 불러오기 위해 static 선언 -> 외부 선언 필요
	static map<int, Clock*> this_map;

	void start(int ms)
	{	
		// C언어 함수이기 때문에 일반 멤버 함수 전달 안됨, static 멤버 함수 받아야
//		IoSetTimer(ms, timerHandler);

		int id = IoSetTimer(ms, timerHandler);
		this_map[id] = this;
	}

	// static 이어야 IoSetTimer로 전달가능
	// 그런데 또 static 에서는 멤버 변수 접근 불가, 멤버 함수 접근 불가
	// 전달할 수 있는 것은 오직 id 뿐
	// 어떻게 id를 통해서 this 포인터를 전달할까? => key-value 가진 map 사용
	static void timerHandler(int id)
	{
		Clock* self = this_map[id]; 
		cout << self->name << endl;
	}
};

// static 멤버 변수는 외부 정의를 해야 합니다. (소스파일)
map<int, Clock*> Clock::this_map;

int main()
{
	Clock c1("AAA");
	Clock c2("\tBBB");
	
	c1.start(1000);	// 1초에 한번씩 이름을 출력
	c2.start(500);

	IoProcessMessage();
}


