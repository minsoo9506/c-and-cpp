## 10.1 객체들의 관계
- 구성
  - 관계의 형태 : 전체/부품
  - 다른 클래스에도 속할 수 있는가 : No
  - 멤버의 존재를 클래스가 관리 : Yes
  - 방향성 : 단방향
- 집합
  - 관계의 형태 : 전체/부품
  - 다른 클래스에도 속할 수 있는가 : Yes
  - 멤버의 존재를 클래스가 관리 : No
  - 방향성 : 단방향
- 연계, 제휴
  - 관계의 형태 : 용도 외엔 무관
  - 다른 클래스에도 속할 수 있는가 : Yes
  - 멤버의 존재를 클래스가 관리 : No
  - 방향성 : 단방향 or 양방향
- 의존
  - 관계의 형태 : 용도 외엔 무관
  - 다른 클래스에도 속할 수 있는가 : Yes
  - 멤버의 존재를 클래스가 관리 : Yes
  - 방향성 : 단방향

## 10.2 구성 관계 (composition)
- Monster.h : Monster class
- Position.h : Position class (Monster 의 sub class)
- main.cpp

```c
#pragma once
#include <string>

class Position
{
private:
	int m_x;
	int m_y;

public:
	Position(const int& x_in, const int& y_in)
		: m_x(x_in), m_y(y_in)
	{}

	void set(const Position& pos_target)
	{
		set(pos_target.m_x, pos_target.m_y);
	}

	void set(const int& x_target, const int& y_target)
	{
		m_x = x_target;
		m_y = y_target;
	}

	friend std::ostream& operator << (std::ostream& out, const Position& pos)
	{
		out << pos.m_x << " " << pos.m_y;
		return out;
	}
};
```
```c
#pragma once
#include <string>
#include "Position.h"

class Monster
{
private:
	std::string m_name;
	Position m_location;

public:
	Monster(const std::string name_in, const Position& pos_in)
		: m_name(name_in), m_location(pos_in)
	{}

	void moveTo(const Position& pos_in)
	{
		m_location.set(pos_in);
	}

	friend std::ostream &operator << (std::ostream& out, const Monster& monster)
	{
		out << monster.m_name << " " << monster.m_location;
		return out;
	}
};
```
```c
#include <iostream>
#include "Monster.h"
using namespace std;


int main()
{
	Monster mon1("Sanson", Position(0, 0));
	{
		mon1.moveTo(Position(1, 1));
		cout << mon1 << endl;
	}

	return 0;
}
```

## 10.3 집합 관계
- 강의 참고
## 10.4 제휴 관계
- 강의 참고
## 10.5 의존 관계
- 강의 참고

## 10.6 컨테이너 클래스
- 다른 class들을 담는 역할
