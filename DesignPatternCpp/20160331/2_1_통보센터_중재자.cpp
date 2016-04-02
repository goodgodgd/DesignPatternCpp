// 통보센터 (Notification Center)

// 핸드폰에서 "알림" 기능을 사용할 때 관찰자가 유용하다.
// 그런데 이걸 다 관찰자로 만들면 클래스들 간의 관계도 많고 객체도 너무 많아진다. -> 코드의 유지보수성 저하
// iOS에서는 알림에 관한 부분을 하나로 묶어주는 통보센터 구현 (중재자 역할)

// 중재자(Mediator) 패턴
// - 복잡한 객체간의 관계를 단순화 시켜주는 클래스

// 사용예: C++로 고성능 서버를 만드는 라이브러리 - poco C++ Libraries, boost::asio
// 네트워크 서버에서 중요한 것: IO 모델, thread 방식
// 예전에는 ACE 라이브러리 사용, 표준에도 많이 도입돼 -> 요즘은 표준을 활용하는 poco, asio 쓴다.
// poco: 코드 읽기 쉽다, asio: 템플릿 발라놔서 읽기 어렵다.
// Design Pattern 중에 STL에 적용된 것이 별로 없다. Java class library를 보는 것이 패턴 공부에 좋다.
// 그런데 poco가 적절한 패턴이 많이 적용되어 있다. - C++ 디자인 패턴 레퍼런스로 좋다. 디자인 패턴과 C++ 스타일이 적절하게 융합
// 크로스 플랫폼: OS마다 고성능의 IO를 제공하는 메커니즘이 따로 있다. -> 추상화하여 플랫폼에 상관없이 같은 동작하게 제공
// poco는 아직 추상화가 부족한부분 있는데 asio는 잘 되어있다. 실제로는 asio 성능이 좋아.


#include <functional>	// 범용 함수 포인터
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;	// 사실은 이렇게 쓰지 말고 명시적으로 붙이는 것이 좋다.

// C++에서 callback을 등록하는 방법은 2가지 형태
// 1. 인터페이스 기반의 객체 등록
//		- 전통적인 디자인 패턴 (객체 지향), 관찰자
// 2. 함수 포인터 (function<>)으로 함수 등록
//		- 통보센터
//		map<string, vector<HANDLER>> notifi_map; -> 이벤트를 관련된 (멤버) 함수 리스트와 연결


// 아이폰 (맥)에 있는 통보센터를 만들어봅시다.
class NotificationCenter
{
	typedef function<void()> HANDLER;
	// 이벤트의 이름과 그와 연결되 다수의 핸들러 연결
	map<string, vector<HANDLER>> notifi_map;

public:
	void addObserver(string key, HANDLER handler)
	{
		notifi_map[key].push_back(handler);
	}

	void postNotificationWithName(string key)
	{
		// 이벤트(key)에 연결된 함수포인터 실행
		vector<HANDLER>& v = notifi_map[key];
		for (HANDLER e : v)
			e();
	}

	// global center의 개념을 도입하자.
	// Singleton: 오직 한개의 객체를 생성하고 어디서든 동일한 방법으로 접근할 수 있도록 한다.
	static NotificationCenter& defaultCenter()
	{
		static NotificationCenter instance;
		return instance;
	}

};

void foo() { cout << "foo" << endl; }
void goo(int n) { cout << "goo " << n << endl; }
class Dialog{
public:
	void warning() { cout << "Warning Dialog" << endl; }
};

int main()
{
	// 객체가 여러개면 알림이 중복될 수 있다.
//	NotificationCenter nc;
	// 싱글톤으로 구현해서 중복되지 않게 하자.
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	nc.addObserver("LOWBATTERY", &foo);
	nc.addObserver("LOWBATTERY", bind(&goo,5));

	Dialog dialog;
	nc.addObserver("LOWBATTERY", bind(&Dialog::warning, &dialog));

	// 알림을 사용하고 싶은 모든 객체에서 싱글톤으로 객체 받아와서 postNotificationWithName() 실행
	// 이제 배터리를 체크하는 모듈에서
	nc.postNotificationWithName("LOWBATTERY");
}

