#include <iostream>
using namespace std;
// 3_��������2

// Effective Java

// API Design on C++

// C++ - ��ı ���̾
// Effective C++

// More Effective C++
// Modern Effective C++
// Effective STL

// ��� ����
// Exceptional C++
// More Exceptional C++
// Exceptional C++ Style

// ��� ���� & �ȵ巹�� �˷���帣��
// C++ Coding Style

// Modern C++ Design




// ��������(FileZilla) - 192.168.2.234
//                    id: cpp
// ioacademy3_2G(5G)

// ���� ����(Policy-based) Design - "Modern C++ design"
// => ��å�� ���� �ڵ带 ������ �ð��� ������ ���� ���
// => C++ ǥ�� ���̺귯���� �ٽ� ������ ���

// ����: �����Լ��� �ƴ� �ζ��� �Լ��̴�. ȣ�⿡ ���� ���� ���ϰ� ����.
// ����: ��å Ŭ������ �Լ��� �ƴ� ���ø� ���ڷ� ���޵ǹǷ�, ���� �ÿ� ��å��
//      ��ü �ϴ� ���� �Ұ����ϴ�.
//     => ������ �Ҷ� ��å�� �����ȴ�.!!!

// ����� ����� ���� ����
template <typename T, typename ThreadModel = SingleThread>
class List : public ThreadModel
{
public:
  void push_front(const T& a)
  {
    lock();
    //...
    unlock();
  }
};

class SingleThread
{
public:
  inline void lock() {}
  inline void unlock() {}
};

// http://d.pr/n/1cEbJ
class MultiThread
{
public:
  void lock()   { cout << "mutex lock" << endl; }
  void unlock() { cout << "mutex unlock" << endl; }
};

List<int, MultiThread> st;

int main()
{

}
