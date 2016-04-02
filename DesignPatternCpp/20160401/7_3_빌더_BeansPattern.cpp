// ����
// -> ������ ���������� ǥ���� �޶����� ��ü�� ���� ��
// -> ��ü ����
// -> �������� ���ڰ� ���� ��

#include <iostream>
#include <string>
using namespace std;

// ��� 3. Beans Pattern
// ���: �⺻ �����ڸ� ȣ���Ͽ� ��ü�� ������ ��, �����Լ��� ���ؼ� �� �ʵ带 �ʱ�ȭ�Ѵ�.
// ����: �������� ����.
// ����: ��ü�� �ϰ����� ������.
//		��ü�� ������ ���Ŀ� �ٷ� ����ϴ� ���� �ƴ϶� ������ �ʱ�ȭ ������ ���� ���ľ� �Ѵ�.
//		2�� ������ó�� �ҿ��� ��ü�� ����, ������ �ص� ������ ���°� �ƴϴ�.
//		������ ��ü���� �ҿ����� ��ü���� �߰����� ������ �ʿ��ϴ�.
//		�ʼ� ������ ������ ������ �� ����. 
//		�Һ� ��ü�� ���� �� ����. (const ��� ����)
//		������ �������� ���� �߰����� ����� �ʿ��ϴ�.

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
	/*const*/ string id;          // �ʼ� ���� �� �� ����
	/*const*/ string address;
	int level;                // ���� ����
	int gold;
	int cash;
};

int main()
{
	UserInfo ui;
	ui.setId("chansik.yun");
	ui.setAddress("����");
	ui.setLevel(10);
	ui.setGold(1000);
	ui.setCash(100);

}