// 빌더
// -> 공정은 동일하지만 표현이 달라지는 객체를 만들 때
// -> 객체 생성
// -> 생성자의 인자가 많을 때

#include <iostream>
#include <string>
using namespace std;

// 방법 3. Beans Pattern
// 방법: 기본 생성자를 호출하여 객체를 생성한 후, 설정함수를 통해서 각 필드를 초기화한다.
// 장점: 가독성이 좋다.
// 단점: 객체의 일관성이 깨진다.
//		객체를 생성한 이후에 바로 사용하는 것이 아니라 별도의 초기화 과정을 따로 거쳐야 한다.
//		2단 생성자처럼 불완전 객체의 문제, 생성을 해도 온전한 상태가 아니다.
//		완전한 객체인지 불완전한 객체인지 추가적인 관리가 필요하다.
//		필수 인자의 개념을 적용할 수 없다. 
//		불변 객체도 만들 수 없다. (const 멤버 변수)
//		스레드 안정서에 대한 추가적이 고려도 필요하다.

class UserInfo
{
public:
	UserInfo() {}

	void setId(string s) { id = s; }
	void setAddress(string s) { address = s; }
	void setLevel(int a) { level = a; }
	void setGold(int a) { gold = a; }
	void setCash(int a) { cash = a; }

private:
	/*const*/ string id;          // 필수 인자 쓸 수 없어
	/*const*/ string address;
	int level;                // 선택 인자
	int gold;
	int cash;
};

int main()
{
	UserInfo ui;
	ui.setId("chansik.yun");
	ui.setAddress("수원");
	ui.setLevel(10);
	ui.setGold(1000);
	ui.setCash(100);

}