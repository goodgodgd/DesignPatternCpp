// ����
// -> ������ ���������� ǥ���� �޶����� ��ü�� ���� ��
// -> ��ü ����

// -> �������� ���ڰ� ������
#include <iostream>
#include <string>
using namespace std;

// ��� 2. Beans Pattern
//    
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
  const string id;          // �ʼ� ����
  const string address;
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