### 15.1 이동의 의미와 스마트 포인터 소개
- 모던 c++의 스마트 포인터를 통해 delete안해도 되는 것  
  - AutoPtr.h에서 가볍게 구현
- Resource.h : 생성자, 소멸자
```c
#pragma once
#include <iostream>

class Resource
{
public:
	int m_data[100];
public:
	Resource()
	{
		std::cout << "Resource constructed" << std::endl;
	}
	~Resource()
	{
		std::cout << "Resource destroyed" << std::endl;
	}
};
```
- AutoPtr.h
```c
#pragma once

#include <iostream>

template<class T>
class AutoPtr
{
public:
	T* m_ptr = nullptr;
public:
	AutoPtr(T *ptr = nullptr)
		: m_ptr(ptr) {}

	// 소멸자에서 지워준다
	~AutoPtr() { if(m_ptr != nullptr) delete m_ptr; }

	// 객체가 pointer 처럼 작동할 수 있도록
	T& operator*() const { return * m_ptr; } // de reference operator
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};
```
- main.cpp
```c
#include <iostream>
#include "AutoPtr.h"
#include "Resource.h"
using namespace std;

void doSome()
{
    try
    {
        // smart pointer
        AutoPtr<Resource> res(new Resource); // 초기화

        if (true)
        {
            throw - 1;
        }
    }
    catch (...)
    {}
}

int main()
{   
    doSome();
    return 0;
}
```
- 아래 예시처럼 복사하는 경우, 문제 발생
  - res2도 해당 메모리의 주소 (즉, 데이터를 접근할 수 있는 열쇠)를 갖게 된다
  - 근데 자동으로 delete되니까 res2가 해당 주소로 접근하려고 하면 이미 메모리에 데이터를 없는 상태
  - 그래서 에러 발생
```c
AutoPtr<Resource> res1(new Resource)
AutoPtr<Resource> res2 // 초기화 안해서 nullptr 인 상태
cout << res1.m_ptr << endl;
cout << res2.m_ptr << endl;
res2 = res1; // 복사
cout << res1.m_ptr << endl;
cout << res2.m_ptr << endl; // 문제발생
```
- 그럼 위와 같은 문제를 해결하기 위해서?
  - 이동 (소유권 이전 move semantics)
  - res1의 소유권을 박탈! nullptr로 만들어준다.
```c
// AutoPtr.h 에 추가로 구현하면 된다
AutoPtr(AutoPtr &a)
{
  m_ptr = a.m_ptr;
  a.m_ptr = nullptr; // 원래 포인터를 null로
}
AutoPtr & operator = (AutoPtr &a) // 복사였던 operator를 오버라이딩
{
  if(&a == this)
    return * this;

  delete m_ptr;
  m_ptr = a.m_ptr;
  a.m_ptr = nullptr;
  return * this;
}
```

### 15.2 오른쪽값 참조 R-value reference
- && 사용
- 곧 사라질 애들만 받아준다 (즉, R-value)
- 다른 방법으로 해당 내용 접근을 못한다는 의미도 있는 것이다
  - 예를 들어,  ```int& lr1 = x;``` 와 같은 경우 x가 갖는 값은 x와 lr1 둘 다 접근 가능 : L-value reference
  - R-value reference는 그럴 일이 없다
- 따라서 move semantics와 밀접한 관련이 있는 것이다
```c
#include <iostream>
using namespace std;

int main()
{   
    int x = 5; // 여기서 L-value는 x, R-value는 5
    const int cx = 5;

    // L-value reference
    int& lr1 = x;
    // int& lr2 = cx; 불가, const 니까
    // int& lr3 = 4; 불가, 참조하는 변수가 메모리에 있어야 된다
    const int& lr4 = x;
    const int& lr5 = cx;
    const int& lr6 = 5;

    // R-value reference
    // int &&rr1 = x; 불가
    // int &&rr2 = cx; 불가
    int&& rr3 = 5;
    // const int&& lr4 = x; 불가
    // const int&& lr5 = cx; 불가
    const int&& lr6 = 5;

    return 0;
}
```
### 15.3 이동 생성자(Move constructor)와 이동 대입(Move assignment)
- 코드가 많아서 강의참고
- (deep)copy constructor/assignment 와 move constructor/assignment 의 시간을 비교
   - move(shallow copy)가 훨씬 빠르다
   - 내용을 copy하는게 아니라 pointer만 복사
  - 따라서 불필요한 copy를 줄이는 것이 중요하다

### 15.4 std::move
- 얘도 코드 너무 많다
- string 관련 예시
- delete 안해도 없애준다
- compiler에게 맡기는 것이 아니라 꼭 move로 하고 싶을 때 std::move 사용
```c
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{   
    vector<string> v;
    string str = "Hello";

    v.push_back(str);
    cout << str << endl;
    cout << v[0] << endl;
// 개발자들이 push_back 을 이렇게 가능하도록 구현해놓은것
    v.push_back(std::move(str));

    cout << str << endl; // 아무것도 안나옴
    cout << v[0] << v[1] << endl;

    return 0;
}
```

### 15.5 std::unique_ptr
- 얘도 코드 너무 많다
- 데이터의 소유권이 한 곳에만 속할 때 사용하는 스마트 포인터
- delete 안해도 없애준다
- 당연히 unique_ptr 는 복사 불가, move는 가능
- 다른 포인터와 마찬가지로 ```->```,  de-reference 사용 가능
```c
std::unique_ptr<Resource> res(new Resource(10000));

// 주로 아래와 같이 사용
auto res1 = std::make_unique<Resource>(5);
```

### 15.6 std:: shared_ptr
- 내부적으로 같은 곳을 가르키고 있는 포인터가 몇 개인지 세고 있다
- delete 안해도 없애준다
```c
// 주로 이렇게 초기화
auto res1 = std::make_shared<Resource>(5);
```
### 15.7 순환 의존성 문제와 std::weak_ptr
```c
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Person
{
    std::string m_name;
    std::shared_ptr<Person> m_partner;
    // std::weak_prt<Person> m_partner;

public:
    Person(const std::string& name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerup(std::shared_ptr<Person>& p1,
                          std::shared_ptr<Person>& p2)
    {
        if (!p1 || !p2)
            return false;
        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is partnered with" << p2->m_name << "\n";

        return true;
    }
};

int main()
{
    // smart pointer가 잘 해준다
    // 생성, 소멸까지 알아서
    auto lucy = std::make_shared<Person>("Lucy");
    auto ricky = std::make_shared<Person>("Ricky");

    // destructor가 실행 안됨
    // dataleak 발생!
    partnerup(lucy, ricky);
    // 이유?
    // Person 클래스에 shared_ptr로 만든애가 있어서
    // 해결 :  weak_ptr로 바꾸면 된다

    return 0;
}
```
- weak_ptr의 단점 :  바로 사용을 못하고 shared_ptr로 바꿔서 사용해야한다. (```lock```을 이용해야한다)
  - 순환 의존성을 깨기 위해 이렇게 한다고 생각하면 된다
```c
const std::shared_ptr<Person> getPartner() const
{
  return m_partner.lock()
}
```
