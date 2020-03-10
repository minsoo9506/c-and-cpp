### 19.1 람다 함수와 std::function
```c
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 맨 뒤 bind를 위한 함수와 클래스
void goodbye(const string& s)
{
    cout << "Goodbye" << s << endl;
}
class object
{
public:
    void hello(const string& s)
    {
        cout << "Hello" << s << endl;
    }
};

int main()
{
    // lambda
    // lambda-introducer : []
    auto func = [](const int& i)->void {cout << "Hello, world" << endl; };
    func(123);
    // 이렇게 가능! 진짜 익명 함수구나~
    [](const int& i)->void {cout << "Hello, world" << endl; }(123);

    // [] 에 & 넣어주면 해당 영역 변수를 reference로 사용가능
    // class의 멤버를 [this]로 사용 자주 한다고 한다
    {
        string name = "JackJack";
        [&]() {std::cout << name << endl; }();
    }
    //
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    auto func2 = [](int val) {cout << val << endl; };
    for_each(v.begin(), v.end(), func2);
    // 근데 주로 아래와 같이 사용!!
    for_each(v.begin(), v.end(), [](int val) {cout << val << endl; });
    //
    cout << []()->int {return 1; }() << endl;

    // std::function
    // function pointer를 체계화한 느낌
    std::function<void(int)> func3 = func2;
    func3(123);
    // bind 사용하면 parameter type 생략
    std::function<void()> func4 = std::bind(func3, 456);
    func4();

    // bind 에서 placeholder
    {
        object instance;
        auto f1 = std::bind(&object::hello, &instance, std::placeholders::_ 1);
        f1("World");

        auto f2 = std::bind(&goodbye, std::placeholders::_ 1);
        f2("World");
    }

    return 0;
}
```
### 19.2 C++17 함수에서 여러개의 리턴값 반환하기
- 함수에서는 기본적으로 return 값이 하나밖에 안됨
- tuple (조금 코딩이 길다)
```c
#include <iostream>
#include <tuple>

using namespace std;

tuple<int, int> my_func()
{
    return tuple<int, int>(123,456);
}

int main()
{
    tuple<int, int> result = my_func();
    cout << std::get<0>(result) << endl;

    return 0;
}
```
- c++ 17
```c
#include <iostream>
#include <tuple>

using namespace std;

// auto
auto my_func()
{
    // <int> 사라짐
    return tuple(123,456,789);
}

int main()
{   
    // 받는 것도 이렇게 가능 like python
    auto [a, b, c] = my_func();
    cout << a << endl; // 123

    return 0;
}
```
### 19.3 std::thread 와 multithreading의 기초
- cpu에 있는 여러개의 core가 있는 것을 이용 (cpu가 여러개 : 멀티프로세스)
- Process를 여러개의 Thread들이 나눠서 일하자
- main thread가 thread들을 시킨다
```c
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
using namespace std;

int main()
{   
    cout << std::thread::hardware_concurrency() << endl;
    cout << std::this_thread::get_id() << endl; // 이 thread의 name 이라고 생각하면 된다

    // multithread
    const int num_pro = std::thread::hardware_concurrency();

    cout << std::this_thread::get_id() << endl; // main thread

    // 그냥 아무것도 안하고 while문 돌려보자 with lambda 함수
    std::thread t1 = std::thread([]() {
        cout << std::this_thread::get_id() << endl;
        while (true) {}});

    std::thread t2 = std::thread([]() {
        cout << std::this_thread::get_id() << endl;
        while (true) {}});

    t1.join(); // thread가 끝날때까지 기다린다의 의미
    t2.join();

    return 0;
}
```
```c
#include <iostream>
#include <thread>
#include <chrono> // 시간 관련
#include <vector>
#include <mutex> // thread 사용하면 cout 출력이 이상해지는데 이를 위해 사용
using namespace std;

mutex mtx;

int main()
{   
    auto work_func = [](const string& name)
    {
        for (int i = 0; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(200));

            mtx.lock();
            cout << name << " " << std::this_thread::get_id() << " is working " << i << endl;
            mtx.unlock();
        }
    };

    std::thread t1 = std::thread(work_func, "minsoo");
    std::thread t2 = std::thread(work_func, "songsong");

    t1.join();
    t2.join();

    return 0;
}
```
### 19.4 Race condition
- 같은 메모리 공간을 사용하기 때문에 생기는 문제 존재
```c
#include <iostream>
#include <thread>
#include <chrono> // 시간 관련
#include <vector>
#include <mutex> // thread 사용하면 cout 출력이 이상해지는데 이를 위해 사용
#include <atomic>
using namespace std;

int main()
{   
    int shared_memory(0);

    auto count_func = [&]()
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            // 이거는 공부를 위해 눈에 보이도록!
            shared_memory++;
        }
    };

    std::thread t1 = std::thread(count_func); // thread 하나만 하면 문제 없음
    std::thread t2 = std::thread(count_func);
    // 근데 2개의 thread로 하면 문제 발생 2000이 아니고 1968 막 이런 숫자 나옴
    // 병렬처리 프로그래밍할때 까다로운 점! shared_memory를 바꾸는 과정이
    // 1.cpu로 shared_memory에 있는 값을 가져와서
    // 2. 더하고
    // 3. 바뀐 값을 다시 보내서 덮어쓴다
    // 근데 t1이 cpu로 읽어들인 사이에 t2가 값을 바꾸고 근데 그 뒤에
    // t1이 다시 값을 보내서 덮으면? 하나가 빠지는 격!!

    t1.join();
    t2.join();

    cout << "result" << endl;
    cout << shared_memory << endl;
    return 0;
}
```
- atomic 으로 문제 해결
  - 위에서 3단계를 한 번에 묶어버리는 것
  - 단점 :  조금 느림. 꼭 필요한 곳에만 쓰자
