// 7_Composite

#include <string>
#include <vector>
#include <iostream>
using namespace std;
// ������ �ڽ��� ũ�Ⱑ ������, ������ �ڽ��� ũ�Ⱑ �����ϴ�.
// ������ ���ϰ� ���� ��� ũ�⸦ ���� �� �ֽ��ϴ�.

class Item
{
  string name;
public:
  Item(string s) : name(s) {}
  virtual ~Item() {}

  virtual int getSize() = 0;
};

class File : public Item
{
  int size;
public:
  File(string n, int s) : Item(n), size(s) {}
  virtual int getSize() { return size; }
};

class Folder : public Item
{
  vector<Item*> v;
public:
  Folder(string n) : Item(n) {}
  // C++������ ������Ʈ ������ ������ ��, �����ϰ� �ִ� ���
  // ��ü�� ���� �޸� ������ å���� �ִ�.
  ~Folder() {
    for (int i = 0; i < v.size(); ++i)
      delete v[i];
  }

  void addItem(Item* p) { v.push_back(p); }

  int getSize()
  {
    int sum = 0;
    for (int i = 0; i < v.size(); ++i)
      sum += v[i]->getSize();

    return sum;
  }
};

// 1. File�� Folder�� ������ �θ� : Item
// 2. File�� Folder�� ���� : getSize()
int main()
{
  // �Ʒ��ڵ尡 ����ǵ��� Folder, File Ŭ������ ����� ������
  Folder* fol1 = new Folder("ROOT");
  Folder* fol2 = new Folder("A");

  File* f1 = new File("a.txt", 10); // �̸�, ũ��
  File* f2 = new File("b.txt", 20);

  // ���輳��
  fol2->addItem(f1);
  fol1->addItem(f2);
  fol1->addItem(fol2);
  cout << f2->getSize() << endl; // 20
  cout << fol2->getSize() << endl; // 10
  cout << fol1->getSize() << endl; // 30

  // Folder f3("...");
  // fol1->addItem(&f3);

  delete fol1;
  // Composite ����
  // - ��ü�� �ݵ�� ���� �����ؾ� �Ѵ�.

}