// �뺸���� (Notification Center)

// �ڵ������� "�˸�" ����� ����� �� �����ڰ� �����ϴ�.
// �׷��� �̰� �� �����ڷ� ����� Ŭ������ ���� ���赵 ���� ��ü�� �ʹ� ��������. -> �ڵ��� ���������� ����
// iOS������ �˸��� ���� �κ��� �ϳ��� �����ִ� �뺸���� ���� (������ ����)

// ������(Mediator) ����
// - ������ ��ü���� ���踦 �ܼ�ȭ �����ִ� Ŭ����

// ��뿹: C++�� ���� ������ ����� ���̺귯�� - poco C++ Libraries, boost::asio
// ��Ʈ��ũ �������� �߿��� ��: IO ��, thread ���
// �������� ACE ���̺귯�� ���, ǥ�ؿ��� ���� ���Ե� -> ������ ǥ���� Ȱ���ϴ� poco, asio ����.
// poco: �ڵ� �б� ����, asio: ���ø� �߶���� �б� ��ƴ�.
// Design Pattern �߿� STL�� ����� ���� ���� ����. Java class library�� ���� ���� ���� ���ο� ����.
// �׷��� poco�� ������ ������ ���� ����Ǿ� �ִ�. - C++ ������ ���� ���۷����� ����. ������ ���ϰ� C++ ��Ÿ���� �����ϰ� ����
// ũ�ν� �÷���: OS���� ������ IO�� �����ϴ� ��Ŀ������ ���� �ִ�. -> �߻�ȭ�Ͽ� �÷����� ������� ���� �����ϰ� ����
// poco�� ���� �߻�ȭ�� �����Ѻκ� �ִµ� asio�� �� �Ǿ��ִ�. �����δ� asio ������ ����.


#include <functional>	// ���� �Լ� ������
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;	// ����� �̷��� ���� ���� ��������� ���̴� ���� ����.

// C++���� callback�� ����ϴ� ����� 2���� ����
// 1. �������̽� ����� ��ü ���
//		- �������� ������ ���� (��ü ����), ������
// 2. �Լ� ������ (function<>)���� �Լ� ���
//		- �뺸����
//		map<string, vector<HANDLER>> notifi_map; -> �̺�Ʈ�� ���õ� (���) �Լ� ����Ʈ�� ����


// ������ (��)�� �ִ� �뺸���͸� �����ô�.
class NotificationCenter
{
	typedef function<void()> HANDLER;
	// �̺�Ʈ�� �̸��� �׿� ����� �ټ��� �ڵ鷯 ����
	map<string, vector<HANDLER>> notifi_map;

public:
	void addObserver(string key, HANDLER handler)
	{
		notifi_map[key].push_back(handler);
	}

	void postNotificationWithName(string key)
	{
		// �̺�Ʈ(key)�� ����� �Լ������� ����
		vector<HANDLER>& v = notifi_map[key];
		for (HANDLER e : v)
			e();
	}

	// global center�� ������ ��������.
	// Singleton: ���� �Ѱ��� ��ü�� �����ϰ� ��𼭵� ������ ������� ������ �� �ֵ��� �Ѵ�.
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
	// ��ü�� �������� �˸��� �ߺ��� �� �ִ�.
//	NotificationCenter nc;
	// �̱������� �����ؼ� �ߺ����� �ʰ� ����.
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	nc.addObserver("LOWBATTERY", &foo);
	nc.addObserver("LOWBATTERY", bind(&goo,5));

	Dialog dialog;
	nc.addObserver("LOWBATTERY", bind(&Dialog::warning, &dialog));

	// �˸��� ����ϰ� ���� ��� ��ü���� �̱������� ��ü �޾ƿͼ� postNotificationWithName() ����
	// ���� ���͸��� üũ�ϴ� ��⿡��
	nc.postNotificationWithName("LOWBATTERY");
}

