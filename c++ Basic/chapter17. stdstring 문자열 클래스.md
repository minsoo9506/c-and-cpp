### 17.1 std::string과 std::wstring
```c
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // 둘다 basic_string이라는 클래스의 instance
    // string : 자료형으로 char이 들어감
    // wstring : 자료형으로 wchar_t이 들어감
    std::string string;
    std::wstring wstring;

    // 주로 길이가 긴 character, unicode에서 사용
    wchar_t wc;

    return 0;
}
```
### 17.2 std::string의 생성자들과 형변환
- 생성자들
```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    //
    std::string my_string("my string");
    std::string second_string(my_string); // 복사가능
    std::string second_string(my_string, 3); // 3번째 글자부터
    std::string second_string(my_string, 3, 5); // 3번째부터 5글자

    //
    std::vector<char> vec;
    for (auto e : "Today is a good day.")
        vec.push_back(e);

    std::string my_string(vec.begin(), vec.end());
    std::string my_string(vec.begin(), std::find(vec.begin(),vec.end(), 'y')); // y앞까지 나옴
}
```

- 형 변환
```c
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
std::string ToString(T x)
{
    std::ostringstream osstream;
    osstream << x;
    reuturn osstream.str();
}

template <typename T>
bool FromString(const std::string& str, T& x)
{
    std::istringstream isstream(str);
    return (isstream >> x) ? true : false;
}

int main()
{
    // std::to_string
    // string으로 만들어준다
    std::string my_str(std::to_string(1004));
    my_str += std::to_string(20);
    std::cout << my_str << std::endl; // 1024
    int i = std::stoi(my_str); // 반대전환


    std::string my_str(ToString(1004));
    double d;
    if (FromString(my_str, d))
        std::cout << d << std::endl;
    else
        std::cout << "Cannot convert string to double" << std::endl;

    return 0;
}
```

### 17.3 std::string의 길이와 용량
- string에서 길이와 용량이 다르다
  - vector와 비슷하다
  - 메모리 재할당 등에 걸리는 시간을 줄이기 위해 길이보다 크게 용량을 갖는다 (메모리)

```c
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string my_str("0123456789");

    cout << my_str.size() << endl;  // 10 , null character는 count x
    cout << my_str.empty() << endl; // 0, 비어있으면 1
    cout << my_str.length() << endl; // 10
    cout << my_str.capacity() << endl; // 15, 여분의 용량 할당
    cout << my_str.max_size() << endl; // 최대 몇글자가 들어가는가?

    my_str.reserve(1000); // 1000글자 확보하고 싶다

    return 0;
}
```
### 17.4 std::string 문자 접근하기와 배열로의 변환
```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string my_str("abcdefg");

    cout << my_str[0] << endl; // a
    my_str[4] = 'Z';
    cout << my_str << endl; // abcdZf

    // 예외처리
    try
    {
        my_str.at(100) = 'X';
    }
    catch (std::exception & e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
```
- c스타일 배열로 변환
  - string은 null character가 안 붙는데 ```c_str```하면 붙여진다
```c
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string my_str("abcdefg");

    cout << my_str.c_str() << endl;
    // cout << my_str.data() << endl; 똑같은 역할

    //
    char buf[20];

    my_str.copy(buf, 5, 0); // 5글자 복사 0부터 (null character는 안 붙여줌)
    cout << buf << endl; // 5글자 뒤에 이상한 글자 나옴: null character가 없어서!
    buf[5] = '\0';
    cout << buf << endl;

    return 0;
}
```

### 17.5 string 대입, 교환, 덧붙이기, 삽입
```c
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str1("one");
    string str2;

    str2 = str1;
    str2 = "two";
    str1 += "three";
    str2.append("two");
    cout << str2 << endl; // twotwo

    std::swap(str1, str2);
    // str1.swap(str2); 똑같음

    string str("aaaa");
    str.insert(2, "bb"); // 2부터 bb삽입
    cout << str << endl;

    return 0;
}
```
