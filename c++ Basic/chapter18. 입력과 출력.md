### 18.1 istream으로 입력받기
- 기본적으로 stream은 buffer에 임시적으로 저장된 것에서 조금씩 꺼내오는 방식
- 맨 뒤에 null char 있다
```c
#include <iostream>
#include <iomanip> // input output manipulators
using namespace std;

int main()
{
    char buf[5];

    cin >> buf;
    // 입력을 5개 이상하면 에러발생 : 불편하네 -> setw
    // 적게하는건 상관없음
    cout << buf << endl;

    cin >> setw(5) >> buf;
    // 길게 적어도 상관없다 잘려서 나옴
    // 잘린 것들? 지워지는게 아니라 buffer에 남아있다
    cout << buf << endl;

    cin >> setw(5) >> buf;
    cout << buf << endl; // 잘린 뒷부분 나옴

    return 0;
}
```
```c
#include <iostream>
using namespace std;

int main()
{
    char ch;
    // 하나씩 받아온다
    while (cin >> ch)
        cout << ch; // buffer로부터 계속 가져옴 빈칸은 안나옴

    // cin.get
    // 빈칸도 나오게 하고 싶다면 cin.get
    char ch;
    while (cin.get(ch) >> ch)
        cout << ch;

    // buffer 사용도 가능
    char buf1[5];
    while (cin.get(buf1,5) >> ch)
        cout << ch;

    // cin.getline
    // 한 줄씩 읽는다 그리고 줄바꿈 character도 읽는다고 한다
    char buf2[5];
    cin.getline(buf2, 5);
    cout << buf1 << endl;
    cin.getline(buf2, 5); // 근데 얘는 이전애들과 다르게
    cout << buf1 << endl; // 잘린부분을 못 읽는다
                          // 한줄씩 다 읽어서 buffer에 남은게 없다
    return 0;
}
```
```c
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // buffer size를 고려할 필요없이 동적으로! 편하다
    string buf;
    getline(cin, buf);
    cout << buf << endl;

    char buf[1024];
    cin.ignore(); // 맨앞 한글자 무시, 숫자넣으면 그 수만큼 무시
    cout << (char)cin.peek() << endl; // buffer에서 꺼내지는 않고 맨앞 한글자 보여줌
    cin >> buf;
    cout << buf << endl;

    cin.unget(); // 마지막 글자를 buffer에 넣는다
    cin >> buf;
    cout << buf << endl; // 그래서 마지막 글자 출력

    return 0;
}
```

### 18.2 ostream으로 출력하기
- 여러가지 옵션들이 존재
```c
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout.setf(std::ios::showpos); // + 기호 나옴
    // cout << std::ios::showpos 이런식도 가능
    cout << 108 << endl;
    cout.unsetf(std::ios::showpos); // 다시 안나옴
    cout << 108 << endl;

    // setprecision
    cout << std::setprecision(3) << 123.456 << endl; //123
    cout << std::setprecision(4) << 123.456 << endl; //123.5

    // showpoint;
    cout << std::showpoint;
    cout << std::setprecision(3) << 123.456 << endl;// 123.

    // setw
    cout << std::setw(10) << -1234 << endl; //10자리 채워라
    cout << std::setw(10) << std::left << -1234 << endl;
    cout.fill('*'); //빈칸을 * 로 채운다
    cout << std::setw(10) << -1234 << endl;

    return 0;
}
```

### 18.3 문자열 스트림 string stream
```c
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    stringstream os;
    // 둘다 data 넣기 가능
    os << "Hello world"; // << : insertion operator 사용
    os.str("Hello world");

    // 근데 os.str은 이어붙이기 안됨
    os << "Hello world1";
    os << "Hello world2";
    // os.str("Hello world");

    // 출력
    cout << os.str() << endl;

    return 0;
}
```
```c
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    stringstream os;
    os << "12345 67.89";

    string str1;
    string str2;
    // 빈칸으로 구분
    os >> str1 >> str2;
    cout << str1 << "|" << str2 << endl; // 12345|67.89

    // string stream을 비울려면?
    os.str("");

    return 0;
}
```

### 18.4 흐름 상태 stream states 와 입력 유효성 검증 input validation
- 강의 참고 코드 너무 많음

### 18.5 정규 표현식 소개
```c
#include <iostream>
#include <regex>
using namespace std;

int main()
{
    // \d 랑 [[:digit]] 이랑 같음
    // regex re("\\d"); // 숫자냐?
    // regex re("\\d+"); 숫자 하나이상 가능
    // regex re("\\d*"); 숫자 안 넣어도 가능
    // regex re("[ab]"); a 또는 b만 가능
    // regex re("[[:digit]]"{3}); 숫자 3개 와야된다
    // regex re("[A-Z]+") A~Z 까지 받고 갯수는 하나이상 ㄴ상관
    // regex re("[A-Z]{1,5}") 1~5개 가능
    // regex re("([0-9]{1})([-]?)([0-9]{1,4})");  ?는 있어도 되고 없어도 되고 의미

    string str;

    while (true)
    {
        getline(cin, str);
        if (std::regex_match(str, re))
            cout << "Match" << endl;
        else
            cout << "No match" << endl;
    }
    // print matches 이 부분은 그냥 넘어가도 ㅇㅇ
    // match 되는 것만 출력
    {
        auto begin = std::sregex_iterator(str.begin(), str.end(), re);
        auto end = std::sregex_iterator();
        for (auto itr = begin; itr != end; ++itr)
        {
            std::smatch match = * itr;
            cout << match.str() << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
```
### 18.6 기본적인 파일 입출력
- 지금까지는 console 입출력 공부! 이제는 파일과 관련하여 공부
- 강의 참고 코드 너무 많음

### 18.7 파일의 임의 위치 접근하기
- 강의 참고 코드 너무 많음
