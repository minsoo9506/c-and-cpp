### 8.1 객체지향 프로그래밍과 클래스
```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Friend
{
public: // access specifier (public, private, protected)

	string name;
	string address;
	int    age;
	double height;
	double weight;

	void print()
	{
		cout << name << " " << address << " " << age << " " << height <<
			" " << weight << endl;
	}

};

int main()
{
	// instanciation
	// f를 초기화해서 instance 만드는 것(메모리에 적재되는 것)
	Friend f{ "minsoo", "Seoul", 26, 174, 72 };

	// 함수이용
	f.print();

	// instance를 vector
	vector<Friend> my_friends;
	my_friends.resize(50);

	for (auto& ele : my_friends)
		ele.print();

	return 0;
}
```

### 8.2 캡슐화, 접근 지정자, 접근 함수
- 접근 지정자
  - default는 private
  - public : 이렇게 써줘야 instance 만들기 가능
  - private : 특별한 방법으로 instance 만들기 가능
  - protected :  뒤에서 상속 배우고 공부

```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Date
{
public: // 접근지정자
	int m_month;
	int m_day;
	int m_year;
};

int main()
{
	Date today;
  // public인 경우 이렇게 접근 가능
	today.m_month = 8;
	today.m_day = 4;
	today.m_year = 2025;

	return 0;
}  
```

- 같은 class에서 만든 다른 instance는 서로 접근 가능
- class 내부의 m_month와 같은 변수들의 이름을 바꿔야하는 경우가 생기는데
  - setDate와 같은 함수를 통해서 instance 초기화를 안하고 public으로 해버리면 이름을 바꾸는데 어려움이 생길 수 밖에 없다.
  - setDate와 같은 함수를 통하면 class 내부에서만 이름을 바꿔주면 된다.

```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Date
{
// default는 private
	int m_month;
	int m_day;
	int m_year;
// 이런 식으로 access function을 만들어준다
// today.m_month 와 같이 instance에서 바로 초기화, 접근하는 것 보다는
public:
	void setDate(const int& month, const int& day, const int& year)
	{
		m_month = month;
		m_day = day;
		m_year = year;
	}

	void copyFrom(const Date& original)
	{
		m_month = original.m_month;
		m_day = original.m_day;
		m_year = original.m_year;
	}
};

int main()
{
	Date today;
	today.setDate(8, 4, 2025);

	Date copy;
	copy.copyFrom(today);
  // private 상태여도  같은 class에서 만든 다른 instance는 서로 접근 가능

	return 0;
}
```

### 8.3 생성자 Constructors
- 기본값 넣기 가능
  - private, public 부분 모두 가능
- 생성자
  - instance 만듬과 동시에 실행 (python에서 init method랑 같은 역할인듯)
  - 함수랑 똑같이 생각하면 된다(instance 만들어질때 호출되는 함수)
  - 생성자의 parameter가 없는 경우 : instance만들때 () 꼭 생략
  - 생성자를 안 만들면 컴파일러가 default 생성자를 알아서 만든다. 그래서 생성자 안 만들고 ```Fraction frac; frac.print();``` 하면 쓰레기값 (컴파일은 된다) 나옴

```c
#include <iostream>
using namespace std;

class Fraction
{
private:
	int m_numerator;
	int m_denominator;

public:
	// 생성자
	// instance 선언과 동시에 실행된다
	Fraction(const int &num, const int &den = 1)
	{
		m_numerator = num;
		m_denominator = den;

		cout << "Fraction() " << endl;
	}

	void print()
	{
		cout << m_numerator << "/" << m_denominator << endl;
	}
};

int main()
{
	Fraction frac(1); // 이 때 생성자 실행
	// 생성자의 parameter가 없는 경우, () 를 꼭 생략해야됨!

	frac.print(); // 1/1

	return 0;
}
```

- public이면 그냥 ```Fraction frac{1,2};``` 이렇게 초기화 가능
- class안에 class 들어가기

