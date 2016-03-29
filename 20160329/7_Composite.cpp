// Composite ���� �ǽ�

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>	// getch();
using namespace std;


// ��� �޴��� ������ �θ�
class BaseFile
{
	string name;
public:
	BaseFile(string s) : name(s) {}
	~BaseFile() {}

	string getname() { return name; }

	// �ݵ�� getSize()�� �θ��� BaseFile�κ��� �;� �Ѵ�.
	// �θ� ���忡���� �������� ������ ����, �ڽ��� �ݵ�� ������ �Ѵٸ� ���� �����Լ��� ����.
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

// �Ʒ� Ŭ������ �̹� ������ �ٽ��Դϴ�.
class Folder : public BaseFile
{
	// ���� �޴� ������ ��Ͽ��� File�� Folder �� ���� �� �� �� �־�� �Ѵ�. -> ������ �θ� �ʿ�
	vector<BaseFile*> v;	// ����� �ռ�: �ڱ� �ڽ��� ������ �� �ִ� ����
public:
	Folder(string s) : BaseFile(s) {}
	// C++ ������Ʈ ������ ������ ��, �����ϰ� �ִ� ��� ��ü�� ���� �޸� ������ å���� �ִ�.
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
	// �Ʒ� �ڵ尡 ����ǵ��� Folder, File Ŭ������ ����� ������.
	Folder* fol1 = new Folder("ROOT");
	Folder* fol2 = new Folder("ROOT");

	File* f1 = new File("a.txt", 10);	// �̸�, ũ��
	File* f2 = new File("b.txt", 20);	// �̸�, ũ��

	// ���� ����
	fol2->addItem(f1);
	fol1->addItem(f2);
	fol1->addItem(fol2);
	cout << f2->getSize() << endl;		// 20
	cout << fol2->getSize() << endl;	// 10
	cout << fol1->getSize() << endl;	// 30

	delete fol1;
	// Composite ����
	//	- ��ü�� �ݵ�� ���� �����ؾ� �Ѵ�.
	//	- �׷��� �ڽ��� ������ ��� ��ü�� ���ؼ� �ѹ��� delete �����ϴ�.
}
