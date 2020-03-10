### 14.1 예외처리의 기본
- 비정상적인 상황에서도 안정적인 프로그램을 만들기 위해서
  - 여러가지 방법 존재
  - 이전에 배웠던 assert도 그 중 하나
- 전통적인 방법
```c
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int findFirstChar(const char* string, char ch)
{
    for (std::size_t index = 0; index < strlen(string); ++index)
        if (string[index] == ch)
            return index;

    return -1;
}

double divide(int x, int y, bool& success)
{
    if (y == 0)
    {
        success = false;
        return 0.0;
    }
    success = false;
    return static_cast<double>(x) / y;
}

int main()
{   
    bool success;
    double result = divide(5, 3, success);

    if (!success)
        std::cerr << "An error occurred" << std::endl; // cerr : cout이랑 같은데 사용처가 다른 느깜
    else
        std::cout << "Result is " << result << std::endl;

    std::ifstream input_file("temp.txt");
    if (!input_file)
        std::cerr << "Cannot open file" << std::endl;

    return 0;
}
```
- 예외처리 방법
  - try, catch, throw
  - 예외처리 시에는 auto같은 방법 사용 불가. 엄격하다고 이해하면 된다.
  - throw하는 type에 맞춰서 catch에서 받는다. 없으면? run time error
```c
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{   
    double x;
    cin >> x;

    try
    {
        if (x < 0.0) throw std::string("Negative input");
        cout << std::sqrt(x) << endl;
    }
    catch (std::string error_message) // error_message는 throw한것
    {
        cout << error_message << endl;
    }
    catch (int x) // 만약 throw 뒤에 int로 바꾸면 얘가 실행
    {
        cout << "int :" << x << endl;
    }

    return 0;
}
```

### 14.2 예외처리와 스택 되감기 stack unwinding
- 강의 참고

### 14.3 예외 클래스와 상속
- 예외 클래스 만들기
```c
#include <iostream>
using namespace std;

class Exception
{
public:
    void report() { cerr << "Exception report" << endl; }
};

class MyArray
{
private:
    int m_data[5];
public:
    int& operator [] (const int& index)
    {
        // if (index < 0 || index >= 5) throw - 1;
        // member function안에서도 throw를 할 수 있구나
        // 그렇다면 class를 throw 해보자
        if (index < 0 || index >= 5) throw Exception();
        return m_data[index];
    }
};

void doSome()
{
    MyArray my_array;

    try
    {
        my_array[100];
    }
    catch (const int& x)
    {
        cerr << "Exception" << x << endl;
    }
    //
    catch (Exception & e)
    {
        e.report();
    }
}

int main()
{   
    doSome(); // Exception report

    return 0;
}
```
- 상속
```c
#include <iostream>
using namespace std;

class Exception
{
public:
    void report() { cerr << "Exception report" << endl; }
};
// 상속
class ArrayException : public Exception
{
public:
    void report()
    {
        cerr << "Array exception" << endl;
    }
};

class MyArray
{
private:
    int m_data[5];
public:
    int& operator [] (const int& index)
    {
        if (index < 0 || index >= 5) throw ArrayException();
        return m_data[index];
    }
};

void doSome()
{
    MyArray my_array;

    try
    {
        my_array[100];
    }
    // 주의
    // Exception부분을 먼저 코딩하면
    // 부모 class에서 잡아버려서
    // Exception 이 출력된다
    catch (ArrayException & e)
    {
        e.report();
    }
    catch (Exception & e)
    {
        e.report();
    }
}

int main()
{   
    doSome(); // Array exception

    return 0;
}
```
- rethrow
```c
#include <iostream>
using namespace std;

class Exception
{
public:
    void report() { cerr << "Exception report" << endl; }
};
// 상속
class ArrayException : public Exception
{
public:
    void report()
    {
        cerr << "Array exception" << endl;
    }
};

class MyArray
{
private:
    int m_data[5];
public:
    int& operator [] (const int& index)
    {
        if (index < 0 || index >= 5) throw ArrayException();
        return m_data[index];
    }
};

void doSome()
{
    MyArray my_array;

    try
    {
        my_array[100];
    }

    catch (ArrayException & e)
    {
        cout << "doSome()" << endl;
        e.report();
        // rethrow
        throw e;
    }
    catch (Exception & e)
    {
        e.report();
    }
}

int main()
{   
    // rethrow안하면 원래 doSome에서만
    // 예외를 받아주고 끝
    // rethrow하면 뒤의 catch부분도 실행
    try
    {
        doSome();
    }
    catch(ArrayException & e)
    {
        cout << "main" << endl;
        e.report();
    }

    return 0;
}

```
### 14.4 std::exception 소개
- 예외와 관련하여 많은 구현 존재
- std::exception은 부모 class로 구현되어 있고 자식 class가 엄청 많다
```c
#include <iostream>
#include <exception>
#include <string>
using namespace std;

int main()
{   
    try
    {
        std::string s;
        s.resize(-1);
        // resize에 -1 과 같은 이상한 값이 들어오면
        // throw하도록 구현이 되어있다
    }
    catch (std::exception & exception)
    {
        std::cout << typeid(exception).name() << std::endl;
        // exception의 자식들중에 resize가 던진게 무엇인지
        // 즉, 어떤 exception을 발생시켰는지
        // class std::length_error 로 나온다
        std::cerr << exception.what() << std::endl;
        // string too long 이라고 나온다
        // 뭔지 알려주는 것! what
    }

    return 0;
}
```
- 그러면 우리가 exception의 자식들중에 원하는 것 가져다 쓸수도 있겠다
  - catch 시에도 원하는 자식으로 받을 수도 있다
  - 근데 귀찮으니까 그냥 부모로 받아러 알아서해주도록 하는 것이다
