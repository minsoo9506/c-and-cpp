### 9.1 산술 연산자 오버로딩 하기
- 오버로딩 안되는 산술 연산자
  - ?:, ::, sizeof, *
- 멤버 함수로만 구현해야 되는 연산자
  - =, [], (), ->
```c
#include <iostream>
using namespace std;

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0) { m_cents = cents; }
	int getCents() const { return m_cents; }
	int& getCents() { return m_cents; }

	Cents operator + (const Cents& c2)
	{
		return Cents(this->m_cents + c2.m_cents);
	}

};

int main()
{
	Cents cents1(6);
	Cents cents2(8);

	cout << (cents1 + cents2 + Cents(6)).getCents() << endl;

	return 0;
}
```
### 9.2 입출력 연산자 오버로딩 하기
- 이전에 instance의 멤버변수를 보려면 print() 같은 함수를 만들어서 사용했는데 그럴 필요없이 입출력 연산자 오버로딩을 이용해보자.
- https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=60205596757&proxyReferer=https%3A%2F%2Fwww.google.com%2F : 해당 블로그 참고
```c
#include <iostream>
#include <fstream> // 파일 출력
using namespace std;

class Point
{
private:
	double m_x, m_y, m_z;
public:
	Point(double x=0.0, double y = 0.0, double z = 0.0)
		: m_x(x), m_y(y), m_z(z)
	{}
	double getX() { return m_x; }
	double getY() { return m_y; }
	double getZ() { return m_z; }

// 출력
	friend std::ostream& operator << (std::ostream& out, const Point& point)
	{
		out << point.m_x << " " << point.m_y << " " << point.m_z;
		return out;
	}
// 입력
	friend std::istream& operator >> (std::istream& in, Point& point)
	{
		in >> point.m_x >> point.m_y >> point.m_z;
		return in;
	}
};

int main()
{
	ofstream of("out.txt"); // txt파일에 출력

	Point p1(0.0, 0.1, 0.2), p2(3.5, 1.5, 1.9);
	cout << p1 << " " << p2 << endl; // 출력
	cin >> p1 >> p2;  // 입력
	cout << p1 << " " << p2 << endl; // 바뀐값 다시 출력

	of<< p1 << " " << p2 << endl; // 파일출력
	of.close();

	return 0;
}
```
### 9.3 단항 연산자 오버로딩 하기
```c
#include <iostream>
using namespace std;

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0) { m_cents = cents; }
	int getCents() const { return m_cents; }
	int& getCents() { return m_cents; }

	Cents operator - () const
	{
		return Cents(-m_cents);
	}

	bool operator ! () const
	{
		return (m_cents == 0) ? true : false;
	}

	friend std::ostream& operator << (std::ostream& out, const Cents& cents)
	{
		out << cents.m_cents;
		return out;
	}
};

int main()
{
	Cents cents1(6);
	Cents cents2(0);

	cout << cents1 << endl; // 6
	cout << -cents1 << endl; // -6
	cout << cents1 << endl; // 6
	cout << -Cents(-10) << endl; // 10

	// bool
	auto temp = !cents2; // auto가 bool로 잡힘
	cout << !cents1 << " " << !cents2 << endl; // 0 1

	return 0;
}
```
### 9.4 비교 연산자 오버로딩 하기
```c
#include <iostream>
using namespace std;

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0) { m_cents = cents; }
	int getCents() const { return m_cents; }
	int& getCents() { return m_cents; }

	friend bool operator == (const Cents& c1, const Cents& c2)
	{
		return c1.m_cents == c2.m_cents;
	}

	friend std::ostream& operator << (std::ostream& out, const Cents& cents)
	{
		out << cents.m_cents;
		return out;
	}
};

int main()
{
	Cents cents1(6);
	Cents cents2(6);

	if (cents1 == cents2)
		cout << "Equal" << endl;

	return 0;
}
```
- vector로 arr을 만들어서 class instance들을 sort하려고 하는데 바로는 불가능하다. 이것도 만들어줘야 한다.
```c
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0) { m_cents = cents; }
	int getCents() const { return m_cents; }
	int& getCents() { return m_cents; }

	// std::sort 사용시에 < 로 해야됨 > 불가
	friend bool operator < (const Cents& c1, const Cents& c2)
	{
		return c1.m_cents < c2.m_cents;
	}

	friend std::ostream& operator << (std::ostream& out, const Cents& cents)
	{
		out << cents.m_cents;
		return out;
	}
};

int main()
{
	vector<Cents>arr(20);
	for (unsigned i = 0; i < 20; ++i)
		arr[i].getCents() = i;

	// 섞는다
	std::random_shuffle(begin(arr), end(arr));

	for (auto& e : arr)
		cout << e << " ";
	cout << endl;

	// sort
	std::sort(begin(arr), end(arr));

	for (auto& e : arr)
		cout << e << " ";
	cout << endl;
	// 오름차순으로 sort 된다
	return 0;
}
```
### 9.5 증감 연산자 오버로딩 하기
- 전위 vs 후위 주의!
```c
#include <iostream>
using namespace std;

class Digit
{
private:
	int m_digit;
public:
	Digit(int digit = 0) : m_digit(digit) {}

	// prefix
	Digit& operator ++()
	{
		++m_digit;
		return * this;
	}
	//postfix
	// post는 dummy int를 넣어주면 됨
	Digit operator ++(int)
	{
		Digit temp(m_digit);
		++(* this);
		return temp;
	}

	friend std::ostream& operator << (std::ostream& out, const Digit& digit)
	{
		out << digit.m_digit;
		return out;
	}
};
int main()
{
	Digit d(5);

	cout << ++d << endl; // 6
	cout << d << endl; // 6

	cout << d++ << endl; // 6
	cout << d << endl; // 7

	return 0;
}
```
### 9.6 첨자 연산자 오버로딩 하기
```c
#include <iostream>
#include <cassert>
using namespace std;

class IntList
{
private:
	int m_list[10];

public:
	int& operator [] (const int index)
	{
		assert(index >= 0);
		assert(index < 10);
		return m_list[index];
	}
};

int main()
{
	IntList my_list;
	cout << my_list[3] << endl;

	// pointer로 사용할 때 주의
	IntList* list = new IntList;
	(* list)[3] = 10; // de reference 해서 접근

	return 0;
}
```
### 9.7 괄호 연산자 오버로딩과 함수 객체
- 괄호 연산자 오버로딩으로 객체를 통해 함수를 호출하는 것처럼 보인다
```c
#include <iostream>
using namespace std;

class Accumulator
{
private:
	int m_counter = 0;
public:
	int operator ()(int i) { return (m_counter += i); }
};

int main()
{
	Accumulator acc;
	cout << acc(10) << endl; // 10
	cout << acc(20) << endl; // 30

	return 0;
}
```
### 9.8 형변환을 오버로딩 하기
- instance를 parameter를 int로 갖는 함수에 바로 사용? 불가능 이를 가능하게 해보자.
```c
#include <iostream>
using namespace std;

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0) { m_cents = cents; }
	int getCents() { return m_cents; }
	void setCents(int cents) { m_cents = cents; }
	// printInt 함수에서 instance를 바로 사용가능케
	operator int() { return m_cents; }

};

void printInt(const int& value)
{
	cout << value << endl;
}

class Dollar
{
private:
	int m_dollars = 0;
public:
	Dollar(const int & input) : m_dollars(input){}

	operator Cents() { return Cents(m_dollars * 100); }
};

int main()
{
	Cents cents1(7);
	printInt(cents1); // 7

	Dollar dol(2);
	Cents cents2 = dol;
	printInt(cents2); // 200
	return 0;
}
```
### 9.9 복사 생성자, 복사 초기화, 반환값 최적화
- 복사 생성자, 복사 초기화

