// 각 행의 평균과 가장 가까운 값
// 각 행의 평균, 평균과 가장 가까운 값 return
// 그 차이가 같으면 큰 값을 return

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// input
	int n(0);
	cin >> n;
	int arr[9][9] = { 0 };
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> arr[i][j];
		}
	}

	// algorithm
	vector <int> rowMean(n);
	int rowSum(0);
	int min(100);
	vector <int> output(n);
	int tmp(0);

	for (int i = 0; i < n; ++i)
	{
		rowSum = 0;
		for (int j = 0; j < n; ++j)
		{
			rowSum += arr[i][j];
		}
		rowMean[i] = (rowSum / n) + 0.5; // float이 나와도 rowMean이 int라서 소수점부분 잘라짐

		for (int j = 0; j < n; ++j)
		{
			tmp = abs(rowMean[i] - arr[i][j]);
			if (tmp < min)
			{
				min = tmp;
				output[i] = arr[i][j];
			}
			else if (tmp == min)
				output[i] = output[i] > arr[i][j] ? output[i] : arr[i][j];
		}
	}

	for (int i = 0; i < n; ++i)
	{
		cout << rowMean[i] << ' ' << output[i] << endl;
	}

	return 0;
}