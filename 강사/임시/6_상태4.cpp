// 6_상태4// 6_상태
// State Pattern: 상태에 따른 동작의 변경
//   - 게임 만들 때 널리 사용된다.

// 방법 3. 변하는 것을 인터페이스 기반 다른 클래스로 분리

#include <iostream>
using namespace std;

// 상태에 따른 동작을 정의한 인터페이스
struct IState
{
  virtual void run() = 0;
  virtual void attack() = 0;
  virtual ~IState() {}
};

// 공통성과 가변성의 분리
// - 디자인 패턴에서 변하는 것을 인터페이스 기반의 다른 클래스로
//   분리하는 패턴은 2가지 입니다.
// 1) 전략 패턴 - 변하는 것이 정책이나 알고리즘
// 2) 상태 패턴 - 변하는 것이 상태에 따른 동작

// 리팩토링의 격언 - Replace type code with State or Sterategy

class Hero
{
  IState* state;
  int gold;
public:
  Hero() : state(nullptr) {}
  void setState(IState* p) { state = p; }

  void run()    { state->run(); }
  void attack() { state->attack(); }
};

class NormalState : public IState
{
public:
  virtual void run()    { cout << "run" << endl; }
  virtual void attack() { cout << "attack" << endl; }
};

class FastState : public IState
{
public:
  virtual void run() { cout << "fast run" << endl; }
  virtual void attack() { cout << "fast attack" << endl; }
};

int main()
{
  NormalState ns; FastState fs;
  Hero hero;
  hero.setState(&ns);   // 초기 상태
  hero.run();
  hero.attack();

  //------------------   아이템 획득 (이전의 상태는 공유된다.)
  hero.setState(&fs);
  hero.run();
  hero.attack();
}


#if 0
// enum Singleton
enum Singleton {
  INSTANCE;
}

class Singleton {
  private static final Singleton INSTANCE = new Singleton();

  private Singleton() {}

  public Singleton getInstance() {
    return INSTANCE;
  }
}

// 위처럼 만들면 문제점이 두가지 있습니다.
// 1. Reflection 을 통해서 2개 이상의 객체를 생성 가능합니다. 
// 2. 객체를 직렬화를 통해서 2개 이상의 객체를 생성 할 수 있습니다. 



// enum class
enum State
{
  FAST{
  @Override
  void run() {
  System.out.println("fast run");
}

},
NORMAL{
  @Override
  void run() {
  System.out.println("run");
}
};

abstract void run();
}


class Hero {

  // int 상수 패턴 
  private static final int STATE_FAST = 0;
  private static final int STATE_NORMAL = 1;

  // int state;


  private State state;

  public void setState(State state) {
    this.state = state;
  }

  void run() {
    state.run();
  }
}

public class Test {
  public static void main(String[] args) {
    Hero hero = new Hero();
    hero.setState(State.NORMAL);
    hero.run();

    hero.setState(State.FAST);
    hero.run();
  }
}


#endif