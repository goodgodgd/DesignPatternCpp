// eYbJ

#include <iostream>
#include <string>
using namespace std;

// Stephan T. Lavavej - STL �����ڷ�
// MS���� ���ϸ鼭 STL ������
// https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Introduction-to-STL-with-Stephan-T-Lavavej
// cppcon.org - C++ conference�� ���� ��� �ڷ� ����
// 14����� C++ ���۷������� ����,  MS���� �ֵ� - ������� github ����

// vector, list���� STL�� ����ȭ ��å�� ����.
// ����ȭ�� ���� ���� ����� lock�� �ʿ���� lock free container�� ����ϴ� ���� ����.
// TBB: lock free container ����, but ���̼��� �̽�
// boost: ���� ��� ����

// ���� ���� ���� �̽�: ��ü ���� -> Funtional Frame, C++���� ������

// string �� typedef��
// typedef basic_string<char, char_traits<char>, allocator<char> > string;
// char_traits: ���ڿ� �񱳱��
// allocator: �޸� �Ҵ�

class my_traits : public char_traits < char >
{
public:
	// document�� ��ӵ� ����
	static bool compare(const char* a, const char* b, size_t sz)
	{
		return strcmpi(a, b);
	}
};

// ��ҹ��ڸ� �������� �ʴ� �� �����ڸ� ���� �ʹ�.
// ���� string ��ü�� �������� �ʾƵ� 
typedef basic_string<char, my_traits> mystring;

int main()
{
	mystring s1 = "abcd";
	mystring s2 = "ABCD";

	if (s1 == s2)
		cout << "same" << endl;
	else
		cout << "not same" << endl;
}
