### 16.1 표준 템플릿 라이브러리 (STL), 컨테이너 (Containers) 소개
- STL 4 component
  - Algorithms
  - Containers
  - Functions
  - Iterators

- Containers
  - sequence containters
    - vector, deque
  - associative containers
    - set, multiset, map, multimap
  - containers adapters
    - stack, queue
```c
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void sequence_containers()
{
    // vector
    {
        vector<int> vec;
        for (int i = 0; i < 10; ++i)
            vec.push_back(i); // 뒤에 추가하는 것만 가능
        for (auto& e : vec)
            cout << e << " ";
        cout << endl;
    }
    //deque
    {
        deque<int> deq;
        for (int i = 0; i < 10; ++i)
        {
            deq.push_back(i);
            deq.push_front(i); // 얘는 앞도 가능
        }
        for (auto& e : deq)
            cout << e << " ";
        cout << endl;
    }
}
```
```c
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

void associative_containers()
{
    // set
    // 중복불가
    {
        set<string> str_set;
        str_set.insert("Hello");
        str_set.insert("World");
        str_set.insert("Hello");

        cout << str_set.size() << endl; // 2, 중복안되니까
        for (auto& e : str_set)
            cout << e << " ";
        cout << endl;
    }
    // multiset
    // set이랑 같은데 중복이 허용
    // 넣는 순서가 유지 x, sort되어진다
    {
        multiset<string> str_set;
        str_set.insert("Hello");
        str_set.insert("World");
        str_set.insert("Hello");

        cout << str_set.size() << endl; // 3
        for (auto& e : str_set)
            cout << e << " ";
        cout << endl;
    }
    // map
    // 넣는 순서가 유지 x, sort되어진다
    {
        map<char, int> map; // 하나씩 대응시킨다
        map['a'] = 10;
        map['b'] = 20;

        cout << map['a'] << endl;

        map['a'] = 100; // 수정가능

        for (auto& e : map)
            cout << e.first << " " << e.second << endl;
        // key와 value에 접근할 때, first와 second 이렇게 접근
        cout << endl;  
    }
    // multimap
    // 넣는 순서가 유지 x, sort되어진다
    {
        multimap<char, int> m_map;
        m_map.insert(pair<char, int>('a', 10)); // before c++ 14
        m_map.insert(pair('b', 20));
        m_map.insert(pair('a', 100));

        cout << m_map.count('a') << endl; // 해당 key에 원소 몇개
        for (auto& e : m_map)
            cout << e.first << " " << e.second << endl;
    }
}
```
```c
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void Container_adapters()
{
    // stack
    // 순서대로 쌓인다
    // 늦게 들어온게 먼저 삭제
    {
        stack<int> stack;
        stack.push(1);    // copy
        stack.emplace(2); // 새로운 object를 만들기
        stack.emplace(3);
        cout << stack.top() << endl; // 3
        stack.pop();                 // 3 삭제
        cout << stack.top() << endl; // 2
    }
    // queue
    // FIFO : first in first out
    {
        queue<int> queue;
        queue.push(1);
        queue.push(2);
        queue.push(3);
        cout << queue.front() << " " << queue.back() << endl; // 1, 3
        queue.pop();
        cout << queue.front() << " " << queue.back() << endl; // 2, 3
    }
    // Priority queue
    // sort 해준다
    {
        priority_queue<int> p_queue;

        for (const int n : {1, 7, 5, 6, 3, 4, 2})
            p_queue.push(n);
        for (int i = 0; i < 10; ++i)
        {   // 7 6 5 4 3 2 1 출력
            cout << p_queue.top() << endl;
            p_queue.pop();
        }
    }
}
```

### 16.2 STL 반복자 소개 Iterator
-  vector 이외의 container들은 혼자 공부!
```c
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

int main()
{
    vector<int> container;
    for (int i = 0; i < 10; ++i)
        container.push_back(i);

    // const 말고 그냥 iterator도 있다
    vector<int>::const_iterator itr;
    itr = container.begin();
    // while
    while (itr != container.end())
    {
        cout << * itr << " ";
        ++itr;
    }
    // for
    for (auto itr = container.begin(); itr != container.end(); ++itr)
        cout << * itr << " ";

    return 0;
}
```

### 16.3 STL 알고리즘 소개
- 엄청 많으니까 reference 참고
- 자료구조와 관련성이 많다
```c
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> container;
    for (int i = 0; i < 10; ++i)
        container.push_back(i);
    // min
    auto itr = min_element(container.begin(), container.end());
    cout << * itr << endl;
    // max
    itr = max_element(container.begin(), container.end());
    cout << * itr << endl;
    // find
    itr = find(container.begin(), container.end(), 3);
    container.insert(itr, 128); // 3이 뒤로 밀리고 그 자리에 128
    // sort
    sort(container.begin(), container.end());
    // 근데 list는 sort() 를 갖고 있어서 list.sort()
    reverse(container.begin(), container.end());
    // list.reverse()

    return 0;
}
```
