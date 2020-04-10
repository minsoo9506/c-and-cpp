// 선택정렬로 오름차순 표현하기
// 맨앞부터 시작해서 하나씩 다 비교하고 swap
// 참고사이트 : https://gmlwjd9405.github.io/2018/05/06/algorithm-selection-sort.html

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

	for (int i = 0; i < n; ++i)
	{
		idx = i;
		for (int j = i + 1; j < n; j++)
			if (num[i] > num[j]) idx = j;
		tmp = num[i];
		num[i] = num[idx];
		num[idx] = tmp;
	}

	for (int i = 0; i < n; i++)
		cout << num[i] << ' ';

	return 0;
}