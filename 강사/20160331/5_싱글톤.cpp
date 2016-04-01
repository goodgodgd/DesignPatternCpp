// 5_싱글톤
#include <iostream>
using namespace std;

// 개념 : 오직 한개의 객체를 만들수 있고 어디에서도 동일한 방법으로 객체를
//        얻을 수 있게 하는 패턴.
// - Chromium, Webkit, Firefox

class Cursor
{
private:
  Cursor() {}           // 규칙 1. private 생성자

  // 규칙 3. 복사와 대입 금지
  //  핵심: 선언만 한다. 구현이 없다!
  // Cursor(const Cursor&);
  // void operator=(const Cursor&);

  // 위의 복사 금지 기법은 C++11에서 문법화 되었습니다.
  // "delete function" 이라는 문법.
  Cursor(const Cursor&) = delete;
  void operator=(const Cursor&) = delete;

  // static final Cursor INSTANCE = new Cursor(); - Java 1.5
  // lazy initialization

public:
  // 규칙 2. 오직 한개만 만드는 정적 멤버 함수
  // - 마이어스의 싱글톤
  static Cursor& getInstance()
  {
    static Cursor instance;
    // Cursor s = instance;

    return instance;
  }
};

// Cursor c;
// - 생성과 소멸의 시점이 명확하게 정의되어 있지 않다.

int main()
{
  Cursor::getInstance();

  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  cout << &c1 << endl;
  cout << &c2 << endl;
}





