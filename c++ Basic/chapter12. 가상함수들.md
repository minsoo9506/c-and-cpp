### 12.1 다형성의 기본 개념
- 자식 클래스의 객체에 부모 클래스의 포인터를 사용한다면?
  - 자식 클래스의 instance가 부모 클래스의 instance인 것처럼 사용된다
- 그런데 ```virtual```을 사용하면
  - 자식 instance의 특징을 유지하면 사용가능

```c
#include <iostream>
#include <string>
using namespace std;

class Animal
{
protected:
    string m_name;
public:
    Animal(string name)
        : m_name(name)
    {}
    string getName() { return m_name; }

    virtual void speak() const { cout << m_name << "???" << endl; }
};
class Cat : public Animal
{
public:
    Cat(string name)
        : Animal(name)
    {}
    void speak() const { cout << m_name << "Meow" << endl; }
};
class Dog : public Animal
{
public:
    Dog(string name)
        : Animal(name)
    {}
    void speak() const { cout << m_name << "Woof" << endl; }
};


int main()
{
    Animal animal("some");
    Cat cat("my_cat");
    Dog dog("my_dog");

    animal.speak(); // ???
    cat.speak(); // Meow
    dog.speak(); // Woof

    // Before virtual
    // 부모클래스의 포인터객체
    // virtual 안 붙이면 ??? 로 나온다
    Animal* ptr_animal1 = &cat;
    Animal* ptr_animal2 = &dog;
    ptr_animal1->speak(); // ???
    ptr_animal2->speak(); // ???

    // after virtual
    // virtual 붙이면 Meow, Woof 로 나온다
    // 다형성
    // 이렇게 이용하면 편리하네
    Cat cats[] = { Cat("cat1"), Cat("cat2") , Cat("cat3") };
    Dog dogs[] = { Dog("dog1"), Dog("dog2") };

    Animal* my_animal[] = { &cats[0], &cats[1] , &cats[2],
                            &dogs[0], &dogs[1] };
    for (int i = 0; i < 5; ++i)
        my_animal[i]->speak();

    return 0;
}
```

### 12.2 가상 함수와 다형성
- 앞에서는 포인터를 사용한 예제니까 여기서는 참조를 이용해본다
- 뒤에서 배우겠지만 virtual 함수는 스택에 저장되는 것이 아니라 virtual table이라는 특별한 방법으로 저장되고 함수를 불러오기 때문에 속도가 느린 편이다

```c
#include <iostream>
using namespace std;

class A
{
public:
    virtual void print() { cout << "A" << endl; }
};
class B : public A
{
public:
    void print() { cout << "B" << endl; }
};
class C : public B
{
public:
    void print() { cout << "C" << endl; }
};

int main()
{
    A a;
    B b;
    C c;

    A& ref1 = b;
    ref1.print(); // B

    A& ref2 = c;
    ref2.print(); // C

    B& ref3 = c;
    ref3.print(); // C
    // B에는 virtual 함수가 없어도 A를 상속받았기 때문에

    return 0;
}
```

### 12.3 override, final, 공변 반환값
-  override

```c
#include <iostream>
using namespace std;

class A
{
public:
    virtual void print(int x) { cout << "A" << endl; }
};

class B : public A
{
public:
    void print(short x) { cout << "B" << endl; }
};

int main()
{
    A a;
    B b;

    A& ref = b;
    ref.print(1); // A 나온다
    // print의 parameter가 다르면
    // 오버라이딩을 할 수 없다 오버로딩이 되어버림

    return 0;
}
```
```c
//이를 위해서
class B : public A
{
public:
    void print(short x) override { cout << "B" << endl; }
};
// 이렇게 치면 short x 에 빨간줄
// 에러를 컴파일전에 잡아준다
```
- final
  - final 하면 뒤에서 자식 class들이 오버라이딩을 못한다
```c
class A
{
public:
    void print() final { cout << "A" << endl; }
};
```
```c
#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
public:
    void print() { cout << "A" << endl; }
    virtual A* getThis() { return this; }
};

class B : public A
{
public:
    void print() { cout << "B" << endl; }
    virtual B* getThis() { return this; }
};

int main()
{
    A a;
    B b;

    A& ref = b;
    b.getThis()->print(); // B
    ref.getThis()->print(); // A
    // getThis까지는 B의 포인터인데
    // print 할 때 A 포인터로 바꿔버림

    cout << typeid(b.getThis()).name() << endl; // class B*
    cout << typeid(ref.getThis()).name() << endl; // class A*

    return 0;
}
```

### 12.4 가상 소멸자
- 자식 소멸자 먼저 실행되고 부모 소멸자 실행
- 그렇다면 다형성에서는?
  - virtual을 안하면 dataleak 발생 가능성 존재

