### 6.1 배열 기초1
- 일렬로 된 메모리 할당 (빅데이터에서는 이게 성립못할수도 있음)

```c
#include <iostream>
using namespace std;

int main()
{
	int student_scores[5];

	cout << sizeof(student_scores) << endl; // 20

	// 하나의 element 초기화
	student_scores[0] = 100 // 1st element

	return 0;
}
```
- 구조체와 배열
```c
#include <iostream>
using namespace std;

struct People
{
	int age;
	int height;
};

int main()
{
	cout << sizeof(People) << endl; // 8

	People korea[10];
	cout << sizeof(korea) << endl; // 80

	korea[0].age = 24;

	return 0;
}
```

-  배열 초기화
```c
#include <iostream>
using namespace std;

int main()
{
	// 1
	int arr[5];
	arr[0] = 1;
	// 2
	int arr[5] = { 1,2,3,4,5 };
	// 3
	int arr[5] = { 1,2, }; // 나머지는 0으로 채워짐
	// 4
	int arr[] = { 1,2,3,4,5 };
	// 5
	int arr[]{ 1,2,3,4,5 };

	return 0;
}
```

### 6.2 배열 기초 2

- 메모리에 일렬로 되어있음을 확인
```c
int arr[4];

cout << (int)arr << endl; // 배열같은 경우 배열 자체가 주소값을 갖는다
cout << (int)&arr << endl;
cout << (int)&arr[0] << endl;
cout << (int)&arr[1] << endl;
cout << (int)&arr[2] << endl;
cout << (int)&arr[3] << endl;
```

- 함수의 매개변수
```c
#include <iostream>
using namespace std;

void doSomething(int arr[]) // 컴파일러는 배열이 아니라 포인터로 처리
{						
	// 따라서 이 값은 매개변수 arr의 주소값의 주소값이 나온다
	// 포인터의 포인터인 것이다!!
	cout << (int)&arr << endl;
	// 따라서 아래의 값도 4가 나옴 (포인터의 size니까)
	cout << sizeof(arr) << endl;
	// 배열 arr의 원소에 접근은 이런식
	// 더 많은 방법 뒤에 배움
	cout << arr[0] << endl;
}

int main()
{
	int my_arr[4] = { 1,2,3,4 };

	doSomething(my_arr);

	return 0;
}
```

### 6.3 배열과 반복문
```c
#include <iostream>
using namespace std;

int main()
{
	int score[] = { 100,90,80 };
	const int num = sizeof(score) / sizeof(int);
	int total = 0;
	int max_score = 0;

	for (int i = 0; i < num; ++i)
	{
		total += score[i];
		max_score = (max_score < score[i]) ? score : max_scroe;
		//if (max_score < score[i]) max_score = score[i];
	}

	return 0;
}
```

### 6.4 배열과 선택 정렬  (selection sort)

```c
#include <iostream>
using namespace std;

void printArray(const int array[], const int length)
{
	for (int index = 0; index < length; ++index)
		cout << array[index] << " ";
	cout << endl;
}

int main()
{
	const int length = 5;
	int array[length] = { 3,1,5,4,2 };
	printArray(array, length);

	for (int startIndex = 0; startIndex < length-1; ++startIndex)
	{
		for(int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			int smallestIndex = startIndex;

			if (array[smallestIndex] > array[currentIndex])
			{
				smallestIndex = currentIndex;
			}
			// swap
			int temp = array[smallestIndex];
			array[smallestIndex] = array[startIndex];
			array[startIndex] = temp;
		}
		printArray(array, length);
	}
	return 0;
}
```

### 6.5 정적 다차원 배열
- 컴퓨터는 1차원(일렬)으로 메모리 저장

```c
#include <iostream>
using namespace std;

int main()
{
	const int num_row=2;
	const int num_col=4;
	int arr[num_row][num_col];

	// 하나씩 초기화
	arr[0][0] = 1;

	// 한번에 초기화
	// num_row는 생략가능
	int arr2[num_row][num_col] =
	{
		{1, 2, }, // 생략하면 0으로 채움
		{6, 7, 3, 4}
	};

	for (int row = 0; row < num_row ; ++row)
	{
		for (int col = 0; col < num_col; ++col)
			cout << (int)&arr2[row][col] << '\t';
		cout << endl;
	}
	// 2차원 배열이지만 메모리에는 일렬로
	// 저장됨을 알 수 있다

	return 0;
}
```