```c
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
using namespace std;

int main()
{   
    atomic<int> shared_memory(0);

    auto count_func = [&]()
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            // 이거는 공부를 위해 눈에 보이도록!
            shared_memory++; // atomic ++ 이 오버로딩 된다
        }
    };

    std::thread t1 = std::thread(count_func);
    std::thread t2 = std::thread(count_func);

    t1.join();
    t2.join();

    cout << "result" << endl;
    cout << shared_memory << endl; // 2000
    return 0;
}
```
- ```mtx.lock()``` 사용하면 atomic이랑 같은 역할 가능
  - thread가 해당 부분에 한번에 한 개만 접근하도록 한다
  - ```std::lock_guard```, ```std::lock_scoped``` 도 같은 역할
```c
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <mutex>
using namespace std;

mutex mtx;

int main()
{   
    int shared_memory(0);

    auto count_func = [&]()
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));

            // {} 범위에 해당하도록 하게 해준다
            std::lock_guard lock(mtx); // 이전에 lock, unlock보다 많이 사용
            // std::scoped_lock lock(mtx); // c++17 이게 best
            shared_memory++;
        }
    };

    std::thread t1 = std::thread(count_func);
    std::thread t2 = std::thread(count_func);

    t1.join();
    t2.join();

    cout << "result" << endl;
    cout << shared_memory << endl; // 2000
    return 0;
}
```
### 19.5 작업 기반 비동기 프로그래밍 async, future, promise
- thread와 async는 내부적으로 처리하는 방법이 약간 다르다. 여기서 배우지는 않는다.
- thread는 join 필요, async는 필요없음
```c
#include <iostream>
#include <thread>
#include <future>
using namespace std;

int main()
{   
    // multi-threading 이전에 배운
    {
        int result;
        std::thread t([&] {result = 1 + 2; });
        t.join();
        cout << result << endl;
    }

    // task-based parallelism
    // multi-thread는 thread 자체를 관리하는 것
    // 여기서는 어떤 task를 할 것이냐가 더 주 관점이 코딩
    // 위에는 따로 변수선언
    // 이거는 return을 받는 변수를 할당하는 특징
    // 그리고 async 뒤에 내용은 시간이 엄청 오래걸릴수도 있다
    // 그리고 return을 받는 변수를 할당하는 특징
    // 그래서 fut.get() 은 async 뒤가 다 끝나고 fut에 할당될 때까지 기달
    {
        auto fut = std::async([] {return 1 + 2; });
        cout << fut.get() << endl;
    }

    // future and promise
    {   
        // promise를 거쳐서 future에 가는 느낌
        std::promise<int> prom;
        auto fut = prom.get_future();

        auto t = std::thread([](std::promise<int>&& prom)
        //promise를 parameter로 넣어야함
        {
            prom.set_value(1 + 2);
        }, std::move(prom));

        cout << fut.get() << endl;
        t.join();
    }

    return 0;
}
```
### 19.6 멀티쓰레딩 예제
- 강의 참고

