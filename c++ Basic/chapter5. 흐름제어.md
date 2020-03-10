### 5.1 제어 흐름 개요 control flow

- 순서도 Flow chart
- exit : 프로그램 종료, 중단
- return 으로도 끝낼수 있다

```c
#include <iostream>
#include <cstdlib> //exit
using namespace std;

int main()
{
	~~
    // 프로그램 종료
    // 중단
    exit(0);
	~~
}
```

### 5.2 조건문 if

- if 문 뒤에 문장이 1개면 {} 생략가능

```c
#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;

    if (x > 10)
	   cout << x << " is greater than 10" << endl;
    else
	   cout << x << " is not greater than 10" << endl;  

    return 0;
}
```
- if 조건에서 0이 아니면 true
- if 문 안에 if 문 더 넣을 수 있으나 else if 로 하는 것을 추천 (너무 깊으면 코드를 보기 어렵다)
- 헷갈릴거 같으면 그냥 {} 를 사용하자

```c
#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;

    // int 문 안에서 초기화
    if (1)
        int x = 5; // 이 경우 x = 5 로 초기화 x
	// {} 가 생략되더라도
	// {int x = 5;} 으로 컴파일되기에 지역변수 scope
	cout << x << endl; // input 값 나옴

    // chaining // else if
    if (x > 10)
	cout << "x is greater than 10" << endl;
    else if (x < 10)
	cout << "x is less than 10" << endl;
    else
	cout << "x is 10. corret" << endl;

    //  
    int min(int x, int y)
    {
        if (x > y) return y;
        else	   return x;
        // 위와 같은 역할
        // return (x > y) ? y; x;
    }

    return 0;
}
```

### 5.3 switch-case

```c
#include <iostream>
using namespace std;

enum class Colors
{
    BLACK,
    WHITE,
    RED
};

void printColorName(Colors color)
{
    switch (color)
    {
    case Colors::BLACK:
        cout << "BLACK" << endl;
	      break;
    case Colors::RED:
        cout << "RED" << endl;
	       break;
    }
}

// 위에서 Colors::BLACK 이렇게 쓰기 귀찮
/*
void printColorName(Colors color)
{
	switch (static_cast<int>(color))
	{
	case 0:
		cout << "BLACK" << endl;
		break;
	case 1:
		cout << "RED" << endl;
		break;
	}
}
*/
int main()
{
    int x;
    cin >> x;

// 해당하는 숫자부터 끝까지 실행
    switch (x)
    {
    case 0:
        cout << "Zero";
    case 1:
        cout << "One";
    case 2:
        cout << "Two";
    }

// 해당하는 부분만 실행하고 싶으면 break
    switch (x)
    {
    case 0:
        cout << "Zero";
        break;
    case 1:
        cout << "One";
        break;
    case 2:
        cout << "Two";
        break;
    default : 	
        cout << "undefined input" << endl;
    }
    return 0;
}
```

- switch ( ) {여기에 int a; 같이 선언은 되는데 초기화는 불가능하다 초기화는 case 안에서 사용} : 근데 이렇게는 잘사용안함
- case 범위를 중괄호 {} 로 묶어도 된다
- case 부분을 indent해도 되고 안해도 된다

### 5.4 goto

- 별로 안쓴다
```c
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x;

tryagain:

    cout << "Enter non-negative number" << endl;
    cin >> x;

    if (x < 0.0)
        goto tryagain;

    cout << sqrt(x) << endl;

    return 0;
}
```

### 5.5 반복문 while

- 무한루프 조심
- count 역할의 변수를 unsigned로 사용하면 overflow가 발생할 수도 있다. 예를 들어, count-- 와 같이 줄어들다가 0이하의 수가 되면 overflow발생하고 while문이 무한루트가 될 수도 있다

```c
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "while-loop" << endl;
    // 몇번 작업했는지 세는 변수 필요
    // while 밖에 선언
    // 안에 쓰고 싶으면 static int count = 0; 이렇게
    int count = 0;

    while (count < 10) // 괄호안이 true면 {} 작동
    {
        cout << count << endl;
        count++;
    }

    // break 사용
    while (1)
    {
        cout << count << endl;
        count++;
        if (count == 10) break;
    }
    return 0;
}
```

### 5.6 반복문 do while
- while문과 다르게 처음에 한 번은 무조건 실행되고 조건 확인

```c
#include <iostream>
using namespace std;

int main()
{
    int selection;

    do
    {
        cout << "1.add" << endl;
        cout << "2.sub" << endl;
        cout << "3.mul" << endl;
    } while (selection <= 1 || selection >= 4);

    cout << "U selected " << selection << endl;

    return 0;
}
```

### 5.7 반복문 for
- for () 안에 여러 가지 변수를 한 번에 넣어서 사용할 수 있다 (초기화, 조건,변화) 모두 다수의 변수사용가능

```c
#include <iostream>
using namespace std;

int main()
{

    for (int count = 0; count < 10; ++count)
    {
    cout << count << endl;
    }
	// 실행순서
	// 0. int count = 0 맨 처음에만 실행
	// 1. 조건 확인 count < 10
	// 2. 조건이 맞는다면 {} 부분 실행 아니면 종료
	// 3. ++count 실행
	// 이제 1 ~ 3 반복

    return 0;
}
```

### 5.8 break, continue
```c
#include <iostream>
using namespace std;

void breakOrReturn()
{
    while (true)
    {
        char ch;
        cin >> ch;

        if (ch == 'b')
            break;
        if (ch == 'r')
            return;
	}

    cout << "Hello" << endl;
}

int main()
{
	// break
	// 는 for while 문을 나오는 역할
	// b를 입력하면 Hello 출력
	// r을 입력하면 그냥 함수가 끝남 Hello 출력 x
    breakOrReturn();

	// continue
    for (int i = 0; i < 10; ++i)
    {
		// 해당 조건 만족하면 continue 실행
		// 뒤에 나오는 반복문 skip (여기서는 홀수만 출력)
		// ++i 로 가서 다시 반복
         if (i % 2 == 0) continue;
            cout << i << endl
    }

    return 0;
}
```

- flag를 이용하는 예시 유용!!
```c
#include <iostream>
using namespace std;


int main()
{
    int count = 0;
    bool escape_flag = false;

    while (!escape_flag)
    {
        char ch;
        cin >> ch;

        cout << ch << " " << count << endl;
	count++;

	if (ch == 'x') escape_flag = true;
    }

    return 0;
}
```

### 5.9 난수 만들기
