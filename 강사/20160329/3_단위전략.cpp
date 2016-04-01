// 3_단위전략

#include <iostream>
using namespace std;
// http://d.pr/n/173DM

// 동기화 여부를 인터페이스 기반의 다른 클래스로 분리하자.
// 장점: 실행 시간에 정책을 교체할 수 있다. - setSync
// 단점: 가상 함수 기반이므로 느리다.
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

List<int> st; // 전역 변수

int main()
{
  st.setSync(new SingleThread);
  
  st.push_front(10);

}




















