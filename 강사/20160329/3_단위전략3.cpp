// 3_단위전략3
// https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-6-of-n

// mr.stl stl lecture - Google
// cppcon.org
// - github
// - youtube
#include <iostream>
#include <string>
using namespace std;

class my_traits : public char_traits<char>
{
public:
  static bool compare(const char* a, const char* b, size_t sz)
  {
    return strcmpi(a, b);
  }
};


// basic_string
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