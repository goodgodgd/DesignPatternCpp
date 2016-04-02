// ����
// -> ������ ���������� ǥ���� �޶����� ��ü�� ���� ��
// -> ��ü ����
// -> �������� ���ڰ� ���� ��

#include <iostream>
#include <string>
using namespace std;

// ��� 3. ����
//		: ������ ������ ���ϰ� ���� ������ ������ ������ ����̴�.

class UserInfo
{
public:
	class Builder		// UserInfo �������ִ� ����
	{
	public:
		Builder(string i, string a) : id_(i), address_(a) {}	// �ʼ����ڴ� �ݵ�� ����!

		Builder& level(int a)
		{
			level_ = a;
			return *this;		// �ڽ��� ���۷����� �����ϴ� ���� �ٽ�! -> �׷��� �ٸ� setter�� �����Ҽ� �ִ�.
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

		// UserInfo �����ڿ��� Builder�� ����� ���� �����ϰ� �����.
		friend class UserInfo;		// �߿�!!

	private:
		const string id_;
		const string address_;
		int level_;
		int gold_;
		int cash_;
	};

private:
	const string id;		// ������ �ʴ� �ʵ� const
	const string address;	// �������� �ʼ� ���ڴ�, �����ڿ����� �ʱ�ȭ �� �� �ִ�.
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

// �ۼ��ؾ� �ϴ� �ڵ�� �ټ� ������, �߰����� ��ü�� ���� �޸𸮵� �ʿ�������,
// ��ü �ϰ����� �����ǰ�, �������� ����.
// ��Ŷ�� ���鶧�� �����ϴ�. - �׻� ������ �����ϰ� ���븸 �޶�����.

// ������ �Һ���ü�� ����µ� �����մϴ�. UserInfo �� ��� ����� const�� �ٲ㵵 �ȴ�!!
// JavaL String -> StringBuilder, StringBuffer(�������������)

int main()
{
	UserInfo ui = UserInfo::Builder("hyukdoo.choi", "�ͻ�")		// �ʼ� ����(�Һ� ����) �Է�
									.level(10)					// ������ ������ �Է�
									.gold(100)
									.cash(2000)
									.build();					// �ݵ�� build �Լ��� ������!!
}
