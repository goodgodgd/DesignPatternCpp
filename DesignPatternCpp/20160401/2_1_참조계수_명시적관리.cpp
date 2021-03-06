// 객체의 수명을 참조 계수로 관리하는 경우가 많습니다.
// 객체를 공유하는데 효과적인 방법
 
#include <iostream>
using namespace std;

// 명시적으로 참족 계수를 관리하는 예제
class Image
{
	int mCount;
public:
	Image() : mCount(0) {}
	~Image() { cout << "이미지 파괴" << endl; }

	void addRef() { ++mCount; }		// 참조 계수 증가
	void release()					// 참조 계수 감소
	{
		if (--mCount == 0)	// 참조 계수가 0되면 자신 파괴
			delete this;
	}
};

int main()
{
	Image* p1 = new Image;	// 규칙1. 객체를 만들면 참조 계수 증가
	p1->addRef();

	Image* p2 = p1;			// 규칙2. 포인터를 복사하면 참조 계수 증가
	p2->addRef();

	p1->release();			// 규칙3. 객체 포인터 사용 후 참조 계수 감소
	//p2->release();		// release 하지 않으면 자원누수 발생!!
}