```c
#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
	int m_num;
	int m_den;
public:
	Fraction(int num = 0, int den = 1)
		: m_num(num), m_den(den)
	{
		assert(den != 0);
	}
	// copy constructor
	Fraction(const Fraction& fraction)
		:m_num(fraction.m_num), m_den(fraction.m_den)
	{}

	friend std::ostream& operator <<(std::ostream& out, const Fraction& f)
	{
		cout << f.m_num << "/" << f.m_den << endl;
		return out;
	}
};

int main()
{
	Fraction frac(3, 5);
	Fraction fr_copy1 = frac;
	Fraction fr_copy2(frac); // 복사 초기화

	cout << frac;  // 3/5
	cout << fr_copy1;  // 3/5
	cout << fr_copy2;  // 3/5

	return 0;
}
```
- 반환값 최적화
  - 컴파일러가 debug와 다르게 release에서 알아서 최적화해준다.
```c
#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
	int m_num;
	int m_den;
public:
	Fraction(int num = 0, int den = 1)
		: m_num(num), m_den(den)
	{
		assert(den != 0);
	}
	// copy constructor
	Fraction(const Fraction& fraction)
		:m_num(fraction.m_num), m_den(fraction.m_den)
	{}

	friend std::ostream& operator <<(std::ostream& out, const Fraction& f)
	{
		cout << f.m_num << "/" << f.m_den << endl;
		return out;
	}
};

Fraction doSomething()
{
	Fraction temp(1, 2);
	cout << &temp << endl;
	return temp;
}

int main()
{
	Fraction result = doSomething();
	// debug 모드에서는 doSomething함수의
	// temp 주소와 아래 result 주소가 다르다
	// 그리고 copy constructor도 실행된다

	// 하지만 release 모드에서는 컴파일러가
	// 알아서 copy가 아니라 temp 그대로 result에
	// 넣어준다. 주소가 똑같이 나온다!
	cout << &result << endl;
	return 0;
}
```
### 9.10 변환 생성자, explicit, delete
-  explicit
- delete
  - 예를 들면, 이전 버전에서 사용하던 방법을 못 쓰도록 막아주는 역할을 한다