```c
#include <iostream>
using namespace std;

class Second
{
public:
	Second()
	{
		cout << "class Second" << endl;
	}
};

class First
{
	Second sec;

public:
	First()
	{
		cout << "class First" << endl;
	}
};

int main()
{
	First first;
	// class Second
	// class First
	// 가 출력된다
	return 0;
}
```
### 8.4 생성자 멤버 초기화 목록 Member Initializer List
```c
#include <iostream>
using namespace std;

class B
{
private:
	int m_b;
public:
	B(const int& m_b_in)
		: m_b(m_b_in)
	{} // {} 없으면 에러뜸
};

class Something
{
private:  // 여기서 초기화 동시에하면? 생성자가 우선순위가 높다 즉, 생성자 초기화목록 출력
	int	m_i;
	double  m_d;
	char	m_c;
	int	m_arr[5];
	B	m_b;

public:
	Something()
		: m_i(1), m_d(3.14), m_c('a'), m_arr{ 1,2,3,4,5 }, m_b(m_i-1) // 초기화목록
	{} // 여기에서 초기화하면 당연히 덮어써서 여기있는게 출력
	void print()
	{
		cout << m_i << " " << m_d << endl;

		for (auto& e : m_arr)
			cout << e << " ";
		cout << endl;
	}
};

int main()
{
	Something som;
	som.print();

	return 0;
}
```

### 8.5 위임 생성자 Delegating Constructors
- 생성자에서 ```name_in``` 말고 ```id_in``` 만 기본값 넣어주고 싶은데 앞에만 넣기 불가능(뒤부터 넣어야됨)
	- 위임 생성자 사용

```c
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
	int	m_id;
	string  m_name;

public:
	Student(const string &name_in)
		: Student(0, name_in)
	{}
	Student(const int& id_in, const string& name_in)
		: m_id(id_in), m_name(name_in)
	{}
	void print()
	{
		cout << m_id << " " << m_name << endl;
	}
};

int main()
{
	Student st1("minsoo");
	st1.print(); // 0 minsoo

	return 0;
}
```
- 초기화 함수를 따로 만들기도 한다
```c
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
	int	m_id;
	string  m_name;

public:
	Student(const string &name_in)
	{
		init(0, name_in);
	}
	Student(const int& id_in, const string& name_in)
	{
		init(id_in, name_in);
	}
	void init(const int& id_in, const string& name_in)
	{
		m_id = id_in;
		m_name = name_in;
	}
	void print()
	{
		cout << m_id << " " << m_name << endl;
	}
};

int main()
{
	Student st1("minsoo");
	st1.print(); // 0 minsoo

	return 0;
}
```
### 8.6 소멸자 destructor
- 변수가 영역을 벗어나 사라질때 호출되는 함수
	- instance가 메모리에서 해제될 때 내부에서 자동으로 호출된다.
	- 동적할당으로 만들어진 경우 영역을 벗어나도 자동으로 메모리가 해제되지 않기 때문에 delete으로 메모리 해제해야 소멸자 호출된다.

```c
#include <iostream>
using namespace std;

class Simple
{
private:
	int m_id;

public:
	Simple(const int&id_in)
		: m_id(id_in)
	{}
	~Simple()
	{
		cout << "Destructor" << m_id << endl;
	}
};

int main()
{
	Simple s1(0);
	Simple s2(1);

	// 실행하면
	// Destructor 1
	// Destructor 0
	// 출력

	// 동적
	Simple* ss = new Simple(0);
	delete ss;

	return 0;
}
```

- 소멸자를 통해 메모리 누수를 막기

```c
#include <iostream>
using namespace std;

class IntArray
{
private:
	int* m_arr = nullptr;
	int m_length = 0;
public:
	IntArray(const int length_in)
	{
		m_length = length_in;
		m_arr = new int[m_length]; // 동적할당
	}
	~IntArray()
	{
		if (m_arr != nullptr)
			delete[] m_arr; // 지우기
	}
	int size() { return m_length; }
};

int main()
{
	while (true)
	{
		IntArray my_int_arr(10000);
	}
	return 0;
}
```
### 8.7 this 포인터와 연쇄 호출
- 같은 class로 찍어내는 instance가 어떻게 구분될까?
	- this가 instance의 주소 갖고 있다

