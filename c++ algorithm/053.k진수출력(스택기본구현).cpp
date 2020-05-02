#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int stack[100];
int top(-1);

void push(int x)
{
	stack[++top] = x;
}

int pop()
{
	return stack[top--];
}

int main()
{
	// input
	int n(0), k(0);
	cin >> n >> k;

	// algorithm
	// 2, 4, 5, 8, 16 진수 출력
	// stack으로 구현

	char str[17] = "0123456789ABCDEF"; 
	while (n > 0)
	{
		push(n % k); // 나머지 push
		n /= k;      // 몫으로 재할당
	}

	while(top >= 0)
		cout << str[pop()];
	
	return 0;
}