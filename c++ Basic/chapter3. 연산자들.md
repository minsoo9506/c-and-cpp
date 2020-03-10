### 3.1 연산자 우선순위와 결합법칙
- 우선순위가 애매하거나 잘 모르겠다고 생각하면 괄호를 사용하자. (숙달되기 전까지)

### 3.2 산술 연산자 arithmetic operator
- x = x + y 와 x += y 가 같다.

### 3.3 증감 연산자 increment decrement operator
```c
#include <iostream>

using namespace std;

int main()
{

  int x1 = 4;
  int x2 = 4;

  int y = ++x1;
  int z = x2++;

  cout << y << endl; // 5
  cout << z << endl; // 4

  // ++ 또는 -- 가
  // 앞에 붙으면 먼저 증감하고 할당
  // 뒤에 붙으면 먼저 할당하고 증감

  return 0;
}
```

### 3.4 sizeof, 쉼표(,) 연산자, 조건부 연산자
- sizeof operator
  - 함수가 아니라 operator 이다
  - 데이터 형의 크기를 알고 싶을 때 사용
  - 단위는 byte로 보여준다

- comma operator
  - 인자들은 구분하는 comma와 헷갈리지말자
  - comma operator는 operator 우선순위가 제일 낮다
  - 주로 for문에서 간편하게 코딩하기 위해 사용한다

- conditional operator
  - arithmetic if 라고도 불린다
  - 조건이 복잡할 떄는 사용하지 말자

```c
#include <iostream>

using namespace std;

int main()
{
  // sizeof
  float a;

  cout << sizeof(float) << endl;
  cout << sizeof(a) << endl;
  cout << sizeof a << endl; // 변수는 괄호생략가능

  // comma operator
  int x = 3;
  int y = 10;
  int z = (++x, ++y);
  cout << z << endl; // 11 로 나옴
  // comma operator는 아래와 같은 역할
  ++x;
  ++y;
  int z = y;

  //conditional operator
  bool onSale = true;
  const int price = (onSale == true) ? 10 : 100;
  cout << price << endl;

  return 0;
}
```

### 3.5 관계 연산자 relation operator
- 실제로 같은 값이여도 컴퓨터는 다르다고 (오차때문에 상당히 근소한 차이) 생각할 수도 있다. 이럴 때는 epsilon = 1e-10 과 같이 오차의 범위를 정한 뒤 , "이 차이보다 크면 다르다" 라고 판단하도록 코딩하자

### 3.6 논리 연산자 logical operator
- ! : not
- && : and
- || : or
- xor은 연산자는 없다
- and가 or 보다 우선순위가 높다
- 논리연산자의 우선순위에 대해 주의! 괄호를 잘 이용하자.
```c
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  // if 조건안에 &&가 있을때
  // 왼쪽이 false면 오른쪽을 계산안한다
  int x = 2;
  int y = 2;

  if (x == 1 && y++ = 2)
  {
    //do something
  }

   cout << y << endl; // 3이 아니라 2가 나옴

   return 0;
}
```

### 3.7 이진수 binary numbers

### 3.8 비트단위 연산자 bitwise operator, 컴퓨터 작동원리
- 속도 최적화에 주로 사용
- bitwise 연산자
  - \<< : left shift
  - \>> :  right shift
  - cout에서의 그 기호랑은 다르다
  - ~ (not), & (and), | (or) , ^ (xor)

  ```c
  #include <iostream>
  #include <bitset> //2진수로 바꿔서 출력

  using namespace std;

  int main()
  {
    // bitwise 연산자

    unsigned int a = 3;
    cout << std::bitset<8>(a) << endl;
    // a를 2진수로 보여줌

    unsigned int b = a << 1;
    // 2진수 숫자 옆으로 한칸 밀기
    cout << std::bitset<8>(b) << endl;
    // 0011 이었던 a를 한 칸 밀어서 b가 0110 됐다는 의미
    // 이 의미는 즉, b = a << n 는 b = a * 2^n 의미
    // right shift는 반대로 나눠주는 것
    // 그냥 곱하기보다 shift operator가 훨씬 빠르다

    unsigned int x = 0b1100;
    unsigned int y = 0b0110;

    cout << std::bitset<4>(x & y) << endl;
    cout << std::bitset<4>(x | y) << endl;
    cout << std::bitset<4>(x ^ y) << endl;
    // 각 자리수마다 비교한다

    return 0;
  }
    ```

### 3.9 비트 플래그, 비트 마스크 bit flags, bit masks

```c
#include <iostream>
#include <bitset>

using namespace std;

int main()
{

  // bit flags
  // item 8개가 있는지 없는지 check하고 싶다
  // bool type 8개가 아니라 char로 해보자

  const unsigned char opt0 = 1 << 0;
  const unsigned char opt1 = 1 << 1;
  const unsigned char opt2 = 1 << 2;
  cout << bitset<8>(opt0) << endl;
  cout << bitset<8>(opt1) << endl;
  cout << bitset<8>(opt2) << endl;

  unsigned char items_flag = 0;
  cout <<"No item " << bitset<8>(items_flag) << endl;

  // item0 obtained
  items_flag |= opt0;
  cout << "item0 obtained " << bitset<8>(items_flag) << endl;

  // item2 obtained
  items_flag |= opt2;
  cout << "item2 obtained " << bitset<8>(items_flag) << endl;

  // item2 lost
  items_flag &= ~opt2;
  cout << "item3 lost " << bitset<8>(items_flag) << endl;

  // has item 1?
  if (items_flag & opt1) { cout << "has item1" << endl; }
  else { cout << "no item1" << endl; }

  // obtain item 1,2
  items_flag |= (opt1 | opt2);
  cout << "item1,2 lost " << bitset<8>(items_flag) << endl;

  return 0;
}
```
