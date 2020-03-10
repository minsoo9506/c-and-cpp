### 11.1 상속의 기본 1
```c
#include <iostream>
using namespace std;

class Mother
{
private:
	int m_i;
public:
	void setValue(const int& i_in) { m_i = i_in; }
	int getValue() { return m_i; }
};

class Child : public Mother // private도 가능, 뒤에서 배움
{
// 아무것도 없어도 부모한테 상속받았으니 사용가능
};

int main()
{
	Child child;
	child.setValue(128);
	cout << child.getValue() << endl; // 128
	return 0;
}
```
- 부모 class에 있는 member와 같은 이름을 자식 class에서 구현하면?
  - 자식 class 구현한 것으로 된다
- 부모의 private은 자식도 접근 불가 그렇다면?
  - ```protected``` 사용 : private랑 같은데 자식에게는 허용
  - ```Mother::setValue(i_in)``` 이런식도 가능 (private 사용할거면)

```c
#include <iostream>
using namespace std;

class Mother
{
private:
	int m_i;
public:
	void setValue(const int& i_in) { m_i = i_in; }
	int getValue() { return m_i; }
};

class Child : public Mother
{
private:
	double m_d;
public:
	void setValue(const int& i_in, const double& d_in)
	{
		// setValue(i_in); 부모, 자식 모두에게 있어서 구분불가
		// m_i = i_in; private라 불가능
		Mother::setValue(i_in); // 이렇게 Mother 함수라고 명시
		m_d = d_in;
	}
	void setValue(const double& d_in) { m_d = d_in; }
	int getValue() { return m_d; }
};

int main()
{
	Child child;
	child.Mother::setValue(1024);
	child.setValue(128);
        cout << child.Mother::getValue() << endl;
	cout << child.getValue() << endl;
	return 0;
}
```
- 부모 class에 생성자가 있으면 자식 class가 생성될 때 부모 class의 생성자도 실행된다
```c
#include <iostream>
using namespace std;

class Mother
{
private:
	int m_i;
public:
	Mother(const int & i_in)
		: m_i(i_in)
	{}
	void setValue(const int& i_in) { m_i = i_in; }
	int getValue() { return m_i; }
};

class Child : public Mother
{
private:
	double m_d;
public:
	Child(const int& i_in, const double& d_in)
		// : m_i(i_in), m_d(d_in)  원래 이런식으로 했는데 안됨
		: Mother(i_in), m_d(d_in) // 부모class의 생성자가 있는 경우
	{   
		// 부모class의 생성자가 없으면 아래와 같이 가능
		// Mother::setValue(i_in);
		// m_d = d_in;
	}

	void setValue(const int& i_in, const double& d_in)
	{
		Mother::setValue(i_in);
		m_d = d_in;
	}
	void setValue(const double& d_in) { m_d = d_in; }
	int getValue() { return m_d; }
};

int main()
{
	Child child(1024,128);
	cout << child.Mother::getValue() << endl; // 1024
	cout << child.getValue() << endl;  // 128
	return 0;
}
```

### 11.2 상속의 기본 2
- teacher.h와 student.h는 person.h이라는 공통점이 있다. 이에 따라 중복되는 점을 최대한 뽑아서 person.h에 옮긴다.
- 상속예시코딩

### 11.3 유도된 클래스들의 생성 순서
- 이전에 봤듯이 자식클래스로 instance를 만들면 자식클래스의 생성자보다 부모클래스의 생성자가 항상 먼저 실행된다.
  - 자식클래스의 instance 생성 -> 부모클래스의 초기화, 생성자 호출 -> 자식클래스의 초기화 실행(초기화 설정했으면) -> 자식클래스의 생성자 body 실행
  - 그래서 자식클래스에서 부모의 멤버변수를 초기화 못하고 body에서 바꿀수 있는 것 (물론, public or protected이고 부모에서 초기화된 경우에 제한)

```c
#include <iostream>
using namespace std;

class Mother
{
public:
	Mother(const int &i_in=0)
		: m_i(i_in)
	{
		cout << "Mother constructor" << endl;
	}
	int m_i;
};

class Child : public Mother
{
public:
	double m_d;
public:
	Child()
		: m_d(1.0) //  m_i(1) 이렇게 부모 member 여기서 초기화 불가
     // : Mother(1), m_d(1.0) 이렇게 가능, 이렇게 많이 쓰는듯 (private일때도 접근가능)
	{
		// 부모가 초기화했으면 여기서 수정은 가능
		cout << "Child constructor" << endl;
	}
};

int main()
{
	Child child;
	// Mother constructor 나오고
	// Child 나온다
	return 0;
}
```

