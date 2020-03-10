### 7.1 매개변수와 실인자의 구분
- parameter vs argument
```c
#include <iostream>
using namespace std;

// parameter 매개변수 x, y
int foo(int x, int y)
{
	return x + y;
}

int main()
{
	// argument 실인자 1, 3
	foo(1, 3);

	return 0;
}
```
### 7.2 값에 의한 전달 (call by value)
```c
#include <iostream>
using namespace std;

void dosomething(int y)
{
	cout << y << &y << endl;
}

int main()
{
	// 값 전달
	dosomething(5);
	// argument 5를 넣으면
	// 내부적으로 int y 가 선언되고
	// y 메모리에 5가 들어가면서 초기화되는 것

	// 변수 사용
	int x = 6;
	cout << x << &x << endl;
	dosomething(x);
	// x가 전달되는 것이 아니라
	// x가 갖고 있는 값 6이 전달(복사)
	// main에서 x 주소와 dosomething 로 찍은 주소가 다름
	// 근데 dosomething으로 내부변수 주소찍으면 항상같음

	// 따라서 함수 안에서 변수를 바꿔도
	// 함수밖에서 영향 없음
	// 그럼 영향 주고 싶으면? 뒤에서 배움

	return 0;
}
```

### 7.3 참조에 의한 인수 전달 (call by reference)
- 참조를 사용하면 상당히 유용
```c
#include <iostream>
using namespace std;

void addone(int &y)
{
	y = y + 1;
}

int main()
{
	int x = 5;
	cout << x << &x << endl; // 5, 주소도 같음
	addone(x);
	cout << x << &x << endl; // 6, 주소도 같음

	// 즉, 참조에 의한 호출은
	// 함수가 변수의 복사를 하는 것이 아니라
	// 그대로 변수 이용

	return 0;
}
```

```c
#include <iostream>
#include <cmath>
using namespace std;
// 함수 parameter에서 const 붙이는 것은 input이고
// const 없으면 이 값들이 output이겠구나~~ 예상가능
void getSinCos(const double degrees, double& sin_out, double& cos_out)
{
	static const double pi = 3.141592;
	double radians = degrees * pi / 180.0;
	sin_out = std::sin(radians);
	cos_out = std::cos(radians);
}

int main()
{
	double sin(0.0);
	double cos(0.0);
	// c,c++ 에서 함수의 return 값을 여러개
	// 못하는데 참조를 이용하면 여러개 return하는 것과 같은 역할
	getSinCos(30.0, sin, cos);

	return 0;
}
```
- 근데 참조의 단점도 있음
	- 함수 argument로 리터럴을 사용할 수 없음
	- 하지만 const 붙이면 가능
- 최근에는 const 거의 대부분 붙임

```c
void foo(int &x) // const int &x 하면 리터럴도 가능
{
	cout << x << endl;
}
int main()
{
	foo(6); // 리터럴 불가
	return 0;
}
```
- 포인터에 대한 참조

```c
// 포인터 타입의 참조변수
void foo(int*& prt) //
{
	cout << ptr << &ptr << endl;
}
int main()
{
	int x = 5;
	int * ptr = &x;
	// 아래 둘이 같은 결과
	cout << ptr << &ptr << endl;
	foo(ptr);

	return 0;
}
```

### 7.4 주소에 의한 인수 전달 (call by address)
```c
#include <iostream>
using namespace std;

// 포인터 타입의 참조변수
void foo(int* ptr)
{
	cout << ptr << " " << &ptr << endl;
}
int main()
{
	int value = 5;
	cout << value << " " << &value << endl;

	int* ptr = &value;
	// 포인터 변수도 변수!
	// 따라서 포인터 변수도 복사되서 들어감
	foo(ptr);
	foo(&value);

	foo(5); // 이거는 에러 발생
	// const 아무리 붙여도 못함

	return 0;
}
```
- const 사용
	- parameter에 const 붙이면 함수 안에서 de referencing으로 값을 못 바꾼다
```c
void foo(const int *ptr)
{
	* ptr = 10; // 불가
}
```

```c
#include <iostream>
#include <cmath>
using namespace std;

void getSinCos(double degrees, double* sin_out, double* cos_out)
{
	* sin_out = 1.0;
	* cos_out = 2.0;
}

int main()
{
	double degrees(30.0);
	double sin, cos;

	getSinCos(degrees, &sin, &cos); // 주소 넣기

	cout << sin << " " << cos << endl;
	// 1.0, 2.0
	// 함수에서 바꾼 값이 바깥에서도 영향준다

	return 0;
}
```

```c
void foo(const int * ptr)
{
	* ptr = x; // 불가
	prt = &x; // 가능
	//  이거 막으려면 const int * const ptr 이렇게 작성
}
```

