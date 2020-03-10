### 1.4 입출력 스트림과의 첫 만남 cin, cout
```c
#include <iostream>

int main()
{
  // cout
    int x = 1024;
    std::cout << "Hello world!" << std::endl;
    std::cout << "I love u!\n";
    std::cout << "I love u!"; // 이렇게 하면 줄바꿈 x
    std::cout << " x is" << x << std::endl;
    std::cout << "abc" << "\t" << "tab!" << std::endl;
    std::cout << "ab" << "\t" << "ctab!" << std::endl;

    using namespace std; // 이렇게 선언하면 {} 안에서 std 빼도 가능
    cout << "Hello world!" << endl;

  // cin
    int y;
    cin >> y; // 사용자가 직접 넣는다
    cout << "Your input is " << y << endl;

    return 0;
}
```


### 1.5 함수와의 첫 만남
- python과는 다르게 함수안에 함수는 선언 불가
- 단, 함수안에 class 선언이 가능하기에 문제는 없음!
```c
#include <iostream>

using namespace std;

int addTwoNumbers(int num_a, int num_b) // 받거나 주는 인자가 없는 경우도 있음 : void 사용
{
    int sum = num_a + num_b;
    return sum;
	// return 뒤에 나오는 코드는 무시됨
}

int main()
{
    cout << addTwoNumbers(1, 2) << endl;
    cout << addTwoNumbers(1, 3) << endl;
    return 0;
}
```

### 1.6 키워드와 식별자(identifier) 이름짓기
- 키워드 : 이미 해당 언어에서 이름이 지어진 것. 변수, 함수 만들 때 해당 키워드랑 이름을 같을 수 없음.
- 변수는 대문자를 잘 안씀, 매크로는 주로 대문자 사용.
- 함수이름을 길게 하기 보다는 주석을 달기.

### 1.7 지역범위
```c
#include <iostream>
using namespace std;

int main()
{
    int x(0); // x = 0 랑 같은 의미
    {
    int x(1); // 지역변수라서 똑같은 이름의 식별자 사용해도 ok
    cout << x << endl; // 1 반환
    // x = 1; 이렇게 하면 {} 밖에서 선언한 x의 값을 바꾸는 것!
    }
    cout << x << endl; // 0 반환
    return 0;
}
```

### 1.8 연산자와의 첫 만남
```c
#include <iostream>
using namespace std;

int main()
{
    int x = 2; // x is a variable, 2 is a literal

    // (unary) 단항연산자
    cout << -x << endl;

    // (binary) 이항연산자 : 연산자 양 옆에
    cout << x + 2 << endl;

    // c++ 유일한 삼항연산자
    int y = (x > 0) ? 1 : 2; // x > 0 이면 1, 아니면 2 할당

    return 0;
}
```
### 1.9 기본적인 서식 맞추기

### 1.10 선언과 정의의 분리
```c
#include <iostream>
using namespace std;

/* 컴파일러는 위에서 부터 읽기에
 * 아예 definition을 main 앞에 쓰던가
 * forward declaration을 해주면 된다 */

int add(int a, int b); // forward declaration

int main()
{
    cout << add(1, 2) << endl;
    return 0;
}

// definition
int add(int a, int b)
{
    return a + b;
}
```

### 1.11 헤더파일 만들기

### 1.12 헤터 가드가 필요한 이유
- header 파일에 #pragma once 넣으면 된다고 생각하면 됨.
```c
#pragma once // 이것이 아래의 것과 같은 의미

// 즉, MY_F가 include 할 때 중복되서 사용되지 않도록 하는 방법
#ifndef MY_F
~~
#endif
```
### 1.13 네임스페이스 명칭 공간
```c
#include <iostream>

namespace MySpace1
{
	//namespace안에 또 namespace를 넣을 수도 있다

    int doSomething(int a, int b)
    {
        return a + b;
    }
}

int doSomething(int a, int b)
{
    return a * b;
}

using namespace std;

int main()
{
    cout << doSomething(3,4) << endl; // 12

    // using namespace MySpace1 하면 마찬가지로 생략가능!!
    cout << MySpace1::doSomething(3,4) << endl; // 7

    return 0;
}

```
### 1.14 전처리기와의 첫 만남
