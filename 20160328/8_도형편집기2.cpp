// 도형 편집기로 배우는 객체 지향 설계의 개념
// 1. 모든 도형을 타입화 하면 편리하다.
// 2. 모든 도형의 공통의 부모가 잇다면, 모든 도형을 묶어서 관리할 수 잇다.
//		rect와 circle을 일일이 이름짓기 귀찮으면 도형마다 vector<>를 만들면 되지만 그럼 도형 종류가 추가될 때마다 vector<>도 늘어난다.
// 3. 모든 자식의 공통된 특징이 있다면 반드시 부모에도 있어야 한다.
//		그래야 부모 포인터로 묶어서 관리할 때 해당 특징을 이용할 수 있다.
//		- LSP (Liskov Substitution Principle)
// 4. 부모의 함수 중 자식이 재정의 하는 모든 함수는 반드시 가상 함수 이어야 한다.
//		"가상함수가 아닌 함수는 재정의 하지 말라" - "Effective C++" 격언
// 5. 기능이 추가되어도  (기능 확장에는 열려 있고, Open)
//		기존 코드는 수정되면 안된다.  (코드 수정에는 닫혀야 한다. Close)
//		한다는 이론 => (OCP 원칙)
// 6. 다형성은 OCP를 만족합니다. (다형성을 잘 구현하면 기존 코드를 수정할 필요가 없다.)

// 7. Prototype Pattern: 기존에 존재하는 객체를 복사해서 새로운 객체를 만드는 패턴 (복사 생성자 사용)
//		핵심: "다형성"을 이용한 객체의 복사
//		java: Cloneable,	C#: ICloneable,	ObjC: Copyable
//		java: clone();,		C#: Clone();	ObjC: copy()

// 8. "Replace type code with polymorphism" => 리팩토링 용어
//		타입에 따라 분기하는 코드가 있다면 다형성으로 바꿔라.

// 9. Template Method 패턴
//		-> 변하지 않는 전체 알고리즘은 부모가 비 가상함수로 제공하고
//			변해야 하는 부분은 가상함수화 해서 자식이 변경할 수 있게 하는 디자인 방법
//		-> NVI(Non Virtual Interface): 디자인 패턴이전엔 원래 이렇게 부르고 많이 쓰고 있었다. 가장 많이 쓰이는 패턴

// 10. DRY(Do not Repeat Yourself)
//		-> 코드의 중복은 코드의 유지보수 비용을 증가시킨다.

// 코드의 중복은 기능이 응집되어 있지 않기 때문에 기능의 수정시 모두 찾아서 수정해야 하므로 유지보수성을 크게 떨어뜨린다.
// 코드에서 변하는 것과 변하지 않는 것을 반드시 분리해야 한다.
// 변하지 않는 전체 흐름에서 변해야 하는 부분을 찾아서 가상 함수로 분리해야 한다.
// "공통성과 가변성의 분리 방법"

// http://d.pr/n/1g5Vk

#include <vector>
#include <iostream>
using namespace std;

class Shape
{
public:

	// java에서는 비 가상함수는 오버라이딩을 못 하도록 "final method"로 구현한다.
	void draw()
	{
		// 변하는 부분: 비가상함수 draw()
		cout << "mutex lock" << endl;
		// 변하는 부분: 가상함수로 제공 drawImpl()
		drawImpl();
		cout << "Shape draw" << endl;
	}

protected:	// 내부 구현은 숨기자
	virtual void drawImpl()
	{
		cout << "Shape draw" << endl;
	}

public:
	// 자신의 복사본을 만드는 가상함수가 있으면 좋다.
	// 복제 생성자 이용
	virtual Shape* clone() { return new Shape(*this); }
};

class Rect : public Shape
{
protected:	// 내부 구현은 숨기자	
	virtual void drawImpl()
	{
		// mutex를 이렇게 중복되게 구현할 필요없다.
//		cout << "mutex lock" << endl;
		cout << "Rect draw" << endl;
//		cout << "mutex lock" << endl;
	}
public:
	virtual Shape* clone() { return new Rect(*this); }
};

class Circle : public Shape
{
protected:	// 내부 구현은 숨기자	
	void drawImpl() { cout << "Circle draw" << endl; }
public:
	virtual Shape* clone() { return new Circle(*this); }
};

int main()
{
	vector<Shape*> v;
	while (1)
	{
		int cmd;
		cin >> cmd;

		if (cmd == 1)
			v.push_back(new Rect);
		else if (cmd == 2)
			v.push_back(new Circle);
		else if (cmd == 8)
		{
			cout << "몇 번째 도형을 복사 할까요 >> ";
			int k;
			cin >> k;
			// 문제: v[k] - Rect인가? Circle인가?
			v.push_back(v[k]->clone());
		}

		else if (cmd == 9)
		{
			for (int i = 0; i < v.size(); ++i)
				v[i]->draw();
		}
	}
}
