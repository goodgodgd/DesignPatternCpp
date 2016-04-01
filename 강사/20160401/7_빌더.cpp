#include <iostream>
#include <string>
using namespace std;

struct IBuilder
{
  virtual void makeHat() = 0;
  virtual void makeUniform() = 0;
  virtual void makeShoes() = 0;

  virtual string getResult() = 0;

  virtual ~IBuilder() {}
};

class Director
{
  IBuilder* pBuilder;
public:
  void setBuilder(IBuilder* p) { pBuilder = p; }

  // 아래 함수가 캐릭터를 만들어서 리턴하는 함수입니다.
  string construct()
  {
    pBuilder->makeHat();
    pBuilder->makeUniform();
    pBuilder->makeShoes();

    return pBuilder->getResult();
  }
};

// 다양한 나라의 빌더를 제공합니다.
class Korean : public IBuilder
{
  string c;
public:
  virtual void makeHat() {
    c += "삿갓";
  }
  virtual void makeUniform() {
    c += "한복";
  }

  virtual void makeShoes() {
    c += "고무신";
  }
  
  virtual string getResult() { return c; }
};

class American : public IBuilder
{
public:
  string c;
public:
  virtual void makeHat() {
    c += "야구모자";
  }
  virtual void makeUniform() {
    c += "양복";
  }

  virtual void makeShoes() {
    c += "구두";
  }

  virtual string getResult() { return c; }
};

int main()
{
  Korean korean; American american;
  Director director;

  // 캐릭터 선택 화살표 키를 누르면 이 코드를 실행한다.
  director.setBuilder(&korean);
  cout << director.construct() << endl;

  director.setBuilder(&american);
  cout << director.construct() << endl;
}