```c
#include <iostream>
using namespace std;

class Base
{
public:
    ~Base()
    {
        cout << "~Base()" << endl;
    }
};

class Derived : public Base
{
private:
    int* m_array;
public:
    Derived(int length) { m_array = new int[length]; }
    ~Derived()
    {
        cout << "~Derived()" << endl;
        delete[] m_array;
    }
};

int main()
{
    Derived* d = new Derived(5);
    Base* b = d;
    delete b;
    // Base의 소멸자만 실행
    // 따라서 Derived에서 메모리누수 발생
    // 소멸자가 실행안되서 delete가 안되니까

    return 0;
}
```
- virtual 사용하면 우리가 원하는대로 자식소멸자 먼저 실행되고 부모소멸자 실행된다
```c
class Base
{
public:
    virtual ~Base()
    {
        cout << "~Base()" << endl;
    }
};
```
### 12.5 동적 바인딩과 정적 바인딩
- static binding이 더 빠르다
- dynamic binding이 더 유연하다

```c
int main()
{
    int x, y;
    cin >> x >> y;

    int op;
    cout << "0:add, 1:subtract, 2:multiply" << endl;
    cin >> op;

    // Static binding (early binding)
    int result;
    switch (op)
    {
    case 0: result = add(x,y); break;
    case 1: result = sub(x,y); break;
    case 2: result = mul(x,y); break;
    }

    // Dynamic binding (late binding)
    // compile time에 결정되는 것이 아니라
    // runtime에 결정되는 것
    int(*func_ptr)(int, int) = nullptr;
    switch (op)
    {
    case 0: func_ptr = add; break;
    case 1: func_ptr = sub; break;
    case 2: func_ptr = mul; break;
    }

    return 0;
}
```

### 12.6 가상 (함수) 표
- ???  잘 이해 못함. 강의 참고
- class에서 virtual function이 있는 상태
  - instance가 만들어지고
  - virtual table에 함수를 가르키는 주소가 있고
  - 특정 함수가 호출되면 virtual table의 주소를 통해 찾아서 실행

### 12.7 순수 가상 함수, 추상 기본 클래스, 인터페이스 클래스
- 자식 클래스에게 제한을 두는 것
- 순수 가상 함수 :  body가 없어서 자식이 반드시 오버라이딩해야함
- 추상 기본 클래스 : 순수 가상 함수를 포함한 클래스

```c
#include <iostream>
#include <string>
using namespace std;

class Animal
{
protected:
    string m_name;
public:
    Animal(std::string name)
        : m_name(name)
    {}
public:
    string getName() { return m_name; }

    virtual void speak() const = 0; // pure virtual function
    // 자식클래스는 무조건 speak 만들어야한다
};

class Cat : public Animal
{
public :
    Cat(string name)
        : Animal(name)
    {}
    void speak() const { cout << m_name << " Meow " << endl; }
};

class Dog : public Animal
{
public:
    Dog(string name)
        : Animal(name)
    {}
    void speak() const { cout << m_name << " Woof " << endl; }
};

class Cow : public Animal
{
public:
    Cow(string name)
        : Animal(name)
    {}
};

int main()
{
    Animal ani("Hi"); // 에러, 만들어지지가 않는다
    Cow cow("umm"); // 에러, speak가 없어서

    return 0;
}
```
- 인터페이스 : 순수 가상함수로만 이루어진 클래스

```c
#include <iostream>
#include <string>
using namespace std;
// 인터페이스 class IErrorLog
class IErrorLog
{
public:
    virtual bool reportError(const char* errorMessage) = 0;
    virtual ~IErrorLog() {};
};

class FileErrorLog : public IErrorLog
{
public:
    bool reportError(const char* errorMessage) override
    {
        cout << "Writing error to a file" << endl;
        return true;
    }
};

class ConsoleErrorLog : public IErrorLog
{
public:
    bool reportError(const char* errorMessage) override
    {
        cout << "printing error to a console" << endl;
        return true;
    }
};

// paramete가 인터페이스
void dosome(IErrorLog & log)
{
    log.reportError("Runtime error!");
}

int main()
{
    FileErrorLog file;
    ConsoleErrorLog console;

    dosome(file);
    dosome(console);
    // 이런구조로 사용하면 편리
    // 파라미터로는 인터페이스로 받으면
    // 다양한 기능을 사용하는 것처럼

    return 0;
}
```

### 12.8 가상 기본 클래스와 다이아몬드 상속 문제
- 강의 그림 참고

