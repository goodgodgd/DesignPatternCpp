
#include <iostream>
using namespace std;

class MenuItem
{
public:
	MenuItem() {}

	// �̰��� ���̺귯�� �̹Ƿ� ����� ������ ���� ����.
	virtual void command()
	{
		// �޴��� ���õ� ����� �ٽ� �ܺο� �˷��� �Ѵ�.
		// "��ü�� �ܺη� �̺�Ʈ�� �߻��Ѵ�." ��� ǥ��
	}
};

//

int main()
{
	MenuItem m1;
	m1.command();
}