### 19.7 Perfect Forwarding과 std::forward
- dd
```c
#include <iostream>
#include <thread>
#include <utility> // std::forward
using namespace std;

struct Mystruct
{};

void func(Mystruct& s)
{
    cout << "Pass by L-ref" << endl;
}

void func(Mystruct&& s)
{
    cout << "Pass by R-ref" << endl;
}

template<typename T>
void func_wrapper(T t)
{
    func(t);
}

template<typename T>
void func_wrapper_f(T&& t)
{
    func(std::forward<T>(t));
}

int main()
{   
    Mystruct s;
    func(s); // L-value
    func(Mystruct()); // R-value
    // 우리가 의도한대로 오버로딩되서 잘 기능

    // 근데 template을 사용하면..?
    // 잘 안됨 둘 다 L 이 나와버림
    // 이를 해결하기 위해 perfect forwarding!!
    func_wrapper(s);
    func_wrapper(Mystruct());

    // std:: forward 사용하면 잘 된다
    func_wrapper_f(s);
    func_wrapper_f(Mystruct();

    return 0;
}
```
- 뒤예시 강의 참고 10분부터

### 19.9 자료형 추론 Type inference
- 참고 : 선언된 변수에 마우스 올리면 자료형 보인다
- 예시가 너무 많아서 일부 생략 강의 참고
- auto
```c
void ex2()
{
    int x = int();
    auto auto_x = x;
    const int& crx = x;
    auto auto_crx1 = crx;
    // crx 는 const int ref 인데 auto는 그냥 int로 생각
    // 이를 사용하려면 아래처럼 써야됨
    const auto& auto_crx2 = crx;

    // volatile은 값이 자주 변해서 빼달라 라는 거라고 함??
    volatile int vx = 1024;
    auto avx = vx; // 얘도 int만
    volatile auto vavx = vx;
}

// template의 경우
template<class T>
void func_ex3(T arg) {}

void ex3()
{
    const int& crx = 123;
    func_ex3(crx); // 여기도 int만 남는다
}
// 이를 해결하기 위해
// template<class T>
// void func_ex3(const T& arg) {}

void ex4()
{
    const int c = 0;
    auto& rc = c;
    // rc = 123 compile error
    // ref로 가져올려고 할때는 auto가 const int &로 추론
}

void ex5()
{
    int i = 42;
    auto&& ri_i = i; // 알아서 l-value ref로 바꿔서 사용
    auto&& ri_2 = 42;
}

void ex6()
{
    int x = 42;
    const int* p1 = &x;
    auto p2 = p1; // const int* 로 그대로 가져온다
}

```
- decltype
- 변수가 선언이 된 type을 그대로 가져온다
```c
#include <iostream>
using namespace std;

struct S
{
    int m_x;
    S() { m_x = 42; }
};

void ex9()
{
    int x;
    const int cx = 42;
    const int& crx = x;
    const S* p = new S();

    auto a = x;
    auto b = cx;
    auto c = crx;
    auto d = p;
    auto e = p->m_x; // e는 그냥 int

    typedef decltype(x)      x_type;
    typedef decltype(cx)     cx_type;  // const int
    typedef decltype(crx)    crx_type; // const int&
    typedef decltype(p->m_x) p_type;   // int , m_x를 가져와서

    // 괄호가 2개면 ref & 를 붙인다
    typedef decltype((x))    x_type; // &int
}
```
