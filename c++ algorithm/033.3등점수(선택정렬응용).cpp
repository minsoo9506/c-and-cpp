// 선택정렬로 내림차순
// 점수가 3번째로 큰 결과 나오게 하기

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
			if (num[idx] < num[j]) idx = j;
		tmp = num[i];
		num[i] = num[idx];
		num[idx] = tmp;
	}

	int order(1);
	for (int i = 0; i < n; i++)
	{
		if (num[i] > num[i + 1]) order++;
		if (order == 3)
		{
			cout << num[i+1] << endl;
			break;
		}
	}

	return 0;
}