```c
#include <iostream>
using namespace std;

class Simple
{
private:
	int m_id;
public:
	Simple(int id)
	{
		setID(id);
		cout << this << endl; // instance 주소
	}
	void setID(int id) { m_id = id; }
	int getID() { return m_id; }
};

int main()
{
	Simple s1(1), s2(2);
	s1.setID(2);
	s1.setID(4);
	cout << &s1 << " " << &s2 << endl;
	// 예상대로 s1,s2의 주소 나옴

	return 0;
}
```
- 위의 코드에서 ```setID(id)``` 부분이 ```this->setID(id)``` 의 의미를 갖는 것이다.
	- 현재 이 주소를 갖고 있는 instance가 이 함수를 사용한다~ 라는 것

- chaining member function
	- 아래와 같이 코딩 가능
```c
#include <iostream>
using namespace std;

class Calc
{
private:
	int m_value;
public:
	Calc(int init_value)
		: m_value(init_value)
	{}

	Calc& add(int value) { m_value += value; return * this; }
	Calc& sub(int value) { m_value -= value; return * this;}
	Calc& mult(int value) { m_value * = value; return * this;}

	void print()
	{
		cout << m_value << endl;
	}
};

int main()
{
	Calc cal(10);
	// class에서 this pointer를 이용해서
	// 아래처럼 연쇄호출
	cal.add(10).sub(10).mult(2).print();

	return 0;
}
```

### 8.8 클래스 코드와 헤더 파일
- 헤더 파일을 만들어서 클래스 이용
	- cpp 파일에 만들기 보다 헤더 파일에 넣는 경우가 많다
	- 클래스도 무거우면 클래스를 위한 cpp파일도 만든다
	- 헤더파일에 ```using namespace std``` 안 쓰는게 좋다

```c
// Calc.h
// 헤더파일
#pragma once
#include <iostream>

class Calc
{
private:
	int m_value;
public:
	Calc(int init_value);
	Calc& add(int vlaue);
}
```
```c
// Calc.cpp
// 헤더파일 내용
#include "Calc.h"
using namespace std;

Calc::Calc(int init_value)
	: m_value(init_value)
{}

Calc& Calc::add(int value)
{
	m_value += value;
	return * this
}
```

```c
//main.cpp
#include "Calc.h"
~~
```

### 8.9 클래스와 const
- 아래에서 ```setValue```함수는 값을 바꾸는 함수니 에러가 발생하는게 납득이 간다. 근데 ```getValue```는 왜??
	- 이를 막기 위해서 class ```getValue``` 부분에 const를 붙이면 된다.
	- ```setValue```는 붙여도 에러가 발생한다.

```c
#include <iostream>
using namespace std;

class Something
{
	int m_value = 0;
public:
	void setValue(int value) { m_value = value };
	int  getValue() { return m_value };
	// int  getValue() const { return m_value };
	// 이러면 에러발생 x
};

int main()
{
	const Something something;

	something.setValue(3); // 에러 발생
	cout << something.getValue() << endl; // 에러 발생

	return 0;
}
```
- 클래스도 함수에 들어가면 복사되어 사용된다.
	- 근데 아래코드에서 Constructors가 두 번 실행되야 할 거 같은데 한번만 실행된다.
	- 이유는 class에 복사 Constructors가 숨어있다. 그래서 복사되면 우리가 지정한 Constructors가 실행되지 않는 것이다.

```c
#include <iostream>
using namespace std;

class Something
{
public:
	Something()
	{
		cout << "constructor" << endl;
	}
	int m_value = 0;
	void setValue(int value) { m_value = value; }
	int  getValue() { return m_value; }
};

void print(Something st)
{
	cout << &st << endl;
	cout << st.m_value << endl;
}

int main()
{
	Something something;
	cout << &something << endl;
	print(something);
	// 두개의 주소는 예상한 바와 같이 다르다
	// 근데 constructor는 한 번만 실행
	return 0;
}
```
- 이를 최적화하기 위해 reference로 넘겨준다
	- const 와 reference를 쓸수있으면 최대한 쓴다!!

