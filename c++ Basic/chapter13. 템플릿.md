### 13.1 함수 Templates
- 반복적인 작업을 도와준다
- template에서도 instance라는 용어를 사용하는데 이전 class의 객체와 약간은 다른의미라고 할 수 있다. (크게 보면 같은 말이긴 함)
  - "template이 getMax(1,2)를 instanciation하려고 한다" 같이 말한다.

```c
#include <iostream>
using namespace std;

template<typename T>
// template<class T> 도 거의 비슷한 역할 typename이 좀 더 일반적인 느낌
// 원래 하나하나 int, float ... 이렇게 해줘야하는데
// template을 이용하여 컴파일러가 알아서 하도록 해준다
// 개발자들이 만들어 놓은 것
int getMax(T x, T y) { return (x > y) ? x : y; }

int main()
{
    cout << getMax(1, 2) << endl; // 2
    cout << getMax(1.5, 2.4) << endl; // 2.4
    cout << getMax('a', 'b') << endl; // b

    return 0;
}
```

### 13.2 클래스 Templates
- MyArray.h
```c
#pragma once
#include <assert.h>
#include <iostream>

template <typename T>

class MyArray
{
private:
	int m_length;
	T* m_data;
public:
	MyArray()
	{
		m_length = 0;
		m_data = nullptr;
	}
	MyArray(int length)
	{
		m_data = new T [length];
		m_length = length;
	}
	~MyArray()
	{
		reset();
	}
	void reset()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}
	T& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	int getLength()
	{
		return m_length;
	}

	void print(); //

};
```
- MyArray.cpp
```c
#include "MyArray.h"

// class 함수의 body를 cpp로 따로 사용하는 경우 with template
// 아래처럼 해줘야 한다
template<typename T>

void MyArray<T>::print()
{
	for (int i = 0; i < m_length; ++i)
		std::cout << m_data[i] << " ";
	std::cout << std::endl;
}

// class에서 사용할 자료형을 이렇게 알려줘야된다
// class explicit instanciation
template class MyArray<double>;
template class MyArray<char>;
```
- main.cpp
```c
#include "MyArray.h"

int main()
{
    // 이렇게 class 뒤에 자료형을 지정해야한다
    // 아니면 에러발생
    MyArray<double> my_array(10);

    for (int i = 0; i < my_array.getLength(); ++i)
        my_array[i] = i * .5;

    my_array.print();

    return 0;
}
```

### 13.3 자료형이 아닌 템플릿 매개변수
- T_SIZE 를 위에서 처럼 header 에서 빠지는 경우가 생기면 explicit instanciation해야되니까 T_SIZE 관련한 것들은 다 header에 넣는다.

```c
#pragma once
#include <assert.h>
#include <iostream>

template <typename T, unsigned int T_SIZE>
class MyArray
{
private:
	// int m_length;
	T* m_data;
public:
	MyArray()
	{
		m_data = new T [T_SIZE];
	}
	~MyArray()
	{
		delete[] m_data;
	}
	T& operator[](int index)
	{
		assert(index >= 0 && index < T_SIZE);
		return m_data[index];
	}
	int getLength()
	{
		return T_SIZE;
	}
	void print()
	{
		for (int i = 0; i < T_SIZE; ++i)
			std::cout << m_data[i] << " ";
		std::cout << std::endl;
	}

};
```
```c
#include "MyArray.h"

int main()
{   
    //  MyArray<double> my_array(100);
    // 위같이 이전예시에서는 동적할당 그래서
    // cin 과 같이 compile time에 100이라는 숫자를 몰라도 된다

    // 반면에 얘는 compile time에 결정되어 있어야한다
    // 즉, 100들어간 자리에 (ex. i = 100) i를 못들어간다
    MyArray<double, 100> my_array;

    for (int i = 0; i < my_array.getLength(); ++i)
        my_array[i] = i * .5;

    my_array.print();

    return 0;
}
```

