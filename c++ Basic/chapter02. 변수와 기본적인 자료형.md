### 2.1 기본 자료형 소개
- 아래의 byte크기는 최소 크기!
- char : 1 byte (문자 하나)
- (signed) int types
  - signed char : 1 btye (char가 컴퓨터에서는 int로 다 계산)
  - *signed* short *int* : 2 byte
  - *signed* int : 2 byte (대부분 4byte로 사용)
  - *signed* long *int* : 4 byte
  - *signed* long long *int* : 8 byte
- (unsigned) int types
  - unsigned char : 1 btye (char가 컴퓨터에서는 int로 다 계산)
  - unsigned short *int* : 2 byte
  - unsigned *int* : 2 byte
  - unsigned long *int* : 4 byte
  - unsigned long long *int* : 8 byte
- Floating-point types
  - float
  - double
  - long double types
- Boolean type
- Void type
- NULL pointer

```c
bool bvlaue = false;
char chvalue = 65;
float fvalue = 3.1415f; //float은 f를 마지막에 붙임
double dvalue = 3.1415;

 //modern c++에서 새로 생김 : auto
 //알아서 컴파일할 때 type 할당
auto avalue = 3.1415; //double
auto avalue = 3.1415f; //float
```
- sizeof(변수) : 변수 type의 size를 찾는다.
```c
int i = 123 // copy initialization
int a(123); // direct initialization
int b{ 123 }; //uniform initialization : 나중에 객체지향에서 배움

// casting
int i = (int)3.1533 // 형변환

// 여러개 선언 가능(같은 type만)
int a, b, c;
int k = 1,  m = 100, n = 17;
```

### 2.2 정수형
```c
int i = 1;
// int는 4byte = 32bit
// 여기서 맨 앞은 부호를 나타내는 것으로 사용
//그래서  - 2^31 ~ + 2^31 의 값을 가진다.

unsigned i = 1;
//unsigned의 경우는 0 ~ +2^32
```
- 해당 정수형을 통해 표현할 수 있는 숫자를 넘어가는 것을 **overflow** 라고 한다. 그래서 우리는 특정 type이 표현할 수 있는 정도를 알고 있어야 한다. 무조건 큰 type을 사용하면? 당연히 낭비하는 것!
- 정수끼리 사칙연산은 정수로만 답이 나온다. 나머지가 버려진다.

### 2.3 c++11 Fixed-width Integers (고정 너비 정수)
```c
#include <iostream>

int main()
{
    using namespace std;
    // 여기서 숫자는 bit를 의미
    std::int16_t i(5); // 16bit인 int, short
    std::int8_t myint = 65; // signed char

    cout << myint << endl;

    std::int_fast8_t fi(5); // 가장 빠른 것 ,signed char
    std::int_least64_t fl(5); // 최소 64bit, long long

    return 0;
}
```

### 2.4 void type (무치형)
```c
// 함수선언 시
void function(void){} // ()안의 void는 생략가능

// 포인터
void *my_void;

// void casting
int i = 123;
float f = 123.4f
// data type은 달라도 주소를 표현하는 크기는 같아서 어떤 형으로도 casting 가능
// 여기서는 void형으로 casting
my_void = (void*)&i
my_void = (void*)&f
```

### 2.5 Floating Point Numbers (부동소수점 수)
- 형 type
  - float  : 최소 4byte (주로 4byte)
  - double : 최소 8byte (주로 8byte)
  - Long double : 최소 8byte (주로 8,12,16byte)
```c
#include <iostream>
#include <limits>

int main()
{
  using namespace std;
  // 여기서는 double과 long double이 같은 크기라서
  //min max lowest 값이 같음(표현할수있는 범위)
  cout << numeric_limits<float>::max() << endl;
  cout << numeric_limits<double>::max() << endl;
  cout << numeric_limits<long double>::max() << endl;
  // min : 가장 작은 수의 절댓값
  cout << numeric_limits<float>::min() << endl;
  // lowest : 가장 작은 수
  cout << numeric_limits<double>::lowest() << endl;

  return 0;
}
```
```c
#include <iostream>
#include <iomanip>
#include <limits>

int main()
{
using namespace std;

cout << 1.0 / 3.0 << endl;
cout << std::setprecision(9); //뒤 소수점표현 길이 지정
//precision을 높일수록 실제 computer가 갖고 있는 수를 알 수 있다
cout << 1.0 / 3.0 << endl;

float f(123456789.0f);
cout << f << endl; //123456792 으로 나옴
// computer가 이진수로 계산하기에 이처럼 오차존재

return 0;
}
```
- std::isnan // 현재 값이 nan인지
```c
#include <iostream>
//#include <iomanip>
#include <limits>
#include <cmath>


int main()
{
using namespace std;

double zero = 0.0;
double posinf = 2.0 / zero;
double nan = zero / zero;

cout << nan <<" " << std::isnan(nan) << endl;
cout << posinf << " " << std::isinf(posinf) << endl;
// posinf 결과는 +inf 로 나온다

return 0;
}

```