### 6.6 C언어 스타일의 배열 문자열
```c
#include <iostream>
using namespace std;

int main()
{
	char myString[] = "string";

	for (int i = 0; i < 7; ++i)
	{
		cout << (int)myString[i] << endl;
		cout << (int)&myString[i] << endl;
	}
	// 마지막에 0이 나오는데 문자열은 마지막에 이 배열이
	// 문자임을 표시하는 null character가 존재


	char arrString[255];
	cin >> arrString;

	arrString[0] = 'H'; // numeric 배열처럼 수정가능
	arrString[3] = '\0'; // null chracter

	cout << arrString << endl; // null전까지 출력됨

	return 0;
}
```

- cstring
	- 초보 연습을 위해 공부하지만 나중에는 std::string 만 거의 쓸 것이다.

```c
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	// strcpy
	char source[] = "Copy this";
	char dest[50];
	strcpy(dest, source);
	// 요즘에는 strcpy_s
	strcpy_s(dest, 50 , source);

	// strcat() : 두 문자열을 붙인다
	strcat(dest, source);
	cout << source << endl;
	cout << dest << endl;

	// strcmp() : 두 문자열을 비교
	// 같으면 0, 다르면 -1 return 주의!!
	cout << strcmp(dest, source) << endl;

	return 0;
}
```

### 6.7 포인터의 기본적인 사용법
- 포인터공부로 컴퓨터 내부 작동 원리에 대한 이해 가능
```c
#include <iostream>
using namespace std;

int main()
{
	int x = 5;
	cout << &x << endl; // 16진수
	cout << (int)&x << endl; // int로 casting

	// de-reference operator *
	// 그 메모리 주소에 뭐가 있는데~
	cout << *&x << endl; // 5 나옴

	// pointer : 메모리 주소를 담는 변수
	int* ptr_x = &x;

	cout << ptr_x << endl;  // x 주소
	cout << *ptr_x << endl; // x 값

	// 주소는 항상 4byte
	double* ptr_d;
	double d;
	cout << sizeof(ptr_x) << endl; //4
	cout << sizeof(ptr_d) << endl; //4
	cout << sizeof(&d) << endl;    //8
	// double 자체는 8byte
	// 그 값의 주소는 항상 4byte . 64bit 체제에서는 8byte

	return 0;
}
```

### 6.7 NULL 포인터
- 포인터를 초기화 안하면 쓰레기값이 담기는데 이를 de-reference 하면 문제가 발생할수도 있기에 조심 : NULL 포인터 사용

```c
#include <iostream>
using namespace std;

void doSome(double* ptr)
{
	if (ptr != nullptr)
		cout << *ptr << endl;
	else
		cout << "Null ptr" << endl;
	cout << "address of pointer ";
	cout << &ptr << endl;
}

int main()
{
	// modern c++ 에서는
	// nullptr 을 사용한다
	double* ptr = nullptr;

	doSome(ptr);
	doSome(nullptr);

	double d{ 123.4 };
	doSome(&d);

	ptr = &d;
	doSome(ptr);

	// 포인터의 주소 ?!
	cout << "address of pointer ";
	cout << &ptr << endl;
	// doSome 함수의 인자들의 주소는 모두 동일
	// ptr의 주소와 doSome에 넣은 뒤의 ptr의 주소는 다르다
	// 즉, 함수에 들어가면어 원래 변수의
	// 값이 복사되어 사용되는 것이다
	return 0;
}
```

### 6.8 포인터와 정적 배열
- 포인터와 배열의 관계!
	- 같다고 할 수 있다
	- 결국 정적 배열은 포인터이다
	- 다만 문법적으로 배열을 좀 더 유용하게 쓰기 위해 약간의 차이가 존재
	- 배열은 첫번째 원소의 주소값을 갖는다
	- arr 와 &arr[0] 는 같은 값을 갖는것이다.

```c
#include <iostream>
using namespace std;

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	// 아래 두개는 같은 값이 나옴
	cout << arr << endl;
	cout << &arr[0] << endl; // &(arr[0])

	cout << *arr << endl; // 1 나옴

	char name[] = "minsoo";
	cout << *name << endl; // m 나옴

	// 그럼 정적배열과 포인터 차이?
	cout << sizeof(arr) << endl; // 20
	int* ptr = arr;
	cout << sizeof(ptr) << endl; // 4

	return 0;
}
```

