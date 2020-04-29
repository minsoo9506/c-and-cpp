#include <iostream>
#include <vector>
using namespace std;

int arr[702][702];
int dy[702][702];

int main()
{
	// input
	int width(0), height(0);
	cin >> width >> height;

	for (int i = 1; i <= width; ++i)
		for (int j = 1; j <= height; ++j)
		{
			cin >> arr[i][j];
			dy[i][j] = dy[i - 1][j] + dy[i][j - 1] - dy[i - 1][j - 1] + arr[i][j];
		}
	int getW(0), getH(0);
	cin >> getW >> getH;

	// algorithm
	int tmp(0), max(0);
	for(int i= getW; i <= width;++i)
		for (int j = getH; j <= height; ++j)
		{
			tmp = dy[i][j] - dy[i - getW][j] - dy[i][j - getH] + dy[i - getW][j - getH];
			if (max < tmp) max = tmp;
		}

	cout << max << endl;

	return 0;
}