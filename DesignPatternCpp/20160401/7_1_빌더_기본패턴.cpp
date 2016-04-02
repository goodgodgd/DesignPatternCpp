// 빌더: 같은 공정이지만 다른 표현의 객체를 생성할 때 
// 축구게임을 만들 때, 선수마다 머리색, 유니폼, 신발 등이 다르다.
// 캐릭터 생성과정을 캡슐화해보자.

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

// 다양한 나라의 빌더를 제공합니다.
class Korean : public IBuilder
{
	string c;
public:
	virtual void makeHat()	{ c += "삿갓"; }
	virtual void makeShoes()	{ c += "짚신"; }
	virtual void makeUniform()	{ c += "한복"; }
	virtual string getResult()  {	return c;	}
};

class American : public IBuilder
{
	string c;
public:
	virtual void makeHat()	{ c += "야구모자"; }
	virtual void makeShoes()	{ c += "구두"; }
	virtual void makeUniform()	{ c += "양복"; }
	virtual string getResult()  { return c; }
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
		pBuilder->makeShoes();
		pBuilder->makeUniform();

		return pBuilder->getResult();
	}
};

int main()
{
	Korean korean;
	American american;
	Director director;

	director.setBuilder(&korean);
	cout << director.construct() << endl;

	director.setBuilder(&american);
	cout << director.construct() << endl;
}