- 함수의 인자
	- 함수의 인자로 배열을 받아도 그 함수에서는 pointer로 사용된다
	- 그래서 함수 내에서 sizeof도 배열의 크기가 아니라 포인터의 크기인 4가 나온다
```c
#include <iostream>
using namespace std;

void printArr(int array[])
{
	cout << sizeof(array) << endl;
}

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	cout << sizeof(arr) << endl; // 20
	printArr(arr); // 4

	return 0;
}
```
- 구조체
	- 배열이 구조체나 클래스 안에 있으면 배열 전체가 간다
```c
#include <iostream>
using namespace std;

struct arrstruct
{
	int arr[5] = { 5,2,6,7,1 };
};

void doSome1(arrstruct arrst) // 구조체
{
	cout << sizeof(arrst.arr) << endl;
}

void doSome2(arrstruct *arrst) // 구조체 주소
{
	cout << sizeof((*arrst).arr) << endl;
}

int main()
{
	arrstruct ms;
	cout << ms.arr[0] << endl; // 5
	// sizeof
	// 같은 size
	cout << sizeof(ms.arr) << endl; // 20
	doSome1(ms);  //20
	doSome2(&ms);  //20

	return 0;
}
```

- C에서는 많이 쓰였는데 C++에서는 잘 안씀
	- 함수내에서 element를 바꾸면 해당 배열의 값이 바뀜 (함수밖에서도)

```c
void changeArr(int array[])
{
	* array = 100; // 첫번째 원소를 100으로
	// array[0] = 100;
}

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	changeArr(arr);
	// 함수밖에서도 값이 바뀜
	cout << arr[0] << endl; // 100

	return 0;
}
```

### 6.9 포인터 연산과 배열 인덱싱
- 포인터 선언시에 포인터 data type??
	- 어차피 포인터 자체는 4byte (x86체제에서, x64는 8byte) 라서 중요하지는 않지만
	- 1. 포인터 + 1 과 같은 연산이 몇 차이가 나는지 파악하기 위해
	- 2. 포인터가 가르키는 data type을 파악하기 위해

```c
#include <iostream>
using namespace std;
int main()
{
	int value1 = 7;
	int* ptr = &value1;
	// 4씩 증가 int니까
	cout << uintptr_t(ptr) << endl;
	cout << uintptr_t(ptr + 1) << endl;
	cout << uintptr_t(ptr + 2) << endl;

	double value2 = 7;
	double* ptr = &value2;
	// 8씩 증가 double이니까
	cout << uintptr_t(ptr) << endl;
	cout << uintptr_t(ptr + 1) << endl;
	cout << uintptr_t(ptr + 2) << endl;

	return 0;
}
```

```c
#include <iostream>
using namespace std;


int main()
{
	// 포인터를 통해 배열의 원소 접근
	int arr[] = { 5,2,6,3,7 };
	int* ptr = arr;

	for (int i = 0; i < 5; ++i)
	{
		cout << * (ptr + i) << " " << (uintptr_t)(ptr + i) << endl;
	}

	// 문자열
	// null char 까지 출력됨
	char name[] = "Song min soo";
	const int n_name = sizeof(name) / sizeof(char);
	for (int i = 0; i < n_name; ++i)
	{
		cout << * (name + i);
	}

	return 0;
}
```

### 6.10 C언어 스타일의 문자열 심볼릭 상수
- 예외적인 케이스
```c
#include <iostream>
using namespace std;

int main()
{
	// 리터럴을 포인터에?? 당연 불가
	char* name = "Song";

	// 기호적 상수
	// const를 붙이면 된다
	const char* name1 = "Song";
	const char* name2 = "Song";
	// 둘이 같은 값을 갖는다
	// 같은 내용이니까 같은 주소를 써라~ 느낌
	// 내용이 달라지면 당연히 포인트값 다름
	cout << (uintptr_t)name1 << endl;
	cout << (uintptr_t)name2 << endl;

	return 0;
}
```

- 문자열 포인터 특성
	- cout 하면 포인터값(주소)이 아니라 그 배열원소가 출력된다 (null character만날때까지 출력)


