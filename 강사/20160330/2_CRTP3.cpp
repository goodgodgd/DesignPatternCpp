// 2_CRTP3
#include <iostream>
using namespace std;

template <typename T>
class Base
{
protected:
  ~Base() {}  

public:
  void finalize()
  {
    delete static_cast<T*>(this);
  }

  // virtual ~Base() {}
};

class Derived : public Base<Derived>
{
public:
  ~Derived() { cout << "¼Ò¸êÀÚ È£Ãâ" << endl; }
};

int main()
{
  Base<Derived>* p = new Derived;
  // delete static_cast<Derived*>(p);

  p->finalize();
  // delete p;

}