```c
#include <iostream>
using namespace std;

class PoweredDevice
{
public:
    int m_i;

    PoweredDevice(int power)
    {
        cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner : virtual public PoweredDevice //
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice(power)
    {
        cout << "Scanner : " << scanner << '\n';
    }
};

class Printer : virtual public PoweredDevice //
{
public:
    Printer(int Printer, int power)
        : PoweredDevice(power)
    {
        cout << "Printer : " << Printer << '\n';
    }
};

class Copier : public Scanner, public Printer
{
public:
    Copier(int scanner, int Printer, int power)
        : Scanner(scanner, power), Printer(Printer, power),
        PoweredDevice(power) //
    {}
};

int main()
{
    // virtual을 넣기 전
    Copier cop(1, 2, 3); // 생성자 2번 호출
    // PD : 3, Scanner : 1, PD : 3, Printer : 2 이렇게

    cout << &cop.Scanner::PoweredDevice::m_i << endl;
    cout << &cop.Printer::PoweredDevice::m_i << endl;
    // 두개의 주소가 다르다

    // virtual 넣으면
    // 생성자도 한번
    // PD : 3, Scanner : 1, Printer : 2
    // 주소도 같음

    return 0;
}
```

### 12.9 객체 잘림과 reference wrapper
- 주로 자식class가 더 정보가 많다
  - 그렇다면 자식 객체를 부모class에 넣는다면?
  - 짤려버린다

```c
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Base
{
public:
    int m_i = 0;

    virtual void print()
    {
        cout << "I'm Base" << endl;
    }
};
class Derived : public Base
{
public:
    int m_j = 1;
    virtual void print() override
    {
        cout << "I'm derived" << endl;
    }
};

int main()
{
    // 객체 잘림
    Derived d1;
    Base& b1 = d1;
    b1.print(); // I'm derived

    // 일부러 했던 실수로 했던 아래처럼 되면
    // 복사되고 m_j에 대한 정보도 없고 Base 정보만 사용가능
    // 다형성이 사라져서 I'm Base
    Derived d2;
    Base b2 = d2;
    b2.print(); // I'm Base

    // reference wrapper (in functional)
    // vector에는 <Base&> 같이 참조를 넣을수 없다
    Base b3;
    Derived d3;
    std::vector<Base> my_vec;
    my_vec.push_back(b3);
    my_vec.push_back(d3);

    for (auto& ele : my_vec)
        ele.print();
    // I'm Base
    // I'm Base

    // 해결
    // 다형성 유지
    Base b4;
    Derived d4;

    std::vector<std::reference_wrapper<Base>> my_vec;
    my_vec.push_back(b3);
    my_vec.push_back(d3);
    for (auto& ele : my_vec)
        ele.get().print();

    return 0;
}
```

### 12.10 동적 형변환 dynamic casting
```c
#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
    int m_i = 0;

    virtual void print()
    {
        cout << "I'm Base" << endl;
    }
};

class Derived1 : public Base
{
public:
    int m_j = 1024;

    virtual void print() override
    {
        cout << "I'm derived" << endl;
    }
};

class Derived2 : public Base
{
public:
    string m_name = "Dr.Two";

    virtual void print() override
    {
        cout << "I'm derived" << endl;
    }
};

int main()
{
    Derived1 d1;
    Base* base = &d1;
    // 다시 base를 Drived1으로 바꾸고 싶다

    // 동적 형변환
    auto* basetod1 = dynamic_cast<Derived1*>(base);

    cout << basetod1->m_j << endl; // 1024
    basetod1->m_j = 256;
    cout << basetod1->m_j << endl; // 256
    cout << d1.m_j << endl; // 256

    // 그렇다면 이번에는 아예 다른 class Derived2로 동적 형변환 가능?
    // 불가능! 안됨 nullptr 들어갈듯
    // 근데 static_cast는 둘다된다;; 가급적 안쓰는게 좋겠구나

    return 0;
}
```

### 12.11 유도 클래스에서 출력 연산자 사용하기
- 멤버로 만들수 없는 함수를 오버라이딩한 것처럼 사용하기 위해 기능을 위임받은 일반 함수를 만들어서 virtual로 만들어서

```c
#include <iostream>
using namespace std;

class Base
{
public:
    Base(){}
    // friend니까 Base의 member가 아니다
    // overriding이 불가능 하겠구나
    friend std::ostream& operator << (std::ostream& out, const Base& b)
    {
        return b.print(out);
    }
    // 그렇다면 이렇게 member를 만들고 virtual해서 위의 것 사용
    // 그러면 자식이 overriding 가능
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

class Derived : public Base
{
public:
    Derived(){}
    virtual std::ostream& print(std::ostream& out) const override
    {
        out << "Derived";
        return out;
    }
};

int main()
{
    Base b;
    std::cout << b << '\n';  // Base

    Derived d;
    std::cout << d << '\n'; // Derived

    Base& bref = d;
    std::cout << bref << '\n'; // Derived

    return 0;
}
```
