// 8_����������2
#include <iostream>
#include <vector>
using namespace std;

// http://d.pr/n/13upb

// 5. ����� �߰��Ǿ (��� Ȯ�忡 ���� �ְ�, Open)
//    ���� �ڵ�� �����Ǹ� �ȵȴ�.(�ڵ� �������� ������ �Ѵ�. Close)
//    �Ѵٴ� �̷� => OCP(���� ��� ��Ģ)

// 6. �������� OCP�� �����մϴ�.
// 7. Prototype Pattern: ������ �����ϴ� ��ü�� �����ؼ� ���ο� ��ü�� ����� ����
//        - "������"�� �̿��� ��ü�� ����
//  java: Cloneable, C#: ICloneable
//  java: clone();   C#: Clone();
//  ObjC: Copyable;      copy();

// 8. "Replace type code with polymorphism"
//    -> �����丵 ��� �Դϴ�.

// 9. Template Method ����
//    -> ������ �ʴ� ��ü �˰����� �θ� �� �����Լ��� �����ϰ�
//       ���ؾ� �ϴ� �κ��� �����Լ�ȭ �ؼ� �ڽ��� 
//       ������ �� �ְ� �ϴ� ������ ���.
//    -> NVI(Non Virtual Interface)

// 10. DRY(Do not Repeat Yourself)
//    -> �ڵ��� �ߺ��� �ڵ��� �������� ����� ������Ų��.

// http://d.pr/n/1g5Vk
class Shape {
public:
  // ������ �ʴ� ��ü �帧���� ���ؾ� �ϴ� �κ��� ã�Ƽ�
  // ���� �Լ��� �и��ؾ� �Ѵ�.
  // "���뼺�� �������� �и� ���"
  
  // Java : final method - �������̵� ����
  void draw() 
  {
    cout << "mutex lock" << endl;
    drawImpl();
    cout << "mutex unlock" << endl;
  }
   
  // �ڽ��� ���纻�� ����� �����Լ��� ������ ����.
  virtual Shape* clone() { return new Shape(*this); }

protected:
  virtual void drawImpl() {
    cout << "Shape draw" << endl;
  }
};

class Rect : public Shape
{
protected:
  virtual void drawImpl() 
  { cout << "Rect draw" << endl; }
public:
  virtual Shape* clone() { return new Rect(*this); }
};

class Circle : public Shape
{
protected:
  virtual void drawImpl() { cout << "Circle draw" << endl; }

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

    if (cmd == 1)      v.push_back(new Rect);
    else if (cmd == 2) v.push_back(new Circle);
    else if (cmd == 8) {
      cout << "�� ��° ������ ���� �ұ�� >> ";
      int k;
      cin >> k;

      v.push_back(v[k]->clone());
    }
    else if (cmd == 9) {
      for (int i = 0; i < v.size(); ++i)
        v[i]->draw();
    }

  }

}