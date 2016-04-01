// ����

// �౸������ ����ٰ� ���� ��, �������� �Ӹ�, ��, �ٸ� �� ������ �Ӹ���, ������, �Ź� ���� �ٸ���.

#include <iostream>
#include <string>
using namespace std;

struct IBuilder
{
	virtual void makeHat() = 0;
	virtual void makeUniform() = 0;
	virtual void makeShoes() = 0;
	virtual string getResult() = 0;

	virtual ~IBuilder();
};

class Director
{
	IBuilder* pBuilder;
public:
	void setBuilder(IBuilder* p) { pBuilder = p; }

	// �Ʒ� �Լ��� ĳ���͸� �����ü� �����ϴ� �Լ��Դϴ�.
	string construct()
	{
		pBuilder->makeHat();
		pBuilder->makeShoes();
		pBuilder->makeUniform();

		return pBuilder->getResult();
	}
};

// �پ��� ������ ������ �����մϴ�.
class Korean : public IBuilder
{
	string c;
public:
	virtual void makeHat()	{ c += "��"; }
	virtual void makeShoes()	{ c += "¤��"; }
	virtual void makeUniform()	{ c += "�Ѻ�"; }
	virtual string getResult()  {	return c;	}
};

class American : public IBuilder
{
	string c;
public:
	virtual void makeHat()	{ c += "�߱�����"; }
	virtual void makeShoes()	{ c += "����"; }
	virtual void makeUniform()	{ c += "�纹"; }
	virtual string getResult()  { return c; }
};

int main()
{
	Korean korean;
	American ameriacan;
	Director director;

	director.setBuilder(&korean);
	cout << director.construct() << endl;


	director.setBuilder(&american);
	cout << director.construct() << endl;
}

