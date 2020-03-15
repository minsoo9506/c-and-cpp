### 4.1 지역 변수, 범위, 지속 시간
- 변수가 사용되는 범위를 최소화한다. 꼭 필요한 만큼만 사용한다.
- 같은 영역 { } 안에 같은 이름의 정의는 불가능하다.
```c
#include <iostream>
using namespace std;

int main()
{
  int apple = 5;
  // 이 시점으로부터 apple 사용가능
  // 선언된 중괄호 { } 끝날때까지
  cout << apple << endl; // 5

  {
	apple = 1;
	cout << apple << endl; // 1

	int apple = 2;
	cout << apple << endl; // 2
  }

  cout << apple << endl; //1

  return 0;
}
```
- namespace
  - namespace 안에 namespace를 넣을 수 있다

```c
#include <iostream>
using namespace std;

// 같은 이름의 함수를 사용하기 위해서
// namespace를 통해 구분한다
namespace work1
{
    int a = 1;
    void doSomething()
    {
	     a += 3;
     }
}

namespace work2
{
    int a = 1;
    void doSomething()
    {
	     a += 5;
     }
}

int main()
{
    work1::a;
    work1::doSomething();

    work2::a;
    work2::doSomething();

    return 0;
}
  ```

### 4.2 전역 변수, 정적 변수, 내부 연결, 외부 연결
- 전역 변수는 최대한 사용하지 않는다.
- 뒤에 객체지향 배우면 전역 변수를 최소화할 수 있을 것이다.

```c
 #include <iostream>
using namespace std;

int value = 1;

int main()
{
    cout << value << endl; // 1
    int value = 0;
    cout << value << endl; // 0
    cout << ::value << endl; // 1
    // :: 전역연산자 사용
    return 0;
}
```

- 정적 변수 (static)
  - 디버깅시에 많이 사용
  - static을 붙여서 전역 변수를 만들면 외부 cpp 파일에서 접근불가

```c
 #include <iostream>
using namespace std;

void doSomething()
{
    // static
    // 원래 함수실행하고 끝나면 다시 초기화되야 하는데
    // 변수 a가 OS로 부터 받은 메모리가 유지
    // static int a; -> 이렇게 불가능 무조건 초기화
    static int a = 1;
    cout << ++a << endl;
}

int main()
{
    doSomething(); // 2
    doSomething(); // 3
    doSomething(); // 4

    return 0;
}
  ```

- internal linkage 는 해당 cpp 파일에서만 external linkage는 다른 cpp에서 접근 가능

```c
#include <iostream>
using namespace std;
// extrnal linkage
// 다른 파일(cpp)의 함수 사용하기 위해
// 또는 다른 파일에서 이걸 사용할 수 있도록
// foward declaration
// extern 생략가능
extern void doSometing;

int main()
{
    doSomething();

    return 0;
}
```

### 4.3 Using문과 모호성
- 코딩의 양이 많아지면 변수의 이름이 같아질수도 있고 namespace도 문제를 발생시키는 경우가 생기니 조심
- namespace를 전역에서 사용하는 것은 지양하자
```c
#include <iostream>
using namespace std;

namespace a
{
    int value = 1;
}
namespace b
{
    int value = 0;
}

int main()
{
    using namespace a;
    using namespace b;
    // cout << value << endl; 이런 경우는 error
    // 1. cout << a::value << endl; 가능
    // 2. 아니면 중괄호로 영역을 나눠서

    return 0;
}
```

### 4.4 Auto 키워드와 자료형 추론
- Auto 키워드
  - 자동으로 자료형 할당
  - 함수 return 값에서도 사용 가능

```c
#include <iostream>
using namespace std;

int add(int x, int y)
{   
    return x + y;
}

// 이렇게도 가능
// input prameter에는 auto 사용불가
//auto add(int x, int y)
//{
//	return x + y;
//}

// 강의 후반부에 input type도 맘대로
// 할 수 있도록 template 사용가능

int main()
{
    // 초기화를 안하면 당연히 auto 사용 불가
    auto a = 123;
    auto b = 123.0;

    // 함수의 return type을 몰라도 되는구나
    auto result = add(1, 2);

    return 0;
}
```

### 4.5 형변환 type conversion
- 특정 자료형을 갖는 변수가 그 범위를 넘어가는 값을 할당받는 경우 문제 발생
  - 예를 들어, double a 를 float b = a 하면 문제 발생
  - float -> int 인 경우는 소수점을 버림(반올림 아님)

```c
#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    // data type을 확인할때
    cout << typeid(4.0).name() << endl;

    int x = 123.0;
    cout << typeid(x).name() << endl;

    //numeric promotion
    // 별 문제 없음
    float a = 1.0f;
    double b = a;

    // numeric conversion
    int i = 30000;
    char c = i;

    // 문제발생
    cout << static_cast<int>(c) << endl; // 48

    // unsigned
    cout << 5u - 10; // -5가 아니라 이상한 수 나옴

    cout << 5u - 10u; // 얘도 이상
    // int보다 unsigned가 우선순위가 높아서
    // u 끼리 계산하면 int가 아니라 u 으로
    // 결과를 내려고 하니까 이상한 수
    // (unsigend는 - 표현 불가)

    return 0;
}
```
- 우선순위 (뒤로 갈수록 높음)
  - int, u int, long, u long, long long, u long long, float, double, long double

