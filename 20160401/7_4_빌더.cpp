// 빌더
// -> 공정은 동일하지만 표현이 달라지는 객체를 만들 때
// -> 객체 생성
// -> 생성자의 인자가 많을 때

#include <iostream>
#include <string>
using namespace std;

// 방법 3. 빌더
//		: 점층적 생성자 패턴과 빈즈 패턴의 장점을 결합한 방법이다.

class UserInfo
{
public:
	class Builder		// UserInfo 생성해주는 역할
	{
	public:
		Builder(string i, string a) : id_(i), address_(a) {}
		Builder& level(int a)
		{
			level_ = a;
			return *this;
		}

		Builder& gold(int a)
		{
			gold_ = a;
			return *this;
		}

		Builder& cash(int a)
		{
			cash_ = a;
			return *this;
		}

		UserInfo build()
		{
			return UserInfo(*this);
		}

		// UserInfo 생성자에서 Builder의 멤버에 접근 가능하게
		friend class UserInfo;		// 중요!!

	private:
		const string id_;
		const string address_;
		int level_;
		int gold_;
		int cash_;
	};

private:
	const string id;		// 변하지 않는 필드 const
	const string address;	// 생성자의 필수 인자다, 생성자에서만 초기화 할 수 있다.
	int level;
	int gold;
	int cash;

public:
	UserInfo(const Builder& builder)
		: id(builder.id_),
		address(builder.address_),
		level(builder.level_),
		gold(builder.gold_),
		cash(builder.cash_) 
	{}
};

// 작성해야 하는 코드는 다소 있지만, 추가적인 객체에 대한 메모리도 필요하지만,
// 객체 일관성이 유지되고, 가독성도 좋다.
// 패킷을 만들때도 유용하다. - 항상 공정이 동일하고 내용만 달라진다.

// 빌더는 불변객체를 만드는데 유용합니다. UserInfo 의 모든 멤버를 const로 바꿔도 된다!!
// JavaL String -> StringBuilder, StringBuffer(스레드관리해줌)

int main()
{
	UserInfo ui = UserInfo::Builder("chansik.yun", "수원")
									.level(10)
									.gold(100)
									.cash(2000).build();
}