### 7.5 다양한 반환 값들(값, 참조, 주소 구조체, 튜플)
- 값 return

```c
#include <iostream>
using namespace std;

int getValue(int x)
{
	int value = x * 2;
	return value;
}

int main()
{
	int val = getValue(3); // 값 return

	return 0;
}
```
-  포인터 return
```c
#include <iostream>
using namespace std;

int* getValue(int x)
{
	int value = x * 2;
	return &value;
}

int main()
{
	int val = * getValue(3);
	// 근데 함수가 끝나면 사라지는 값을
	// 굳이 de referencing할 필요는 없다
	// 문제 발생 가능

	int* val =  getValue(3);
	// 주소를 그대로 받는 이게 더 위험

	return 0;
}
```

- 참조 return
```c
#include <iostream>
using namespace std;

int& getValue(int x)
{
	int value = x * 2;
	return value;
}

int main()
{
	int val = getValue(3);
	// 이것도 문제 가능성 존재
	// 포인터 return과 같은 문제

	cout << val << endl; // 여기는 떴는데
	cout << val << endl; // 여기는 쓰레기값 나옴
	return 0;
}
```
- 참조 return with array

```c
#include <iostream>
#include <array>
using namespace std;

int& get(std::array<int, 100> my_arr, int ix)
{
	return my_arr[ix];
}

int main()
{
	std::array<int, 100> my_arr;
	my_arr[30] = 10;

	get(my_arr, 30) = 1024; // 오 편리하구나

	cout << my_arr[30] << endl; // 1024

	return 0;
}
```
-  구조체
	- 여러개를 return 받고 싶다 : 아래처럼 구조체로 사용
	- 근데 함수마다 구조체를 만들어야하는 단점이 있다

```c
#include <iostream>
using namespace std;

struct S
{
	int a, b, c, d;
};

S getStrct()
{
	S my_s{ 1,2,3,4 };
}

int main()
{
	S my_s = getStrct();

	return 0;
}
```

- tuple (c++17)
```c
#include <iostream>
#include <tuple>
using namespace std;


std::tuple<int, double> getTuple()
{
	int a = 10;
	double d = 3.14;
	return std::make_tuple(a, d);
}

int main()
{
	std::tuple<int, double> my_tp = getTuple();
	cout << std::get<0>(my_tp) << endl;

	// c++17
	auto [a, d] = getTuple();
	cout << a << endl;
	cout << d << endl;

	return 0;
}
```

### 7.6 인라인 함수 Inline Functions
- inline 하면 함수가 아닌 것처럼 컴파일된다
	- 함수를 불러오고 이렇게 안해도 되는 상황
	- 속도가 빨라질 수 있다
	- 요즘 컴파일러가 알아서 inline하기도 해서 점점 차이가 없어진다. 반대로 inline을 안해줄수도 있다.
	- inline을 굳이 안해도 되겠구나

```c
#include <iostream>
using namespace std;

inline int min(int x, int y)
{
	return x > y ? y : x;
}

int main()
{
	cout << min(5, 6) << endl;
	// inline하면 아래처럼 작동
	// 함수를 불러오지 않는 것처럼
	cout << (5 > 6 ? 6 : 5) << endl;

	return 0;
}
```

### 7.7 함수 오버로딩

- 동일한 이름을 갖는 함수를 여러개 만드는 것
	- 들어오는 매개변수는 다른데 기능은 비슷한 함수를 구현할 때 주로 사용
	- return type만 다르면 에러 발생, 매개변수도 달라야 한다. (매개변수가 중요)
	- 주의해야할 점은 함수 매칭이 확실하지 않는 경우 문제 발생 가능

```c
#include <iostream>
using namespace std;

int add(int x, int y)
{
	return x + y;
}

double add(double x, double y)
{
	return x + y;
}

int main()
{
	add(1, 2);
	add(3.6, 6.0);
	// 두가지 함수 중에서 무엇을 사용할지는
	// 컴파일할 때 결정되야한다

	return 0;
}
```
- return을 void로 하고 참조 이용

```c
void getnum(int &x){}
void getnum(double &x){}
int main()
{
	int x;
	getnum(x);
	// int x를 선언해야하는 불편함 존재
}
```
```c
typedef int my_int;
void print(int x){}
void print(my_int x){}
// 컴파일이 같은 함수라고 인식하고 에러발생
```

### 7.8 매개변수의 기본값
- 주의해야할 점 : 기본값이 header 파일이나 declaration에서 선언되어 있으면 뒤에 함수본문에서는 기본값을 빼야한다.

```c
#include <iostream>
using namespace std;

void print(int x = 0) // default
{
	cout << x << endl;
}

int main()
{
	print(10); // 10
	print(); // 0

	return 0;
}
```
- 오버로딩

