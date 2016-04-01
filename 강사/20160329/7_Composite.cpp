// 7_Composite

#include <string>
#include <vector>
#include <iostream>
using namespace std;
// 파일은 자신의 크기가 있지만, 폴더는 자신의 크기가 없습니다.
// 하지만 파일과 폴더 모두 크기를 구할 수 있습니다.

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
  // C++에서는 컴포지트 패턴을 구현할 때, 포함하고 있는 모든
  // 객체에 대한 메모리 해지의 책임이 있다.
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

// 1. File과 Folder의 공통의 부모 : Item
// 2. File과 Folder의 사용법 : getSize()
int main()
{
  // 아래코드가 실행되도록 Folder, File 클래스를 만들어 보세요
  Folder* fol1 = new Folder("ROOT");
  Folder* fol2 = new Folder("A");

  File* f1 = new File("a.txt", 10); // 이름, 크기
  File* f2 = new File("b.txt", 20);

  // 관계설정
  fol2->addItem(f1);
  fol1->addItem(f2);
  fol1->addItem(fol2);
  cout << f2->getSize() << endl; // 20
  cout << fol2->getSize() << endl; // 10
  cout << fol1->getSize() << endl; // 30

  // Folder f3("...");
  // fol1->addItem(&f3);

  delete fol1;
  // Composite 패턴
  // - 객체를 반드시 힙에 생성해야 한다.

}