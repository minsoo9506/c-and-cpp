// 버블정렬응용
// 음수, 양수만 분류
// 음수를 왼쪽 양수를 오른쪽으로 보내기
// https://gmlwjd9405.github.io/2018/05/06/algorithm-bubble-sort.html

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int n;
	cin >> n;
	vector<int> num(n);
	for (int i = 0; i < n; ++i)
		cin >> num[i];

	// algorithm
	int tmp(0), idx(0);

	for (int i = n - 2; i > 0; --i)
	{
		for (int j = 0; j <= i; ++j)
			if (num[j] > 0 && num[j+1] < 0)
			{
				tmp = num[j];
				num[j] = num[j+1];
				num[j+1] = tmp;
			}
	}

	for (int i = 0; i < n; ++i)
	{
		cout << num[i] << ' ';
	}

	return 0;
}