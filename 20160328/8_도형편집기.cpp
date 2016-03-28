// ���� ������� ���� ��ü ���� ������ ����
// 1. ��� ������ Ÿ��ȭ �ϸ� ���ϴ�.
// 2. ��� ������ ������ �θ� �մٸ�, ��� ������ ��� ������ �� �մ�.
//		rect�� circle�� ������ �̸����� �������� �������� vector<>�� ����� ������ �׷� ���� ������ �߰��� ������ vector<>�� �þ��.
// 3. ��� �ڽ��� ����� Ư¡�� �ִٸ� �ݵ�� �θ𿡵� �־�� �Ѵ�.
//		�׷��� �θ� �����ͷ� ��� ������ �� �ش� Ư¡�� �̿��� �� �ִ�.
//		- LSP (Liskov Substitution Principle)
// 4. �θ��� �Լ� �� �ڽ��� ������ �ϴ� ��� �Լ��� �ݵ�� ���� �Լ� �̾�� �Ѵ�.
//		"�����Լ��� �ƴ� �Լ��� ������ ���� ����" - "Effective C++" �ݾ�

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