```c
try
{
  throw std::runtime_error("Bad thing happened");
}
catch(std::exception & exception)
{
  ~~
}
```
- exception 직접 만들기
  - std::exception을 상속하여 구현
```c
#include <iostream>
#include <exception>
#include <string>
using namespace std;

class CustomException : public std::exception
{
public:
    // 아래처럼 override해줘야 한다
    const char* what() const noexcept override
    {
        return "Custom exception";
    }
};

int main()
{   
    try
    {
        throw CustomException();
    }
    catch (std::exception & exception)
    {
        std::cout << typeid(exception).name() << std::endl;
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}
```
### 14.5 함수 try
- initializer list 시 발생하는 예외
  - 생성자에 try 구문을 사용한다
  - 원래 ```B b(0)``` 에서 이미 catch를 하였기 때문에 뒷부분의 ```Catch in main()```이 실행되지 않는데
  - 생성자에 try 사용하면  rethrow해준 것처럼 뒷부분도 실행된다.
```c
#include <iostream>
using namespace std;

class A
{
private:
    int m_x;
public:
    A(int x) : m_x(x)
    {
        if (x <= 0)
            throw 1;
    }
};

class B : public A
{
public :
    B(int x) try : A(x)
    {
        // do initialization
    }
    catch (...)
    {
        cout << "Catch in B constructor" << endl;
    }
};

int main()
{   
    try
    {
        B b(0);
    }
    catch (...)
    {
        cout << "Catch in main()" << endl;
    }
    // 결과로
    // Catch in B constructor
    // Catch in main()
    // 나온다

    return 0;
}
```

### 14.6 예외처리의 위험성과 단점
- 메모리 누수 조심
  - 아래와 같은 경우 delete를 못하고 throw가 되어버릴수도 있다.
```c
try
{
  int * i = new int[10000];
  throw "error";
  delete[] i;
}
```
- 소멸자 안에서는 throw 못하게 되어있다.
- 모든 오류를 예외처리로 잡으려고 하지 말아라.