```c
#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
	int m_num;
	int m_den;
public:
	Fraction(char) = delete;

	explicit Fraction(int num = 0, int den = 1)
		: m_num(num), m_den(den)
	{
		assert(den != 0);
	}

	Fraction(const Fraction& fraction)
		:m_num(fraction.m_num), m_den(fraction.m_den)
	{}

	friend std::ostream& operator <<(std::ostream& out, const Fraction& f)
	{
		cout << f.m_num << "/" << f.m_den << endl;
		return out;
	}
};

void doSomething(Fraction frac)
{
	cout << frac << endl;
}

int main()
{
	Fraction frac(7);

	// explicit 붙이기 전에는
	// 아래 값들 정상 작동
	doSomething(frac);
	doSomething(Fraction(7));
	doSomething(7); // 생성자처럼 자동으로 바꿔줌

	// explicit 넣으면
	// 조건이 까다로워진다고 이해하면 된다
	// 따라서 이렇게만 가능해진다
	doSomething(frac);
	doSomething(Fraction(7));

	// delete
	Fraction frac('c');

	return 0;
}
```
### 9.11 대입 연산자 오버로딩, 깊은 복사, 얕은 복사
- 얕은 복사
  - 기본 복사 생성자 호출 (아무 구현 안했을 때)
  - 아래는 동적할당 예시
  - 포인터 :  주소값 복사하는데 문제는 복사값 사라지면서 deconstructor가 실행되면서 delete가 실행되면 그 메모리가 지원지면서 원본으로도 값을 읽을 수 없다.
```c
#include <iostream>
#include <cassert>
using namespace std;

class MyString
{
public:
	char* m_data = nullptr;
	int m_length = 0;
public:
	MyString(const char* source = "")
	{
		assert(source);
		m_length = std::strlen(source) + 1;
		m_data = new char[m_length]; // 동적할당

		for (int i = 0; i < m_length; ++i)
			m_data[i] = source[i];

		m_data[m_length - 1] = '\0';
	}
	~MyString()
	{
		delete[] m_data;
	}
	char* getString() { return m_data; }
	int getLenghth() { return m_length; }
};

int main()
{
	MyString hello("Hello");

	cout << (int*)hello.m_data << endl;
	cout << hello.getString() << endl;

	// 얕은 복사
	// copy는 해당 scope를 벗어나면 지워진다
	// 지워질때 delete 실행해서 메모리 해제
	{
		MyString copy = hello; // 복사생성자 호출
		cout << (int*)copy.m_data << endl;
		cout << copy.getString() << endl;
	}
	// 이상한 값이 나온다 with 에러
	// 왜? 원래의 데이터도 지워지는 것
	cout << hello.getString() << endl;

	return 0;
}
```
- 깊은 복사
  - 위와는 다르게 복사 우리가 구현
  - 위와 다르게 당연히 ```copy``` 의 주소가 다르다
  - 내가 복사를 구현할 시간이 없다면 ?? 막아버리자. ```MySting(const MyString &source) = delete```

- 대입연산자

```c
#include <iostream>
#include <cassert>
using namespace std;

class MyString
{
public:
	char* m_data = nullptr;
	int m_length = 0;
public:
	MyString(const char* source = "")
	{
		assert(source);
		m_length = std::strlen(source) + 1;
		m_data = new char[m_length]; // 동적할당

		for (int i = 0; i < m_length; ++i)
			m_data[i] = source[i];

		m_data[m_length - 1] = '\0';
	}
	// 깊은 복사
	// 그냥 포인터를 복사하는게 아니라 값을 복사
	MyString(const MyString& source)
	{
		cout << "copy" << endl;
		m_length = source.m_length;

		if (source.m_data != nullptr)
		{
			m_data = new char[m_length];
			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = nullptr;
	}
	// 대입연산자
	MyString& operator = (const MyString& source)
	{
		cout << "assignment" << endl;
		if (this == &source)
			return * this;

		delete[] m_data;
		m_length = source.m_length;

		if (source.m_data != nullptr)
		{
			m_data = new char[m_length];
			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = nullptr;

		return * this;
	}
	~MyString()
	{
		delete[] m_data;
	}
	char* getString() { return m_data; }
	int getLenghth() { return m_length; }
};

int main()
{
	MyString hello("Hello");

	cout << (int*)hello.m_data << endl;
	cout << hello.getString() << endl;

	{
		MyString copy = hello; // 복사생성자 호출
		cout << (int*)copy.m_data << endl;
		cout << copy.getString() << endl;
	}

	cout << hello.getString() << endl;

	//
	MyString str1 = hello; // 여기는 복사생성자
	MyString str2;
	str2 = hello; // 여기에 대입연산자

	return 0;
}
```
### 9.12 이니셜라이져 리스트 initializer list
