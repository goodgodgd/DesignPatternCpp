// 인라인 함수와 함수 포인터의 이야기
// cl 4_함수와전략2.cpp /FAs /Ob1

// inline : 최적화 명령입니다. /Ob1

// 1. 인라인 치환은 컴파일 시간 문법입니다.
// 2. 인라인 함수라도 함수 포인터에 담아서 호출하면 인라인 치환 될 수 없다.
//   (함수 포인터는 결국 변수이다. 실행 시간에 변경될 수 있다.)

       int add1(int a, int b) { return a + b; }
inline int add2(int a, int b) { return a + b; }

int main()
{
  int n1 = add1(10, 20);   // 호출
  int n2 = add2(10, 20);   // 치환

  int(*f)(int, int) = &add2;
  // if (/...)
  //   f = &add1;

  f(10, 20); // 호출? 치환?

}