```c
void print(const Something &st)
{
	cout << &st << endl;
	cout << st.m_value << endl;
}
```

- const를 이용한 오버로딩
```c
#include <iostream>
#include <string>
using namespace std;

class Something
{
public:
	string m_value = "default";

	const string& getValue() const {
		cout << "const version" << endl;
		return m_value;}

	string& getValue() {
		cout << "none const version" << endl;
		return m_value; }
};


int main()
{
	Something something1;
	something1.getValue() = 10; // non const version 함수
	const Something something2;
	//something2.getValue() = 10; 에러발생 const version 함수
	something2.getValue();
	return 0;
}
```

### 8.10 정적 static 멤버 변수
- 참고 : static 은 헤더파일에서 컴파일 안된다. cpp 파일에 넣어야한다.

```c
#include <iostream>
using namespace std;

class Something
{
public:
	//static int m_value = 1; static은 초기화 못함
	static int m_value;
};
// 초기화 하려면 이런 식으로 해야됨
int Something::m_value = 1;

int main()
{
	Something st1;
	Something st2;

	st1.m_value = 2;

	cout << &st1.m_value << " " << st1.m_value << endl; // 같은주소, 2
	cout << &st2.m_value << " " << st2.m_value << endl; // 같은주소, 2

	// 이렇게도 접근 가능
	Something::m_value = 1024;
	cout << &Something::m_value << " " << Something::m_value << endl;// 같은주소, 2014

	return 0;
}
```

- const 사용
	- const니까 초기화 해줘야함 위 코드랑 다르다.
```c
class Something
{
public:
	static const int m_value = 1;
};
// int Something::m_value = 1;  못씀
```

### 8.11 정적 멤버 함수
```c
#include <iostream>
using namespace std;

class Something
{
private:
	static int s_value;

public:
	int getValue()
	{
		return s_value;
	}
};

int main()
{
	// cout << Something::s_value << endl;
	// class에서 private 하면 에러
	// 이거 사용하고 싶으면
	// static int getValue()
	// cout << Something::getValue() << endl;

	Something s;
	cout << s.getValue() << endl;

	return 0;
}
```
- instance들(instance의 non static 값도)은 당연히 주소가 다르지만 class의 멤버함수는 하나의 주소에 저장되서 사용된다.
- this라는 것은 (python의 self 같은 느낌인듯) 특정 instance를 사용한다는 것

```c
#include <iostream>
using namespace std;

class Something
{
private:
	static int s_value;
	int m_value;

public:
	static int getValue()
	{
		// return this->s_value; 에러발생
		// static함수라 this를 사용못함
		// static이니까!! 원리를 잘 생각해봐
		// this로 접근해야하는 모든 것이 안된다는 것!

		// return m_value;
		// return this->m_vale;
		// 마찬가지로 얘네 둘다 못씀
	}
	int temp()
	{
		return this->s_value;
		// 여기는 가능 static이 아니라
	}
};

int Something::s_value = 1024;

int main()
{

	Something s1, s2;
	cout << s1.getValue() << endl;

	// 멤버 함수의 포인터
	// 멤버 함수는 하나의 주소니까 instance로 접근이 아니라
	// 아래처럼 class로 접근
	int(Something::*fptr1)() = &Something::temp;
	// 아래와 같이 instance아니면 접근 못함
	// no static member function은 instance에 종속되어
	// 있는 형태니까 instance 즉, this pointer없으면 작동안함
	cout << (s2.* fptr1)() << endl;
	// cout << (.* fptr1)() << endl; 작동안함

	// 얘는 위에와 다르게 Something:: 없고
	// 특정 instance없어도 가능
	int (*fptr2)() = &Something::getValue;
	cout << fptr2() << endl;

	return 0;
}
```
- static member variable은 constructor에서 초기화 불가
	- 하려면 아래와 같은 방법 존재

