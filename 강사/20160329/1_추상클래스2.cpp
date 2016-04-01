// 1_�߻�Ŭ����2
#include <iostream>
using namespace std;

// http://d.pr/n/13s6j

// 1. ī�޶� ����ڿ� ī�޶� ������ ������ ��Ģ�� ���� ��������.
//   - �������̽�, ��༭, ��������

// C++���� �������̽��� ����� ���
// #define interface struct
struct ICamera
{
  // default method
  virtual void save() {}

  virtual void take() = 0;
  virtual ~ICamera() {}  // �������̽��� �ᱹ �θ��̴�.
                         // �ݵ�� ���� �Ҹ��ڰ� �ʿ��ϴ�.
};

// 2. ����ڴ� ��¥ ī�޶�� ������ ��Ģ�� �ִ�. ��Ģ��θ� ����ϸ� �ȴ�.
class Person
{
public:
  void takePicture(ICamera* p)
  {
    p->take();
  }
};

// 3. ī�޶��� �����ڴ� �������̽��� ��ӵ� �Լ��� �����ϴ� ������ ��ü Ŭ������ 
//    ����� �ȴ�.

// ��Ģ: ��� ī�޶�� ICamera �κ��� �Ļ��Ǿ�� �Ѵ�. ��� ���� ����
//      ��� ī�޶�� ICamera�� �����ؾ� �Ѵ�. ��� ǥ���Ѵ�.
class Camera : public ICamera
{
public:
  virtual void take()
  {
    cout << "take picture with Camera" << endl;
  }
};

// 4. ������ ����: Ŭ���̾�Ʈ�� ��ü Ŭ������ �����ϴ� ���� �ƴ϶�
//               �߻� Ŭ������ �������̽��� �����ϴ� ������ ���� ���
//               DIP(Dependency Inversion Principle)
//             => ����ڴ� �������̽��� �����ϴ� ��ü Ŭ������ ��ü�� �� �ִ�.
//             => ��ü ������ ������ ������
//             => OCP�� �����Ѵ�.
class SmartPhone : public ICamera
{
public:
  virtual void take() {}
};

int main()
{
  Camera c; SmartPhone s;
  Person p; 
  p.takePicture(&s);
}


#if 0
// ���� ����: ��ü�� �Ұ����� ������ ������ ���� ���
class SmartPhone
{
public:
  void take()
  { cout << "take picture with SP" << endl;}
};


class Camera
{
public:
  void take()
  { cout << "take picture with Camera" << endl;}
};

class Person
{
public:
  void takePicture(SmartPhone* p)
  {
  }

  void takePicture(Camera* p)
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



