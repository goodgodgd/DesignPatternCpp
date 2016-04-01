// 4_데코레이터 패턴
#include <iostream>
using namespace std;

// 재귀적 합성 기법을 사용한 디자인 패턴 2가지
// 1. 컴포지트: 재귀적 합성을 통한 복합 객체의 구성
// 2. 데코레이터: 재귀적 합성을 통한 기능의 추가

// 핵심 2가지
// 1. 포함을 통한 기능의 추가 - 동적인 기능의 추가
// 2. 재귀적 합성 - 기능을 추가했던 객체를 다시 추가할 수 있다.

class Item
{
public:
  virtual void print() = 0;
  virtual ~Item() {}
};

class Ticket : public Item
{
public:
  void print()
  {
    cout << "작은 음악회 - 2016.12.25" << endl;
  }
};

// 모든 광고(포장지)의 공통의 특징을 부모로 제공하자
class Decorator : public Item
{
  Item& item;
public:
  Decorator(Item& i) : item(i) {}
  void print() { item.print(); }
};

class Ad1 : public Decorator
{
public:
  Ad1(Item& t) : Decorator(t) {}

  void print()
  {
    Decorator::print();
    cout << "자동차 광고" << endl;
  }
};

class Ad2 : public Decorator
{
public:
  Ad2(Item& t) : Decorator(t) {}

  void print()
  {
    cout << "TV 광고" << endl;
    Decorator::print();
  }

};

int main()
{
  Ticket t;

  // 기능을 추가한 객체에 다시 기능을 추가하고 싶다.
  Ad1 ad1(t);
  Ad2 ad2(ad1);

  ad2.print();
}


//---------------------------
// Zip으로 압축되어 있는 파일을 읽어야 한다. - NIO(New IO)
// FileInputStream fis = new FileInputStream("a.zip");
// BufferedInputStream bis  = new BufferedInputStream(fis);
// ZipInputStream zis = new ZipInputStream(bis);

// zis.read();

// 포장지 패턴
// - 문제를 분해해서 해결할 수 있도록 한다.
// - 클래스가 단 하나만의 책임을 가지도록 응집화 할 수 있다.
//   SRP