```c
#include <iostream>
using namespace std;

class Something
{
public:
	class init_
	{
	public:
		init_()
		{
			s_value = 1234;
		}
	};
private:
	static int s_value;
	int m_value;
	static init_ s_initializer;
public:
	static int getValue()
	{
		return s_value;
	}
};

int Something::s_value = 56;
Something::init_ Something::s_initializer;

int main()
{
	cout << Something::getValue() << endl; // 1234

	return 0;
}
```

### 8.12 친구 함수와 클래스 friend
- 외부 함수에서 class A의 private을 출력(접근)하고 싶다!!
	- 친구로 선언해준다

```c
#include <iostream>
using namespace std;

class A
{
private:
	int m_value = 1;

	friend void doSome(A& a);
};

void doSome(A& a)
{
	// class A의 private을 출력하고 싶다!!
	cout << a.m_value << endl;
}

int main()
{
	A a;
	doSome(a);
	return 0;
}
```
- class 2개를 접근

```c
class B; // forward declaration
// 이거 안해주면 class A에서
// friend void doSome(A& a, B& b); 이걸못함
// B가 A보다 뒤에 있으니까

class A
{
private:
	int m_value = 1;

	friend void doSome(A& a, B& b);
};

class B
{
private:
	int m_value = 2;

	friend void doSome(A& a, B& b);
};

void doSome(A& a, B& b)
{
	cout << a.m_value << endl;
	cout << b.m_value << endl;
}
```
- 이번에는 다른 class가 내 private member를 접근하게 해주자

```c
class A
{
private:
	int m_value = 1;

	friend class B; // 이렇게 해주면 class B가 classA의 private member 접근가능
};

class B
{
private:
	int m_value = 2;
public:
	void doSome(A& a)
	{
		cout << a.m_value << endl;
	}
};
```

- 그렇다면 다른 class가 private 접근할 때, 특정 함수만 접근하도록 제한해서 허용하고 싶은 경우

```c
class A; // class B 때문에 전방선언

class B
{
private:
	int m_value = 2;
public:
	void doSome(A& a); // class A m_value를 모르기에 m_value를 사용하는 몸통은 class A뒤에 나오게한다
};

class A
{
private:
	int m_value = 1;

	friend void B::doSome(A& a);
};

void B::doSome(A& a)
{
	cout << a.m_value << endl;
}
```

### 8.13 익명 객체
```c
#include <iostream>
using namespace std;

class A
{
public:
	void print()
	{
		cout << "hello" << endl;
	}
};

int main()
{
	// 익명객체
	// 만들때마다 다른게 만들어지는 것
	// 한번 하고 없어짐
	A().print();
	A().print();

	return 0;
}
```

### 8.14 클래스 안에 포함된 자료형 nested types
- class 안에서만 자료형 선언

```c
#include <iostream>
using namespace std;

class Fruit
{
public:
	enum FruitType
	{
		APPLE, BANANA, CHERRY,
	};
private:
	FruitType m_type;
public:
	Fruit(FruitType type) : m_type(type)
	{}
	FruitType getType() { return m_type; }
};

int main()
{
	Fruit apple(Fruit::APPLE);
	cout << apple.getType() << endl;

	return 0;
}
```
### 8.15 실행 시간 측정하기
```c
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> // 시간관련
using namespace std;

class Timer
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<clock_t> start_time = clock_t::now();

public:
	void elapsed()
	{
		std::chrono::time_point<clock_t> end_time = clock_t::now();
		cout << std::chrono::duration_cast<second_t>(end_time - start_time).count() << endl;
	}
};


int main()
{
	random_device rnd_device;
	mt19937 mersenne_engine{ rnd_device() };

	vector<int> vec(10000);

	std::shuffle(begin(vec), end(vec), mersenne_engine);

	Timer timer;

	std::sort(begin(vec), end(vec));
	timer.elapsed();

	return 0;
}
```