### 11.4 유도된(derived) 클래스들의 생성과 초기화
- 자식클래스에서 sizeof 해보면 부모 것도 다 사용가능하도록 메모리를 할당 받는다
```c
#include <iostream>
using namespace std;

class Mother
{
private:
	int m_i;
public:
	Mother(const int &i_in=0)
		: m_i(i_in)
	{
		cout << "Mother constructor" << endl;
	}
};

class Child : public Mother
{
public:
	double m_d;
	int m_temp;
public:
	Child()
		: m_d(1.0), m_temp(1) , Mother(1024)
	{
		cout << "Child constructor" << endl;
	}
};

int main()
{
	cout << sizeof(Mother) << endl; // 4
	cout << sizeof(Child) << endl; // 24 : 부모,본인뿐만 아니라 패딩때문에 더 커진 상태

	return 0;
}
```
- 생성, 소멸 순서
```c
#include <iostream>
using namespace std;

class A
{
public:
	A(int a){ cout << "A : " << a << endl; }
	~A() { cout << "Destructor A" << endl; }
};

class B : public A
{
public:
	B(int a, double b)
		: A(a)
	{ cout << "B: " << b << endl; }
	~B() { cout << "Destructor B" << endl; }
};

class C : public B
{
public:
	C(int a, double b, char c)
		: B(a, b)
	{ cout << "C: " << c << endl; }
	~C() { cout << "Destructor C" << endl; }
};

int main()
{
	C c(1024, 3.14, 'a');
	// constructor는 A B C
	// destructor는 C B A 순서대로
	return 0;
}
```

### 11.5 상속과 접근 지정자
- 손자 class 에게 영향주는 것 주의

```c
#include <iostream>
using namespace std;

class Base
{
public:
    int m_public;
protected:
    int m_protected;
private:
    int m_private;
};

class Derived1 : public Base
{
public:
    Derived1()
    {
        m_public;
        m_protected;
        //m_private; 에러
    }
};
class Derived2 : protected Base
{
public:
    Derived2()
    {
        m_public;
        m_protected;
        // m_private; 에러
    }
};
class Derived3 : private Base
{
public:
    Derived3()
    {
        m_public;
        m_protected;
        // m_private; 에러
    }
};

class Grandchild : public Derived2
{
public:
    Grandchild()
    {
        Derived2::m_protected;
        // Derived3::m_protected; 에러
        // Derived3는 Base를 private로 가져와서
        // Derived3 안에서 m_public, m_protected, m_private 들이 private처럼 작동
    }
};

```

### 11.6 유도된 클래스에 새로운 기능 추가하기
- 부모class 변수를 자식class에서 접근하여 뭔가 하고 싶다
	- 부모class에서 protected로 바꿔주고 접근
	- 주로 부모class의 변수와 자식class의 변수를 같이 함수에서 뭔가 해야 하는 경우에 사용

```c
#include <iostream>
using namespace std;

class Base
{
protected:
    int m_value;
public:
    Base(int value)
        : m_value(value)
    {}
};

class Derived : public Base
{
public:
    Derived(int value)
        : Base(value)
    {}
    void dosomething(int value)
    {
        Base::m_value = value;
        //do some work with the variable
    }
};
```

### 11.7 상속받은 함수를 오버라이딩 하기
- 부모class의 함수를 상속받으면
	- 오버라이딩 안하면 부모class함수 그대로 실행
- 상속받고 오버라이딩하면 당연히
	- 새로 만든 함수가 실행
- 그렇다면 부모 함수와 자식 함수 (같은이름) 둘 다 사용하고 싶다면?
	- 아래와 같이 가능
	- 변수관련해서 static_cast도 사용가능

```c
#include <iostream>
using namespace std;

class Base
{
protected:
    int m_i;
public:
    Base(int value = 0)
        : m_i(value)
    {}
    void print() { cout << "Base" << endl; }
};

class Derived : public Base
{
private:
    double m_d;
public:
    Derived(int value = 0)
        : Base(value)
    {}
    void print()
    {
        Base::print(); // 이렇게 함수 앞에 class 이름 써서
        cout << "Derived" << endl;
    }
};

int main()
{
    Base b;
    b.print();
    Derived d;
    d.print();

    return 0;
}
```

### 11.8 상속받은 함수를 감추기
```c
#include <iostream>
using namespace std;

class Base
{
protected:
    int m_i;
public:
    Base(int value = 0)
        : m_i(value)
    {}
    void print() { cout << "Base" << endl; }
};

class Derived : public Base
{
private:
    double m_d;
public:
    Derived(int value = 0)
        : Base(value)
    {}

    // protected 가 public으로 바뀌는 효과
    using Base::m_i;

    // 반대로 public을 막아보자
private:
    using Base::print;
};

int main()
{
    Derived d(7);

    // 원래 접근 불가인데
    // using Base::m_i;
    // 하면서 public이 되어 접근 가능
    d.m_i = 7;
    cout << d.m_i << endl; // 7

    // 사용불가
    d.print();

    return 0;
}
```

### 11.9 다중 상속
```c
#include <iostream>
using namespace std;

class USBDevice
{
private:
    long m_id;
public:
    USBDevice(long id) : m_id(id) {}
    long getID() { return m_id; }
    void plugAndPlay() {}
};

class NetworkDevice
{
private:
    long m_id;
public:
    NetworkDevice(long id) : m_id(id) {}
    long getID() { return m_id; }
    void networking() {}
};

class USBNetworkDevice : public USBDevice, public NetworkDevice
{
public:
    USBNetworkDevice(long usb_id, long net_id)
        : USBDevice(usb_id), NetworkDevice(net_id)
    {}
};

int main()
{
    USBNetworkDevice my(3.14, 6.3);

    // my.getID(); 에러발생

    // 이렇게 구분해서 사용
    my.USBDevice::getID();
    my.NetworkDevice::getID();

    return 0;
}
```