### 6.11 메모리 동적 할당 new 와 delete
- 동적할당
	- heap 에 저장
	- 정적할당은 stack에 저장되는데 heap의 용량이 더 크다
	- 실제로 메모리할당은 동적할당을 주로 한다

```c
#include <iostream>
using namespace std;

int main()
{
	// new
	// 메모리를 가져오는 역할
	int* ptr = new int;
	* ptr = 7; //de-reference
	// int * ptr = new int{7};

	// delete
	// 메모리를 돌려주는 역할
	// 이거안해도 프로그램 끝나면 OS가
	// 메모리 다시 가져가지만
	// 우리가 원할때 돌려주는 의미
	delete ptr;
	// 근데
	// delete 한 이후에 ptr을 찍어보면
	// 그대로 값이 나옴!!
	// de-reference 하면 쓰레기값이 나오고
	// 즉, 주소는 남아있지만 그 주소따라가보면 nothing
	// 뒤에 이런 문제도 해결하는 방법 배움 (smart pointer)
	cout << ptr << endl;
	cout << * ptr << endl;

	// 뭐 이런식으로 가능
	ptr = nullptr;

	// 메모리가 없을때 에러발생할 수도!!
	// 이렇게 하면 에러발생은 안하고 nullptr로 초기화
	int* ptr = new (std::nothrow) int{ 7 };

	return 0;
}
```

- 메모리 누수 memory leak
	- 동적메모리 할당지우기를 깜빡하는 경우
```c
#include <iostream>
using namespace std;

int main()
{
	// memory leak
	while (true)
	{
		int* ptr = new int;
		cout << ptr << endl;

		// delete ptr; 까먹
	}
	return 0;
}
```

### 6.12 동적 할당 배열
- runtime에 배열의 사이즈 결정하고 그때마다 os에서 메모리를 받아와서 유동적

```c
#include <iostream>
using namespace std;

int main()
{

	int length;
	cin >> length;

	int* arr = new int[length];

	arr[0] = 1;
	arr[1] = 2;

	// 2 보다 큰 값하면 원소에 쓰레기값들어감
	// 근데
	// int* arr = new int[length]{};
	// int* arr = new int[length]{1,2};
	// 이런식으로 하면 나머지는 0으로 채워짐
	// 만약 초기화한 원소 수보다 length를 작게 할당하면?
	// 컴파일시에 짤리면서 경고하는 소리나옴

	for (int i = 0; i < length; ++i)
	{
		cout << arr[i] << endl;
		cout << (uintptr_t)&arr[i] << endl;
	}

	delete[] arr; // 배열 지울때 [] 사용

	return 0;
}
```

```c
// 컴파일 안됨
int* arr = new int[] {1, 2, 3, 4};
```

### 6.13 포인터와 const

- const 포인터 ~
	- 포인터 자체의 값(주소)을 안 바꾸겠다가 아니라
	- 그 포인터가 가르키는 값을 안 바꾸겠다
	- 즉, de-reference를 통해 value를 바꾸는것이 불가능하다는 의미

```c
#include <iostream>
using namespace std;

int main()
{
	// const 포인터
	int value1 = 5;
	int value2 = 5;
	const int* ptr = &value2;
	// * ptr = 6; 불가
	value2 = 6;// 이거는 가능
	cout << * ptr << endl; // 6 나옴
	ptr = &value1; // 이거도 가능

	// * const 포인터
	int value3 = 10;
	int* const ptr2 = &value3;
	* ptr2 = 10; // 이제 가능
	int value4 = 7;
	// ptr2 = &value4; 불가능

	// const * const 포인터
	// 위 두 기능합치기
	int value5 = 4;
	const int* const ptr3 = &value5;

	return 0;
}
```

### 6.14 참조 변수
- 참조 변수 reference
	- 포인터보다 편할수 있다
	- 그냥 value의 다른 이름이라고 생각할 수 있다
	- 참조변수는 무조건 초기화해야한다
	- 오른쪽에 리터럴 못 들어간다. 변수가 들어가야한다

