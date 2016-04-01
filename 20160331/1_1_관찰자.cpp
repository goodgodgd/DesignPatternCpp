// 예시: 엑셀에서 데이터를 기반으로 표를 그리면 데이터가 변했을 때 즉각적으로 표가 변경됨
// 구현방법1: 각각의 그래프가 주기적으로 표를 확인
// 구현방법2: 표가 바뀌었을 때 그래프에 알려줌 - poll, push
// SW 아키텍쳐에서 중요한 역할
// MVC (Model - View - Controller) 모델
//		------------   ----------
//		  옵저버			 어댑터

#include <iostream>
#include <vector>
using namespace std;

// 1. 관찰자 패턴 개념: 하나의 이벤트를 여러 객체에 전파하는 패턴.

// 관찰자 인터페이스
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};

class PieGraph : public IObserver
{
public:
	virtual void onUpdate(void* p)
	{
		int* data = static_cast<int*>(p);
		cout << "********** Pie Graph **********" << endl;
		for (int i = 0; i < 5; ++i)
			cout << i << " : " << data[i] << endl;
	}
};

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

#if 0
// 관찰의 대상: 표 - (모델이라고 부릅니다)
class Table
{
	int data[5];
	vector<IObserver*> v;
public:
	Table() { memset(data, 0, sizeof(data)); }
	void attach(IObserver* p) { v.push_back(p); }
	void detach(IObserver* p) {}

	void notify(void* p)
	{
		// auto를 쓰는 경우: 개념이 중요할 때
		// vector<IObserver*>::iterator a = v.begin();
		// auto를 쓰지 않는 경우: 간혹 int, long, double, float 등 타입이 중요할 때는
		// built-in type에 대해선 잘 쓰지 않고 객체에 대해서 많이 쓴다.

		for (IObserver* e : v)	// for (auto e : v) 도 가능
			e->onUpdate(p);
	}

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
#endif


// 문제점: 모델의 (테이블의) 데이터 형식, 길이 등을 알고 있어야 한다.
// 모든 Table(관찰의 대상)의 특징은 항상 동일하다.
// -> 부모로 제공하자.

// 정리: 달라지는 것은 가상함수화 해서 자식이 변경,
//		공통적인 것은 부모 클래스로 만들어서 제공
// 처음부터 계층적인 설계를 하기 보다는 짜면서 중복되는 부분을 계층구조를 만들어 나간다.

class Subject
{
	vector<IObserver*> v;
public:
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

	PieGraph pg;
	BarGraph bg;
	table.attach(&pg);
	table.attach(&bg);

	table.edit();
}
