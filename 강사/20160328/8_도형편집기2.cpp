// 8_도형편집기2
#include <iostream>
#include <vector>
using namespace std;

// http://d.pr/n/13upb

// 5. 기능이 추가되어도 (기능 확장에 열려 있고, Open)
//    기존 코드는 수정되면 안된다.(코드 수정에는 닫혀야 한다. Close)
//    한다는 이론 => OCP(개방 폐쇄 원칙)

// 6. 다형성은 OCP를 만족합니다.
// 7. Prototype Pattern: 기존에 존재하는 객체를 복사해서 새로운 객체를 만드는 패턴
//        - "다형성"을 이용한 객체의 복사
//  java: Cloneable, C#: ICloneable
//  java: clone();   C#: Clone();
//  ObjC: Copyable;      copy();

// 8. "Replace type code with polymorphism"
//    -> 리팩토링 용어 입니다.

// 9. Template Method 패턴
//    -> 변하지 않는 전체 알고리즘은 부모가 비 가상함수로 제공하고
//       변해야 하는 부분은 가상함수화 해서 자식이 
//       변경할 수 있게 하는 디자인 방법.
//    -> NVI(Non Virtual Interface)

// 10. DRY(Do not Repeat Yourself)
//    -> 코드의 중복은 코드의 유지보수 비용을 증가시킨다.

// http://d.pr/n/1g5Vk
class Shape {
public:
  // 변하지 않는 전체 흐름에서 변해야 하는 부분을 찾아서
  // 가상 함수로 분리해야 한다.
  // "공통성과 가변성의 분리 방법"
  
  // Java : final method - 오버라이딩 금지
  void draw() 
  {
    cout << "mutex lock" << endl;
    drawImpl();
    cout << "mutex unlock" << endl;
  }
   
  // 자신의 복사본을 만드는 가상함수가 있으면 좋다.
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
      cout << "몇 번째 도형을 복사 할까요 >> ";
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