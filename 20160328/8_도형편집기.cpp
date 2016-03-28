// 도형 편집기로 배우는 객체 지향 설계의 개념
// 1. 모든 도형을 타입화 하면 편리하다.
// 2. 모든 도형의 공통의 부모가 잇다면, 모든 도형을 묶어서 관리할 수 잇다.
//		rect와 circle을 일일이 이름짓기 귀찮으면 도형마다 vector<>를 만들면 되지만 그럼 도형 종류가 추가될 때마다 vector<>도 늘어난다.
// 3. 모든 자식의 공통된 특징이 있다면 반드시 부모에도 있어야 한다.
//		그래야 부모 포인터로 묶어서 관리할 때 해당 특징을 이용할 수 있다.
//		- LSP (Liskov Substitution Principle)
// 4. 부모의 함수 중 자식이 재정의 하는 모든 함수는 반드시 가상 함수 이어야 한다.
//		"가상함수가 아닌 함수는 재정의 하지 말라" - "Effective C++" 격언

// http://d.pr/n/1ftN8

#include <vector>
#include <iostream>
using namespace std;

class Shape 
{
public:
	virtual void draw() { cout << "Shape draw" << endl; }
};

class Rect : public Shape
{
public:
	void draw() { cout << "Rect draw" << endl; }
};

class Circle : public Shape
{
public:
	void draw() { cout << "Circle draw" << endl; }
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
		else if (cmd == 9)
		{
			for (int i = 0; i < v.size(); ++i)
				v[i]->draw();
		}
	}
}
