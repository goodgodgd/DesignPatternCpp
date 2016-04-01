// SampleGraph.cpp
#include "IObserver.h"

#include <iostream>
using namespace std;

class SampleGraph : public IObserver
{
public:
  virtual void onUpdate(void* p)
  {
    int* data = static_cast<int*>(p);
    cout << "******** Sample Graph *********" << endl;
    for (int i = 0; i < 5; ++i)
      cout << i << " : " << data[i] << endl;
  }
};

// �ݵ�� ���� ��� �ȿ��� ��ü�� �����ϴ� ����� �������־�� �մϴ�. - �ٽ�!!!
// - SampleGraph ��� �̸��� ���� DLL�� ����� ����� �˰� �ֽ��ϴ�.
// - ���α׷� ���ο����� ���� �̸��� ����ϸ� �ȵ˴ϴ�.

// �ݵ�� DLL ���ο��� �ڽ��� ���� Ŭ������ ��ü�� �������־�� �մϴ�.
// - �Լ� �ϳ��� ����մϴ�.

extern "C"
__declspec(dllexport)   // �����쿡�� DLL ���� �ɺ��� �����ϴ� ���.
IObserver* CreateGraph()
{
  return new SampleGraph;
}

#if 0
void foo() {}          -> foo

void foo(int) {}       -> foo@int
void foo(double) {}    -> foo@double
void foo(int, int) {}  -> foo@int@int
#endif

// ���α׷� -> visual studio 2013 -> visual studio 2013 tools -> Developer Command Prompt
// cl SampleGraph.cpp /LD

// /LD: DLL�� ������ �ɼ��Դϴ�.

// D:\plugin ������ ���� SampleGraph.dll�� ������ �־� �ּ���.