// small version 이기에
// 그냥 for문으로 돌린다.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// input
	int width(0), height(0);
	cin >> width >> height;
	int arr[50][5];
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			cin >> arr[i][j];
	int getW(0), getH(0);
	cin >> getW >> getH;

	// algorithm
	int sum(0), max(0);
	for(int i= 0; i < width - getW +1;++i)
		for (int j = 0; j < height - getH + 1; ++j)
		{
			sum = 0;
			for (int n = i; n < i + getW; ++n)
				for (int m = j; m < j + getH; ++m)
					sum += arr[n][m];
			if (max < sum) max = sum;
		}

	cout << max << endl;

	return 0;
}