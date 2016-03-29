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

// 문제의 소지: 사진 찍는 기능이 구체 클래스인 Camera에 의존해서 (강한 결합을) 다른 객체 (SmartPhone)를 도입하기 어렵다.
// 강한 결합: 교체가 불가능한 형태의 경직된 설계 방식
class Person
{
public:
	void takePicture(Camera* p)
	{
		p->take();
	}
	// smart phone으로 사진찍기 위해 이렇게 오버로딩을 해줘야 한다. 코드 변경 불편
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

// 1. 카메라 사용자와 카메라 제작자 사이의 규칙을 먼저 설계하자.
//	- 인터페이스, 계약서, 프로토콜

// C++에서 인터페이스를 만드는 방법
// 주로 class 보다 struct를 많이 쓴다.
// class는 디폴트 접근지정자가 private이고 struct는 public이다.
// 인터페이스는 상속 받는 모든 이들에게 오픈되어 있어야 하므로 public을 써야 한다.
// 따라서 struct를 쓰면 public: 한줄 줄일 수 있다.
struct ICamera
{
	virtual ~ICamera() {}	// 인터페이스도 결국 부모이다.
							// 반드시 가상소멸자가 필요하다.
	virtual void take() = 0;
};

// 2. 사용자는 진짜 카메라는 없지만 규칙이 있다. 규칙대로만 사용하면 된다.
//		카메라에 의존하지 않고 인터페이스에 의존하므로 인터페이스를 상속받는 어떤 구체 클래스로도 변경가능하다.
class Person
{
public:
	void takePicture(ICamera* p)
	{
		p->take();
	}
};

// 3. 카메라의 제작자는 인터페이스로 약속된 함수를 제공하는 형태의 구체 클래스를 만들면 된다.
// 규칙: 모든 카메라는 ICamera 로부터 파생되어야 한다. 라고 하지 말고		(파생: 기본 구현이 되어있는 것)
//		모든 카메라는 ICamera를 구현해야 한다. 라고 표현한다.
//		파생(java에서 extends)과 구현(java에서 implements)은 다르다.
class Camera : public ICamera
{
public:
	virtual void take()
	{
		cout << "take picture with Camera" << endl;
	}
};

// 4. 느슨한 결합: 클라이언트가 구체 클래스에 의존하는 것이 아니라 추상 클래스나 인터페이스에 의존하는 형태의 설계 방법
//		DIP(Dependency Inversion Principle)
//		=> 사용자는 인터페이스를 만족하는 구체 클래스를 교체할 수 있다.
//		=> 교체 가능한 유연한 디자인
//		=> OCP를 만족한다. (새 기능을 추가해도 기존 코드를 수정하지 않아도 된다.)
class SmartPhone : public ICamera
{
public:
	virtual void take()
	{
		cout << "take picture with SmartPhone" << endl;
	}
};

// 하지만 사용자가 의존 클래스가 Camera 라는 구체 클래스로 확정적이다면 인터페이스를 쓸 필요가 없다.
// 인터페이스의 비용: 관리해야 할 클래스가 늘어난다. 유지보수 할 게 많아진다.
//					동적 바인딩이기 때문에 성능이 떨어지고 가상함수 테이블 (메모리) 유지해야 한다.
//					인터페이스를 변경하면 모든 자식 클래스를 변경해야 하므로 변경이 너무 어렵다.
//					자바에서는 인터페이스가 많이 사용되었는데 이 때문에 변경이 너무 어려워졌다.
//					자바8에서는 순수 가상함수 아닌 default method를 제공해서 필요한 것만 오버라이딩 하도록 수정됐다.

int main()
{
	Camera c;
	Person p;
	p.takePicture(&c);
}