### 4.6 문자열 std::string
- 여기서는 전통적인 c 방법이외의 내용
- string
  -  string을 기본자료형처럼 쓸 수 있는 것은 string 라이브러리에 개발되어 있어서

``` c
#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main()
{
    // 문자열
    char arr_str[] = "hello world";

    // string (in c++)
    string my_hell = "hello world";

    cout << my_hell << endl;

    // 예시 프로그램
    cout << "Your name? : ";
    string name;
    // cin >> name; 이거는 띄어쓰기하면 이상해~
    // enter 칠 때까지 해당 line을 받는것
    std::getline(std::cin, name);

    cout << "Your age? : ";
    int age;
    cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    //enter 전까지 숫자 다 받도록
    cout << name << " " << age << endl;

    // string 끼리 더함
    string a("min");
    string b("soo");
    string name = a + b; // append
    cout << name << endl;

    // string 길이
    cout << a.length() << endl;

    return 0;
}
```

### 4.7 열거형 enumerated types
- enum
  - 일반적으로 원소이름은 대문자 (매크로랑 비슷한 느낌)
  - 각 원소별로 index 할당하는 느낌
  - enum들 안의 원소가 같은 이름이 있으면 컴파일이 안됨
  - 수동으로 할당할 때 같은 숫자 당연안됨
  - header 파일에 넣어서 여러 프로그램에서 써도 좋다
  - int로 저장되는 것 같지만 바로 호환은 어렵고 casting 해야 한다.

```c
#include <iostream>
#include <typeinfo>
using namespace std;

enum Color
{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_BLUE,
    COLOR_GREEN
};

enum Feeling
{
    HAPPY = 10, // 여기에 10 할당하면
    JOY,		// 11
    BLUE,		// 12
    TIRED		// 13
};

int main()
{
    Color paint = COLOR_BLACK;

    cout << paint << endl; // 0 나옴
    cout << COLOR_BLACK << endl; // 0 나옴
    cout << HAPPY << endl; // 10 나옴

    return 0;
}
  ```

### 4.8 영역 제한 열거형 (열거형 클래스)
- class를 사용하지 않고 enum만 사용하면 각 enum의 원소들이 int로 저장되기에 혼선발생 : 아예 다른 내용인데 == 같다가 성립하는 것과 같은 문제발생

```c
 #include <iostream>
using namespace std;

// enum class (c++11에서 도입)
enum class Color
{
    BLACK,
    RED
};

enum class Feeling
{
    HAPPY,
    JOY
};

int main()
{
    Color color = Color::BLACK;
    Feeling feeling = Feeling::HAPPY;

	// error 뜨고 컴파일이 안됨
	// 다른 class의 경우 비교를 막아준다
    if (color == feeling)
        cout << "same" << endl;

    return 0;
}
```

### 4.9 자료형에게 가명 붙여주기 type aliases
- 유지보수 장점
- 긴 type을 지정해야하는 경우 편해짐

```c
 #include <iostream>
using namespace std;

int main()
{   
    // distance_t 를 double type으로
    typedef double distance_t;

    // 그냥 double로 한 것과 같음
    // 예를 들어, 이 프로그램에서 거리는 double로
    // 사용하겠다 같은 경우
    // 유지보수도 편함 : distance_t를 float으로 바꾸겠다!
    // 이 경우 typedef 부분만 수정하면 됨
    distance_t home2work = 10;
    distance_t work2bus = 100;

    return 0;
}
```

### 4.10 구조체 struct
```c
 #include <iostream>
using namespace std;

struct Person
{
    double height;
    float weight;
    int age;
    string name;
};

void printPerson(Person ps)
{
    cout << ps.height << " " << ps.age << " " << ps.name << endl;
}

int main()
{
    // 초기화방법 1 : 순서대로 작성
    Person me{ 2.0, 100.0, 20, "minsoo" };

    // 2 이런식으로도 가능
    // me.age = 20
    printPerson(me);

    return 0;
}
```
- 구조체 안에 함수가 들어갈 수도 있다.
```c
strunt Person
{
    double height;
    int age;

    void print()
    {
      cout << height << " " << age << endl;
    }
}

int main()
{
  Person me{180, 20};
  me.print();
}
```
- 구조체안에 구조체가 들어갈 수도 있다
- 구조체 처음 만들때 초기화도 가능하다. (기본값을 넣어주는 것)
- 함수가 구조체를 return 할 수도 있다.

```c
 #include <iostream>
using namespace std;

struct Employee
{
    short id; // 2byte
    int age; // 4
    double wage; // 8
}; // 총 14 byte

int main()
{
    Employee emp1;

    cout << sizeof(emp1) << endl; // 근데 16 나옴

    // 이런 현상을 padding 이라고 하는데
    // 컴파일러가 효율적인 메모리할당을 위해
    // 2 + (2) + 4 + 8 = 16
    // 이렇게 2만 할당안하고 2를 추가로 padding해서
    // 크기가 16이라고 한다.
    // 추후에 이를 고려한 코딩이 효율적이다

    return 0;
}
```