```c
#include <iostream>
using namespace std;

int main()
{
	int value = 5;
	// 포인터
	int* ptr = nullptr;
	ptr = &value;
	// 참조
	int& ref = value;
	cout << ref << endl; // 5
	ref = 10;
	cout << value << endl; // 10

	// 1~3번째 줄은 같은 결과
	// 4번째는 포인터의 주소니까 다름
	cout << &value << endl;
	cout << &ref << endl;
	cout << ptr << endl;
	cout << &ptr << endl;

	//
	const int y = 8;
	int& ref = y; // 불가능
	const int& ref = y; // const붙여야함

	//
	int value1 = 5;
	int value2 = 10;
	int& ref1 = value1;
	ref1 = value2;
	cout << ref1 << endl; //10

	return 0;
}
```

- 함수인자로 참조 변수
	- 해당 변수의 값을 함수내에서 바꾸면 함수밖에서도 바뀐다
	- 변수가 복사되는게 아니라 그 변수가 자체로 넘어간다고 한다
	- 이전에 포인터를 인자로 넣었을 때는 복사되어서 사용되었는데 이와 다름을 이해하자

```c
#include <iostream>
using namespace std;

void doSomething(int &n) // const 넣으면 n 못 바꿈
{
	n = 10;
}

int main()
{
	int n = 5;
	doSomething(n);
	cout << n << endl; // 10

	return 0;
}
```
```c
#include <iostream>
using namespace std;

struct Something
{
	int v1;
	float v2;
};

struct Other
{
	Something st;
};

int main()
{
	Other ot;
	ot.st.v1 = 3; // 이렇게 하면 복잡
	// reference 이용
	int& v1 = ot.st.v1;
	v1 = 3;

	return 0;
}
```

### 6.15 참조와 const
```c
#include <iostream>
using namespace std;


// const 넣으면
// 함수 내부에서 x 값 못 바꾸고
// 함수의 인자로 변수가 아닌 숫자리터럴 가능
void dosome(const int &x)
{
	cout << x << endl;
}

int main()
{
	// int& ref_x = 3 + 4; // 불가능
	const int& ref_x = 3 + 4; // 가능

	// 다 가능 wow
	// reference를 함수파라미터로 사용하는 장점에 해당
	int a = 3;
	dosome(a);
	dosome(1);
	dosome(a + 1);

	return 0;
}
```

### 6.16 포인터와 참조의 멤버 선택 연산자 member selection operators
```c
#include <iostream>
using namespace std;

struct Person
{
	int age;
	double weight;
};

int main()
{
	Person person;
	// . 은 member selection opt
	person.age = 5;
	person.weight = 30;

	// 마찬가지
	Person& ref = person;
	ref.age = 15;

	// -> 가 member selection opt
	Person* ptr = &person;
	ptr->age = 30;
	// (* ptr).age = 20; // 이것도 가능

	// ptr을 de-referensing해서
	// 할당 가능 당연히 같은 주소값
	Person& ref2 = * ptr;
	ref2.age = 45;

	return 0;
}
```

### 6.17 c++11 For-each 반복문
```c
#include <iostream>
using namespace std;


int main()
{
	int fibo[] = { 0,1,1,2,3,5,8,13 };
	// output
	// fibo 원소들이 하나씩 넘어간다
	for (int num : fibo)
		cout << num << " ";
	cout << endl;

	// change array value
	// 이렇게 하면 원소들이 다 10으로 바뀜
	// for(int num : fibo) 이렇게 하면
	// 안바뀜 -> 함수인자 복사되서 사용되니까
 	for (int& num : fibo) // 그리고 int 이렇게보다 auto 많이 넣는다
		num = 10;

	return 0;
}
```
```c
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

int main()
{
	// 가장 큰 숫자 찾기
	int whereMax[] = { 1,3,7,9,10,46,44,78 };

	int max_num = std::numeric_limits<int>::lowest();

	for (const auto& n : whereMax)
		max_num = std::max(max_num, n);
	cout << max_num << endl; // 78

	return 0;
}
```

### 6.18 void 포인터
- 거의 사용안함 그냥 포인터의 이해를 위해 공부
- 나중에 뒤에서 아래의 내용을 더 깔끔하게 해결하는 방법 배움

