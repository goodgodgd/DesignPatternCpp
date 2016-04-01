// 3_��������

#include <iostream>
using namespace std;
// http://d.pr/n/173DM

// ����ȭ ���θ� �������̽� ����� �ٸ� Ŭ������ �и�����.
// ����: ���� �ð��� ��å�� ��ü�� �� �ִ�. - setSync
// ����: ���� �Լ� ����̹Ƿ� ������.
struct ISync
{
  virtual void lock() = 0;
  virtual void unlock() = 0;
  virtual ~ISync() {}
};

class MultiThread : public ISync
{
public:
  virtual void lock()   { cout << "mutex lock" << endl;   }
  virtual void unlock() { cout << "mutex unlock" << endl; }
};
// http://d.pr/n/10xvN
class SingleThread : public ISync
{
public:
  virtual void lock() {}
  virtual void unlock() {}
};

template <typename T>
class List
{
  ISync* pSync;
public:
  List() : pSync(0) {
    if (pSync == 0)
      pSync = new SingleThread;
  }

  void setSync(ISync* p) { pSync = p; }

  void push_front(const T& a) 
  {
    pSync->lock();
    // ...
    pSync->unlock();
  }
};

List<int> st; // ���� ����

int main()
{
  st.setSync(new SingleThread);
  
  st.push_front(10);

}




















