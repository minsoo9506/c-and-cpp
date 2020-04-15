// 삽입정렬
// https://gmlwjd9405.github.io/2018/05/06/algorithm-insertion-sort.html

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
	int tmp(0), key(0);

	for (int i = 1; i < n; ++i)
	{
		tmp = num[i];
		for (int j = i-1; j >= 0; --j)
		{
			if (num[j] > tmp)
				num[j + 1] = num[j];
			else break;
		}
		num[j + 1] = tmp;
	}

	for (int i = 0; i < n; ++i)
		cout << num[i] << ' ';

	return 0;
}