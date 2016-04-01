// 6_����4// 6_����
// State Pattern: ���¿� ���� ������ ����
//   - ���� ���� �� �θ� ���ȴ�.

// ��� 3. ���ϴ� ���� �������̽� ��� �ٸ� Ŭ������ �и�

#include <iostream>
using namespace std;

// ���¿� ���� ������ ������ �������̽�
struct IState
{
  virtual void run() = 0;
  virtual void attack() = 0;
  virtual ~IState() {}
};

// ���뼺�� �������� �и�
// - ������ ���Ͽ��� ���ϴ� ���� �������̽� ����� �ٸ� Ŭ������
//   �и��ϴ� ������ 2���� �Դϴ�.
// 1) ���� ���� - ���ϴ� ���� ��å�̳� �˰���
// 2) ���� ���� - ���ϴ� ���� ���¿� ���� ����

// �����丵�� �ݾ� - Replace type code with State or Sterategy

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
  hero.setState(&ns);   // �ʱ� ����
  hero.run();
  hero.attack();

  //------------------   ������ ȹ�� (������ ���´� �����ȴ�.)
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

// ��ó�� ����� �������� �ΰ��� �ֽ��ϴ�.
// 1. Reflection �� ���ؼ� 2�� �̻��� ��ü�� ���� �����մϴ�. 
// 2. ��ü�� ����ȭ�� ���ؼ� 2�� �̻��� ��ü�� ���� �� �� �ֽ��ϴ�. 



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

  // int ��� ���� 
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