```c
#include <iostream>
using namespace std;

int main()
{
	int i = 5;
	float f = 3.0;
	char c = 'a';
	// 문제없음
	void* ptr = nullptr;
	ptr = &i;
	ptr = &f;
	ptr = &c;
	// 단점
	// void라서 이게 int 인지 float 인지 모름
	// void 라서 포인트연산 불가능
	cout << ptr + 1 << endl; // 불가
	// de reference도 불가능
	cout << * ptr << endl; // 불가
	// casting하면 사용 가능
	cout << * static_cast<float*>(ptr) << endl;

	return 0;
}
```

### 6.19 이중 포인터와 동적 다차원 배열
- 이중 포인터
	- " * " 더 붙이면 더 됨 (다중포인터)
```c
#include <iostream>
using namespace std;

int main()
{
	// 이중포인터
	int* ptr = nullptr;
	int** ptrptr = nullptr;

	int value = 5;

	ptr = &value;
	ptrptr = &ptr;

	return 0;
}
```
- 사용예시
	- 2D를 이중포인터로

```c
#include <iostream>
using namespace std;

int main()
{
	int col = 5;
	int row = 3;
	int* r1 = new int[col] {1, 2, 3, 4, 5};
	int* r2 = new int[col] {6, 7, 8, 9, 10};
	int* r3 = new int[col] {11, 12, 13, 14, 15};

	int** matrix = new int* [row] {r1, r2, r3};

	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
			cout << matrix[r][c] << " ";
		cout << endl;
	}

	delete[] r1;
	delete[] r2;
	delete[] r3;
	delete[] matrix;

	return 0;
}
```

### 6.20 std::array 소개
```c
#include <iostream>
#include <array>
using namespace std;

int main()
{
	// array
	// int arr[5] = { 1,2,3,4,5 }; 이거랑 동일
	// 단, 원소가 몇개인지 꼭 들어가야됨
	// 1
	std::array<int, 5> my_arr = { 1,2,3,4,5 };
	// 2 (using namespace std한 경우)
	array<int, 5> my_arr = { 1,2,3,4,5 };

	//
	my_arr = { 1,2, }; // 나머지 0

	// 두번째(.at)는 my_arr의 갯수와 수를 비교한다고함
	// 그래서 다르면 예외처리(나중에 배움)
	// 속도는 첫번째가 더 빠르다
	cout << my_arr[10] << endl;
	cout << my_arr.at(10) << endl;

	// 기타 기능 (다양함)
	cout << my_arr.size() << endl;

	return 0;
}
```
- 함수 인자로서 array
	- array도 복사되서 사용됨
	- 따라서 array가 클 경우에 속도가 느림
	- reference로 사용하면 해결되겠군
```c
void printlen(array<int, 5> my_arr)
{
	cout << my_arr.size() << endl;
}
```
- 정렬 기능
```c
#include <iostream>
#include <array>
#include <algorithm> //sort를 위해
using namespace std;


int main()
{
	array<int, 5>my_arr = { 1,32,3,5 };

	for (auto& element : my_arr)
		cout << element << " ";
	cout << endl;

	// 정렬
	sort(my_arr.begin(), my_arr.end());
	// sort(my_arr.rbegin(), my_arr.rend()); 역순

	for (auto& element : my_arr)
		cout << element << " ";
	cout << endl;

	return 0;
}
```

### 6.21 std::vector 소개
- vector 완전 편함
```c
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// 동적할당 되는거라
	// array와 다르게 사이즈 필요 없네
	std::vector<int> arr;

	std::vector<int> arr2 = { 1,2,3,4 };
	cout << arr2.size() << endl; // 4

	std::vector<int> arr3 = { 1,2, };
	cout << arr3.size() << endl; // 2

	std::vector<int> arr4{ 1,2,3 };
	cout << arr4.size() << endl; // 3

	return 0;
}
```
- vector
	- 길이를 기억
	- 메모리를 알아서 지워준다 : return해서 나가거나 block 밖으로 나가거나하면 (delete 안해도 된다고 함)

```c
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> arr = { 1,2,3,4,5 };

	for (auto& itr : arr)
		cout << itr << " ";
	cout << endl;

	// array와 동일
	cout << arr[1] << endl; // 2
	cout << arr.at(1) << endl; // 2

	// resize
	arr.resize(10);

	cout << arr.size() << endl; // 10
	// 나머지 0 채워짐
	for (auto& itr : arr)
		cout << itr << " ";
	cout << endl;

	return 0;
}
```
