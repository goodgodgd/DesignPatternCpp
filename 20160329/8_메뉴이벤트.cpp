
#include <iostream>
using namespace std;

class MenuItem
{
public:
	MenuItem() {}

	// 이것은 라이브러리 이므로 여기다 구현할 수는 없다.
	virtual void command()
	{
		// 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
		// "객체가 외부로 이벤트를 발생한다." 라고 표현
	}
};

//

int main()
{
	MenuItem m1;
	m1.command();
}
