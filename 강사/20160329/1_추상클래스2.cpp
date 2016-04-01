// 1_추상클래스2
#include <iostream>
using namespace std;

// http://d.pr/n/13s6j

// 1. 카메라 사용자와 카메라 제작자 사이의 규칙을 먼저 설계하자.
//   - 인터페이스, 계약서, 프로토콜

// C++에서 인터페이스를 만드는 방법
// #define interface struct
struct ICamera
{
  // default method
  virtual void save() {}

  virtual void take() = 0;
  virtual ~ICamera() {}  // 인터페이스도 결국 부모이다.
                         // 반드시 가상 소멸자가 필요하다.
};

// 2. 사용자는 진짜 카메라는 없지만 규칙이 있다. 규칙대로만 사용하면 된다.
class Person
{
public:
  void takePicture(ICamera* p)
  {
    p->take();
  }
};

// 3. 카메라의 제작자는 인터페이스로 약속된 함수를 제공하는 형태의 구체 클래스를 
//    만들면 된다.

// 규칙: 모든 카메라는 ICamera 로부터 파생되어야 한다. 라고 하지 말고
//      모든 카메라는 ICamera를 구현해야 한다. 라고 표현한다.
class Camera : public ICamera
{
public:
  virtual void take()
  {
    cout << "take picture with Camera" << endl;
  }
};

// 4. 느슨한 결합: 클라이언트가 구체 클래스에 의존하는 것이 아니라
//               추상 클래스나 인터페이스에 의존하는 형태의 설계 방법
//               DIP(Dependency Inversion Principle)
//             => 사용자는 인터페이스를 만족하는 구체 클래스를 교체할 수 있다.
//             => 교체 가능한 유연한 디자인
//             => OCP를 만족한다.
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
// 강한 결합: 교체가 불가능한 형태의 경직된 설계 방식
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



