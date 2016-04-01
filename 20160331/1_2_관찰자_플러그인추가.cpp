// 기존 라이브러리로 제공되는 것에 새로운 기능을 추가하는 plug-in을 구현해보자
// 그래프 - DLL로 만들어보자!

// 플러그인의 원리
// BarGraph가 들어있는 모듈을 수정하지 않고
// SampleGraph(plugin)가 들어있는 DLL을 로드해서 기능추가 가능

#include <iostream>
#include <vector>
using namespace std;

#include "IObserver.h"
#include "ioacademy.h"
using namespace ioacademy;

// 1. 관찰자 패턴 개념: 하나의 이벤트를 여러 객체에 전파하는 패턴.

// IObserver.h 로 이동해야 합니다.
#if 0
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};
#endif

class BarGraph : public IObserver
{
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Bar Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

class Subject
{
	vector<IObserver*> v;
public:
	//------------------------------
	Subject()
	{
		// 1. 약속된 폴더의 모든 DLL을 열거한다.
		IoEnumFiles("D:\\plugin", "*.dll", LoadModule, this);	// LoadModule의 param으로 this 전달
	}

	// static 멤버 함수는 this가 없으므로 일반 함수 포인터와 시그니처가 동일하다.
	static int LoadModule(string name, void* param)
	{
		cout << name << endl;

		// 2. DLL을 로드한다.
		void* addr = IoLoadModule(name);	// gcc에서는 dlopen()로 so 파일을 동적로드 가능

		// 3. 약속된 함수를 찾는다.
		typedef IObserver* (*FP)();
		FP f = (FP)IoGetFunctionAddress(addr, "CreateGraph");	// void* 리턴하므로 캐스팅

		// 4. 객체 생성
		IObserver* p = f();

		// 5. SampleGraph를 관찰자로 등록한다.
		Subject* self = static_cast<Subject*>(param);	// this를 전달받아 객체의 메소드 호출
		self->attach(p);

		return 1;	// 0: 하나만 불러라. 1:모든 파일을 계속 열거해달라.
	}

	//------------------------------

	void attach(IObserver* p) { v.push_back(p); }
	void detach(IObserver* p) {}

	void notify(void* dat)
	{
		for (IObserver* e : v)	// for (auto e : v) 도 가능
			e->onUpdate(dat);
	}
};

// 관찰의 대상: 표 - (모델이라고 부릅니다)
class Table : public Subject
{
	int data[5];
public:
	Table() { memset(data, 0, sizeof(data)); }

	void edit()
	{
		while (1)
		{
			int index;
			cout << "index : ";
			cin >> index;
			cout << "data : ";
			cin >> data[index];

			// 모든 관찰자에 알려준다.
			notify(data);
		}
	}
};

int main()
{
	Table table;

	BarGraph bg;
	table.attach(&bg);

	table.edit();
}