### 2.6 Boolean 자료형과 조건문 if
- computer 입장에서는 true : 1, false : 0 결국 숫자임

```c
#include <iostream>

int main()
{
using namespace std;

bool b1 = true;
bool b2 = false;

// 1 0 으로 출력됨
cout << b1 << endl;
cout << b2 << endl;

// true false로 출력하고 싶으면
cout << std::boolalpha;
//cout << std::noboolalpha; 원상복귀
cout << b1 << endl;
cout << b2 << endl;

return 0;
}
```
- ! : not 의미
- && : and 의미. 둘 다 true이면 true
- || : or 의미. 둘 중 하나이상 true이면 true
- == :  등호 의미, 같으면 true

```c
#include <iostream>

int main()
{
    using namespace std;

    if (true)
        cout << "This is true " << endl;
    else
        cout << "This is false" << endl;
    // 한줄실행인 경우, {} 안써도 됨
    // 두줄이상인 경우, {} 꼭 써야됨

    // if() 에서 () 안에 0이 아닌 숫자가 true 의미
    // 0을 넣으면 false 의미

    return 0;
}
```

### 2.7 문자형 char type

 ```c
 #include <iostream>

int main()
{
	using namespace std;

	char c1(65); //char c1 = 65; 랑 같음
	char c2('A'); //한글자는 '', 문자열은 "" 사용

	cout << c1 << endl; // 결과는 A 로 나온다

	// c style casting
	cout << (char)65 << endl;
	cout << (int)'A' << endl;

	// cpp style casting
	cout << char(65) << endl;
	cout << int('A') << endl;

	// 나중에 다시 배움
	cout << static_cast<char>(65) << endl;
	cout << static_cast<int>('A') << endl;

	// 기능적으로는 다 같음

	return 0;
}
 ```
 - \n 와 endl 의 차이 : (몇몇 특수한 상황에서) \n는 버퍼에 있는 것을 출력하지 않는데 endl은 버퍼의 내용까지 모두 출력한다.
 - \t : tab (주로 4칸) 띄어준다.
 - 추가적으로 \n, \t 같은 경우 이는 한글자로 취급된다.

### 2.8 literal constants (리터럴 상수)
```c
float pi = 3.14f; //여기 3.14f 가 literal constants 인 것이다

//Decimal : 0 1 2 3 4 5 6 7 8 9 10
//Octal : 0 1 2 3 4 5 6 7 10 11 12 13
//Hexa : 0 1 2 3 4 5 6 7 8 9 A B C D E F 10
int x_octal = 011; // 숫자앖에 0을 붙임
int x_hexa = 0xF; // 0x 를 붙임

// c++14 부터 binary literal 가능
int x = 0b1010; // 0b 를 붙임
int x = 0b101'0111'1011 // ' : 읽기 편하게 사용할 수 있음 컴파일러가 무시함
```

### 2.9 symbolic constants (심볼릭 상수)
- const 를 사용한다
```c
#include <iostream>

using namespace std;

void printnum(const int my_number)
{
    // 위처럼 파라미터에 const 붙이면
    // 함수 내부에서 변경 x
    cout << my_number << endl;
}

int main()
{
    const double gravity = 9.8;
    // const 하면 값을 바꿀 수 없음
    // 물론 억지로 바꾸는 방법은 있지만 노노!!

    double const gravity = 10; // 이렇게도 가능
    // 근데 나중에 둘의 차이를 배움

    return 0;
}
```
- constexpr
```c
#include <iostream>

using namespace std;

int main()
{
    // 1
    const int my_const(123);

    // 2
    int num;
    cin >> num;
    const int special_num(num);

    // 1번과 2번은 차이 :
    // 1번은 컴파일할 때, 123으로 결정되고
    // 2번은 num에 따라서 달라진다(런타임에 결정)

    // 이를 구분할 수 없었는데 c++11에서
    // constexpr 등장
    constexpr int my_const(123);
    // 1번의 경우 이처럼 사용(컴파일시에 결정)
    // 2번의 경우 에러남

    return 0;
}
```
- (**주의**) 추가로 c언어에서는 메크로(#define ~)를 사용하는데 c++ 에서는 거의 사용 안한다고 한다. 메크로 말고 const로 선언하자.
- 그래서 header 파일에 const를 몰아서 작성하고 const를 바꿔야하는 상황이 오면 간편하게 header 파일만 수정하면 된다.
