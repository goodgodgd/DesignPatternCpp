// Composite 패턴 실습

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>	// getch();
using namespace std;


// 모든 메뉴의 공통의 부모
class BaseFile
{
	string name;
public:
	BaseFile(string s) : name(s) {}
	~BaseFile() {}

	string getname() { return name; }

	// 반드시 getSize()는 부모인 BaseFile로부터 와야 한다.
	// 부모 입장에서는 구현해줄 내용이 없고, 자식이 반드시 만들어야 한다면 순수 가상함수가 좋다.
	virtual int getSize() = 0;
};

class File : public BaseFile
{
	int size;
public:
	File(string s, int sz) : BaseFile(s), size(sz) {}

	int getSize()
	{
		return size;
	}
};

// 아래 클래스가 이번 예제의 핵심입니다.
class Folder : public BaseFile
{
	// 서브 메뉴 아이템 목록에는 File과 Folder 두 가지 다 들어갈 수 있어야 한다. -> 공통의 부모 필요
	vector<BaseFile*> v;	// 재귀적 합성: 자기 자신을 포함할 수 있는 설계
public:
	Folder(string s) : BaseFile(s) {}
	// C++ 컴포지트 패턴을 구현할 때, 포함하고 있는 모든 객체에 대한 메모리 해지의 책임이 있다.
	~Folder()
	{
		for (size_t i = 0; i < v.size(); i++)
			delete v[i];
	}

	void addItem(BaseFile* p) { v.push_back(p); }

	int getSize()
	{
		int total = 0;
		for (size_t i = 0; i < v.size(); i++)
			total += v[i]->getSize();
		return total;
	}
};


int main()
{
	// 아래 코드가 실행되도록 Folder, File 클래스를 만들어 보세요.
	Folder* fol1 = new Folder("ROOT");
	Folder* fol2 = new Folder("ROOT");

	File* f1 = new File("a.txt", 10);	// 이름, 크기
	File* f2 = new File("b.txt", 20);	// 이름, 크기

	// 관계 설정
	fol2->addItem(f1);
	fol1->addItem(f2);
	fol1->addItem(fol2);
	cout << f2->getSize() << endl;		// 20
	cout << fol2->getSize() << endl;	// 10
	cout << fol1->getSize() << endl;	// 30

	delete fol1;
	// Composite 패턴
	//	- 객체를 반드시 힘에 생성해야 한다.
	//	- 그래야 자신이 포함한 모든 객체에 대해서 한번에 delete 가능하다.
}