### 13.4 함수 템플릿 특수화 specialization
- template으로 일반화 되게 사용하던거를 부분적으로 특별하게 사용하고 싶은 경우에 해당한다
-  function
```c
#include <iostream>
using namespace std;

template<typename T>
T getmax(T x, T y)
{
    return (x > y) ? x : y;
}
// 특수화
// 특정 자료형의 경우는 이 함수를 써라
template<>
char getmax(char x, char y)
{
    cout << "Specialization" << endl;
    return (x > y) ? x : y;
}

int main()
{   
    cout << getmax(1, 2) << endl; // 2
    cout << getmax('a', 'b') << endl; // b 나오고 Specialization

    return 0;
}

```
- class의 member function
```c
~~ class

// 클래스 밖에서  이런식으로~~
// 아래의 경우, double이 들어온 경우
// 따로 이렇게 하겠다~
template<>
void func<double>::print()
{
    ~~
}
```

### 13.5 클래스 템플릿 특수화
- 다른 class 하나 만든다고 생각할 수 있다
```c
#include <iostream>
using namespace std;

template<typename T>
class A
{
public:
    void dosome() { cout << typeid(T).name() << endl; }
    void test(){}
};

template<>
class A<char>
{
public:
    void dosome() { cout << "Char type" << endl; }
};

int main()
{   
    A<int> a_int;
    A<char> a_char;

    a_int.dosome();
    a_char.dosome();

    a_int.test();
    // a_char.test(); // 사용못함

    return 0;
}
```
- 추가내용은 강의 5분부터 참고 (코드 많아서 생략)

### 13.6 템플릿을 부분적으로 특수화 하기
- template parameter가 여러개인 경우 모두 specialization하는게 아니라
  - 상속을 이용하여 specialization하고 싶은 parameter만 해주면 된다

```c
#include <iostream>
using namespace std;

template <class T, int size>
class StaticArray_BASE
{
private:
    T m_array[size];
public:
    T* getArray() { return m_array; }
    T& operater[](int index) { return m_array[index]; }

    void print()
    {
        for (int count = 0; count < size; ++count)
            std::cout << (* this)[count] << ' ';
        std::cout << endl;
    }
};

template <int size>
class StaticArray<char, size> : public StaticArray_BASE<char, size>
{
public:
    void print()
    {
        for (int count = 0; count < size; ++count)
            std::cout << ( * this)[count];
        std::cout << endl;
    }
};

int main()
{   
    StaticArray_BASE<int, 2> int2;
    int2[0] = 1;
    int2[1] = 2;
    int2.print();

    StaticArray<char, 14> char14;
    strcpy_s(char14.getArray(), 14, "Hello world);

    return 0;
}
```


### 13.7 포인터에 대한 템플릿 특수화

```c
#include <iostream>
using namespace std;

template<class T>
class A
{
private:
    T m_value;
public:
    A(const T & input)
        : m_value(input)
    {}

    void print() { cout << m_value << endl; }
};

template<class T>
class A<T*>
{
private:
    T* m_value;
public:
    A(T* input)
        : m_value(input)
    {}

    void print() { cout << * m_value << endl; }
};

int main()
{   
    A<int> a_int(123);
    a_int.print(); // 123

    int temp = 123;
    A<int*> a_int_ptr(&temp);
    a_int_ptr.print(); // 123

    return 0;
}
```

### 13.8 멤버 함수를 한 번 더 템플릿화 하기
```c
#include <iostream>
using namespace std;

template<class T>
class A
{
private:
    T m_value;
public:
    A(const T & input)
        : m_value(input)
    {}

    template<typename TT>
    void dosome(const TT &input=0)
    {
        cout << typeid(T).name() << " " << typeid(TT).name() << endl;
    }

    void print() { cout << m_value << endl; }

};


int main()
{   
    A<int> a_int(123);
    a_int.print(); // 123

    // dosome의 TT 를 따로 templatize
    A<int> a(123);
    a.dosome<float>(); // int float
    a.dosome('a'); // int char

    return 0;
}
```
