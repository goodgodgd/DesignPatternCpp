// ���� ������� ���� ��ü ���� ������ ����
// 1. ��� ������ Ÿ��ȭ �ϸ� ���ϴ�.
// 2. ��� ������ ������ �θ� �մٸ�, ��� ������ ��� ������ �� �մ�.
//		rect�� circle�� ������ �̸����� �������� �������� vector<>�� ����� ������ �׷� ���� ������ �߰��� ������ vector<>�� �þ��.
// 3. ��� �ڽ��� ����� Ư¡�� �ִٸ� �ݵ�� �θ𿡵� �־�� �Ѵ�.
//		�׷��� �θ� �����ͷ� ��� ������ �� �ش� Ư¡�� �̿��� �� �ִ�.
//		- LSP (Liskov Substitution Principle)
// 4. �θ��� �Լ� �� �ڽ��� ������ �ϴ� ��� �Լ��� �ݵ�� ���� �Լ� �̾�� �Ѵ�.
//		"�����Լ��� �ƴ� �Լ��� ������ ���� ����" - "Effective C++" �ݾ�
// 5. ����� �߰��Ǿ  (��� Ȯ�忡�� ���� �ְ�, Open)
//		���� �ڵ�� �����Ǹ� �ȵȴ�.  (�ڵ� �������� ������ �Ѵ�. Close)
//		�Ѵٴ� �̷� => (OCP ��Ģ)
// 6. �������� OCP�� �����մϴ�. (�������� �� �����ϸ� ���� �ڵ带 ������ �ʿ䰡 ����.)

// 7. Prototype Pattern: ������ �����ϴ� ��ü�� �����ؼ� ���ο� ��ü�� ����� ���� (���� ������ ���)
//		�ٽ�: "������"�� �̿��� ��ü�� ����
//		java: Cloneable,	C#: ICloneable,	ObjC: Copyable
//		java: clone();,		C#: Clone();	ObjC: copy()

// 8. "Replace type code with polymorphism" => �����丵 ���
//		Ÿ�Կ� ���� �б��ϴ� �ڵ尡 �ִٸ� ���������� �ٲ��.

// 9. Template Method ����
//		-> ������ �ʴ� ��ü �˰����� �θ� �� �����Լ��� �����ϰ�
//			���ؾ� �ϴ� �κ��� �����Լ�ȭ �ؼ� �ڽ��� ������ �� �ְ� �ϴ� ������ ���
//		-> NVI(Non Virtual Interface): ������ ���������� ���� �̷��� �θ��� ���� ���� �־���. ���� ���� ���̴� ����

// 10. DRY(Do not Repeat Yourself)
//		-> �ڵ��� �ߺ��� �ڵ��� �������� ����� ������Ų��.

// �ڵ��� �ߺ��� ����� �����Ǿ� ���� �ʱ� ������ ����� ������ ��� ã�Ƽ� �����ؾ� �ϹǷ� ������������ ũ�� ����߸���.
// �ڵ忡�� ���ϴ� �Ͱ� ������ �ʴ� ���� �ݵ�� �и��ؾ� �Ѵ�.
// ������ �ʴ� ��ü �帧���� ���ؾ� �ϴ� �κ��� ã�Ƽ� ���� �Լ��� �и��ؾ� �Ѵ�.
// "���뼺�� �������� �и� ���"

// http://d.pr/n/1g5Vk

#include <vector>
#include <iostream>
using namespace std;

class Shape
{
public:

	// java������ �� �����Լ��� �������̵��� �� �ϵ��� "final method"�� �����Ѵ�.
	void draw()
	{
		// ���ϴ� �κ�: �񰡻��Լ� draw()
		cout << "mutex lock" << endl;
		// ���ϴ� �κ�: �����Լ��� ���� drawImpl()
		drawImpl();
		cout << "Shape draw" << endl;
	}

protected:	// ���� ������ ������
	virtual void drawImpl()
	{
		cout << "Shape draw" << endl;
	}

public:
	// �ڽ��� ���纻�� ����� �����Լ��� ������ ����.
	// ���� ������ �̿�
	virtual Shape* clone() { return new Shape(*this); }
};

class Rect : public Shape
{
protected:	// ���� ������ ������	
	virtual void drawImpl()
	{
		// mutex�� �̷��� �ߺ��ǰ� ������ �ʿ����.
//		cout << "mutex lock" << endl;
		cout << "Rect draw" << endl;
//		cout << "mutex lock" << endl;
	}
public:
	virtual Shape* clone() { return new Rect(*this); }
};

class Circle : public Shape
{
protected:	// ���� ������ ������	
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
			cout << "�� ��° ������ ���� �ұ�� >> ";
			int k;
			cin >> k;
			// ����: v[k] - Rect�ΰ�? Circle�ΰ�?
			v.push_back(v[k]->clone());
		}

		else if (cmd == 9)
		{
			for (int i = 0; i < v.size(); ++i)
				v[i]->draw();
		}
	}
}
