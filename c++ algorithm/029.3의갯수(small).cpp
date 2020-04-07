// 3의 갯수는? small
#include <iostream>
// #include <vector>
// #include <algorithm>
using namespace std;

int main() 
{
	// input data
	int num = 0;
	cin >> num;

	// algorithm
	int tmp(0), cnt(0);
	for (int i = 0; i <= num; i++) // 숫자가 크지 않기에 하나씩 확인
	{
		tmp = i;
		while (tmp > 0)
		{
			if (tmp % 10 == 3) cnt++; // 나머지가 3인 경우 cnt++
			tmp /= 10;
		}		
	}

	cout << cnt << endl;

	return 0;
}