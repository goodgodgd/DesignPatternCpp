// http://d.pr/n/13s6j

#include <iostream>
using namespace std;

#if 0
class SmartPhone
{
public:
	void take()
	{
		cout << "take picture with SP" << endl;
	}
};

class Camera
{
public:
	void take()
	{
		cout << "take picture with Camera" << endl;
	}
};

// ������ ����: ���� ��� ����� ��ü Ŭ������ Camera�� �����ؼ� (���� ������) �ٸ� ��ü (SmartPhone)�� �����ϱ� ��ƴ�.
// ���� ����: ��ü�� �Ұ����� ������ ������ ���� ���
class Person
{
public:
	void takePicture(Camera* p)
	{
		p->take();
	}
	// smart phone���� ������� ���� �̷��� �����ε��� ����� �Ѵ�. �ڵ� ���� ����
	void takePicture(SmartPhone* p)
	{
		p->take();
	}
};

int main()
{
	Camera camera;
	Person person;

	person.takePicture(&camera);
}
#endif

// 1. ī�޶� ����ڿ� ī�޶� ������ ������ ��Ģ�� ���� ��������.
//	- �������̽�, ��༭, ��������

// C++���� �������̽��� ����� ���
// �ַ� class ���� struct�� ���� ����.
// class�� ����Ʈ ���������ڰ� private�̰� struct�� public�̴�.
// �������̽��� ��� �޴� ��� �̵鿡�� ���µǾ� �־�� �ϹǷ� public�� ��� �Ѵ�.
// ���� struct�� ���� public: ���� ���� �� �ִ�.
struct ICamera
{
	virtual ~ICamera() {}	// �������̽��� �ᱹ �θ��̴�.
							// �ݵ�� ����Ҹ��ڰ� �ʿ��ϴ�.
	virtual void take() = 0;
};

// 2. ����ڴ� ��¥ ī�޶�� ������ ��Ģ�� �ִ�. ��Ģ��θ� ����ϸ� �ȴ�.
//		ī�޶� �������� �ʰ� �������̽��� �����ϹǷ� �������̽��� ��ӹ޴� � ��ü Ŭ�����ε� ���氡���ϴ�.
class Person
{
public:
	void takePicture(ICamera* p)
	{
		p->take();
	}
};

// 3. ī�޶��� �����ڴ� �������̽��� ��ӵ� �Լ��� �����ϴ� ������ ��ü Ŭ������ ����� �ȴ�.
// ��Ģ: ��� ī�޶�� ICamera �κ��� �Ļ��Ǿ�� �Ѵ�. ��� ���� ����		(�Ļ�: �⺻ ������ �Ǿ��ִ� ��)
//		��� ī�޶�� ICamera�� �����ؾ� �Ѵ�. ��� ǥ���Ѵ�.
//		�Ļ�(java���� extends)�� ����(java���� implements)�� �ٸ���.
class Camera : public ICamera
{
public:
	virtual void take()
	{
		cout << "take picture with Camera" << endl;
	}
};

// 4. ������ ����: Ŭ���̾�Ʈ�� ��ü Ŭ������ �����ϴ� ���� �ƴ϶� �߻� Ŭ������ �������̽��� �����ϴ� ������ ���� ���
//		DIP(Dependency Inversion Principle)
//		=> ����ڴ� �������̽��� �����ϴ� ��ü Ŭ������ ��ü�� �� �ִ�.
//		=> ��ü ������ ������ ������
//		=> OCP�� �����Ѵ�. (�� ����� �߰��ص� ���� �ڵ带 �������� �ʾƵ� �ȴ�.)
class SmartPhone : public ICamera
{
public:
	virtual void take()
	{
		cout << "take picture with SmartPhone" << endl;
	}
};

// ������ ����ڰ� ���� Ŭ������ Camera ��� ��ü Ŭ������ Ȯ�����̴ٸ� �������̽��� �� �ʿ䰡 ����.
// �������̽��� ���: �����ؾ� �� Ŭ������ �þ��. �������� �� �� ��������.
//					���� ���ε��̱� ������ ������ �������� �����Լ� ���̺� (�޸�) �����ؾ� �Ѵ�.
//					�������̽��� �����ϸ� ��� �ڽ� Ŭ������ �����ؾ� �ϹǷ� ������ �ʹ� ��ƴ�.
//					�ڹٿ����� �������̽��� ���� ���Ǿ��µ� �� ������ ������ �ʹ� ���������.
//					�ڹ�8������ ���� �����Լ� �ƴ� default method�� �����ؼ� �ʿ��� �͸� �������̵� �ϵ��� �����ƴ�.

int main()
{
	Camera c;
	Person p;
	p.takePicture(&c);
}