```c
#include <iostream>
#include <string>
using namespace std;

void print(std::string str){}
void print(char ch = ' '){}

int main()
{
	print(); // char ch = ' ' 함수

	print(10); // 에러
	// 두번째에 default가 있으니까
	// 오버로딩 불가

	return 0;
}
```
```c
void print(int x) {}
void print(int x, int y = 10) {}

int main()
{

	print(10); // 에러
	// 두번째에 default가 있으니까
	// 오버로딩 불가

	return 0;
}
```

### 7.9 함수 포인터 Function pointer
- 함수도 메모리에 저장
- 즉, 함수도 주소를 갖고 있다 : 함수 포인터
	- 함수가 어떤 명령 하는지 ... 등등
	- 함수 호출하면 해당 메모리 주소에 있는 정보 가져와서 실행
- 함수 포인터 초기화 할 때, return type과 parameter가 맞춰줘야 함수 포인터 사용 가능

```c
#include <iostream>
using namespace std;

int func()
{
	return 5;
}

int goo()
{
	return 10;
}

int main()
{
	// 함수 주소 갖고 오기
	int(*fcnptr)() = func;
	cout << fcnptr() << endl; // 5
	// 함수 주소 바꾸기 가능 (비슷한 함수)
	fcnptr = goo;
	cout << fcnptr() << endl; // 10

	return 0;
}
```
- 함수의 매개변수도 함수 넣기
	- 얘도 당연히 default 함수 지정가능

```c
#include <iostream>
#include <array>
using namespace std;

bool isEven(const int& number)
{
	if (number % 2 == 0) return true;
	else return false;
}

bool isOdd(const int& number)
{
	if (number % 2 == 1) return true;
	else return false;
}

void printNum(const array<int, 10>& my_arr, bool (*check_func)(const int&))
{
	for (auto element : my_arr)
	{
		if (check_func(element) == true) cout << element;
	}
	cout << endl;
}
int main()
{
	std::array<int, 10> my_arr{ 0,1,2,3,4,5,6,7,8,9 };

	printNum(my_arr, isEven);
	printNum(my_arr, isOdd);
	// 함수는 그 자체가 포인터니까
	// 앞에 & 필요없이 그냥 넣어도 됨

	return 0;
}
```

```c
// 위에서 내용 이어서
// 둘 다 가능 깔끔~
typedef bool(* check_func_t)(const int&)
using check_func_t = bool( * )(const int&)

void printNum(const array<int, 10>&my_arr, check_func_t check_func) ~
// 이렇게 사용가능
```
- c++11 std::function
	- 뒤에서 유용한 기능 배운다
```c
#include <iostream>
#include <array>
#include <functional>
using namespace std;

bool isEven(const int& number)
{
	if (number % 2 == 0) return true;
	else return false;
}
bool isOdd(const int& number)
{
	if (number % 2 == 1) return true;
	else return false;
}
void printNum(const array<int, 10>& my_arr,
	std::function<bool(const int&)>check_func)
{
	for (auto element : my_arr)
	{
		if (check_func(element) == true) cout << element;
	}
	cout << endl;
}
int main()
{
	std::array<int, 10> my_arr{ 0,1,2,3,4,5,6,7,8,9 };

	std::function<bool(const int&)> fcnptr = isEven;
	printNum(my_arr, fcnptr);
	fcnptr = isOdd;
	printNum(my_arr, fcnptr);

	return 0;
}
```

### 7.10 스택과 힙
- Data
	- 초기화
	- 초기화된 전역, 정적 변수
- BSS
	- 비초기화
	- 비초기화된 전역, 정적 변수
- Code
	- 우리가 작성한 프로그램이 저장

- Stack
	- 속도가 빠른 편
	- 크기가 작은 편
	- 예를 들어, 정적변수를 너무 크게 잡으면 stack overflow 발생
	- 지역변수 저장

- Heap
	- 동적메모리 할당
	- 크기가 큰 편
	- 순서대로 쌓이는 stack과 달리 쌓이는 순서를 예측하기 어렵다

### 7.11 std::vector를 스택처럼 사용하기
- vector를 잘 사용하는 방법?
	- new, delete를 최대한 피하는 것 : 동적할당은 heap 이니까 느림

