// 버블정렬
// 인접한 두 원소의 크기를 비교하여 정렬
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
			if (num[j] > num[j + 1])
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