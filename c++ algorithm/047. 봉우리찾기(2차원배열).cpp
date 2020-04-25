#include <iostream>
#include <vector>
using namespace std;


int main()
{
	// input
	int n(0);
	cin >> n;
	int arr[51][51] = { 0 };
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < n + 1; ++j)
		{
			cin >> arr[i][j];
		}
	}

	// algorithm
	int cnt(0), flag(0);
	int x[4] = {-1, 0, +1, 0};
	int y[4] = { 0, -1, 0, +1 };
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < n + 1; ++j)
		{
			flag = 0;
			for (int k = 0; k < 4; ++k)
				if (arr[i][j] <= arr[i + x[k]][j + y[k]]) // 주위에 하나라도 본인보다 큰게 있으면 탈락
				{
					flag = 1;
					break;
				}
			if (flag == 0)
				cnt++;
		}
	}

	cout << cnt << endl;

	return 0;
}