```c
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	std::vector<int> v{ 1,2,3 };

	v.resize(2); // 원래 크기보다 작게 resize

	for (auto& e : v)
		cout << e << " "; // 1, 2 만 출력됨
	cout << endl;

	cout << v.size() << " " << v.capacity() << endl; // 2, 3

	// cout << v[2] << endl; // runtime 에러

	// 즉, vector의 size를 줄이면 원래 값을 메모리에서 지우지는 않고
	// 없는 척 한다
	// 아래처럼 하면 억지로 불러올 수 있다

	int* ptr = v.data();
	cout << ptr[2] << endl; // 3 나옴

	return 0;
}
```
```c
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	std::vector<int> v{ 1,2,3 };

	v.reserve(1024);
	// 메모리를 확보해 놓겠다
	for (auto& e : v)
		cout << e << " ";
	cout << endl;
	// v.resize(10) 하면 뒤에 0 븥어서 나오는데
	// 얘는 1,2,3 만 나옴
	// 뒤에 원소가 추가될 떄 메모리 교체 같은 작업이 없어서
	// 속도가 더 빠르다

	cout << v.size() << " " << v.capacity() << endl; // 3, 1024

	return 0;
}
```

- 왜 vector로 stack 사용하냐
	-  장점 :  push할 때 capacity가 있으니까 new, delete할 필요없이 사용가능. pop할 때도 capacity 유지하고 size만 줄어드니까 효율적으로 기능.
	-	 단점 :  capacity가 너무 크면 낭비 (그런 경우 거의 없는데 빅데이터, GPU 같은 경우에 한정 될듯)

```c
#include <iostream>
#include <vector>
using namespace std;

void printStack(const std::vector<int>& stack)
{
	for (auto& e : stack)
		cout << e << " ";
	cout << endl;
}

int main()
{
	std::vector<int> stack;

	stack.push_back(3);
	stack.push_back(4);
	printStack(stack);
	stack.push_back(6);
	stack.pop_back();
	stack.pop_back();
	printStack(stack);

	return 0;
}
```

### 7.12 재귀적 함수 호출
- 무한루프가 되지 않도록 조심해야된다
	- 종료 조건을 꼭 넣도록 하자

```c
#include <iostream>
using namespace std;

void countDown(int count)
{
	cout << count << endl;
	if(count > 0)
		countDown(count - 1);
}

int main()
{
	countDown(5);

	return 0;
}
```

### 7.13 방어적 프로그래밍의 개념
- 많은 사람들이 사용하는 프로그램은 최대한 general하게 만들어야 할 것이다.
	- syntax error
	- semantic error : 문맥 오류
	- violated assumption : 사용자가 내가 의도한 방식과 다르게 사용하는 경우

```c
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int x;
	cin >> x;
	// semantic error
	// 조건은 5이상인데 결과는 greater than
	if (x >= 5)
		cout << "x is greater than 5" << endl;
	return 0;

	// violated assumption
	// 사용자가 글자보다 큰 경우 입력하면 에러!
	string hello = "hello, I'm minsoo";
	int ix;
	cin >> ix;
	cout << hello[ix] << endl;
}
```

### 7.14 단언하기 assert
- release mode에서는 아무작동 없다. debug mode에서 작동하는 것이다.
- 런타임에 에러 보여줌
```c
#include <iostream>
#include <cassert>
#include <array>
using namespace std;

void printValue(const std::array<int, 5>& my_arr, const int& ix)
{
	assert(ix >= 0);
	assert(ix <= my_arr.size() - 1);
	cout << my_arr[ix] << endl;
}

int main()
{
	std::array<int, 5>my_arr{ 1,2,3,4,5 };
	printValue(my_arr, 100);
	// 실행하면 cmd창에 assert로
	// 왜 에러가 떴는지 보여준다

	return 0;
}
```
- static_assert
	- 컴파일할 때 에러
	- 문구남기기 가능

```c
#include <iostream>
#include <cassert>
#include <array>
using namespace std;

int main()
{
	const int x = 10;

	static_assert(x == 5, "x should be 5");
	// 컴파일하기전에 이미 빨간줄
	return 0;
}
```
### 7.15 명령줄 인수 command line arguments
- 뭔 소리인지 잘 모르겠음

### 7.16 생략부호 Ellipsis
```c
#include <iostream>
#include <cstdarg> // for ellipsis
using namespace std;

//  들어갈 갯수 count 넣고 ...
double findAver(int count, ...)
{
	double sum = 0;
	va_list list;
	va_start(list, count);

	for (int arg = 0; arg < count; ++arg)
		sum += va_arg(list, int);

	va_end(list);

	return sum / count;
}

int main()
{
	cout << findAver(1, 1, 2, 3, "hello", 'c') << endl;
	// 1
	cout << findAver(3, 1, 2, 3, "hello", 'c') << endl;
	// 1,2,3 의 평균인 2
	cout << findAver(10, 1, 2, 3, "hello", 'c') << endl;
	// 오류 발생
	// 원래 값보다 큰 경우는 오류 발생

	return 0;
}
```
