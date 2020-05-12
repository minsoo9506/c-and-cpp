#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// input
	int input[10][3];
	int n(0), m(0);
	int x(0), y(0), c(0);
	cin >> n >> m;
		
	// algorithm
	int arr[10][10] = { 0, };		// 최대 10*10으로 제한
	for (int i = 1; i <= m; ++i)
	{
		cin >> x >> y >> c;
		arr[x][y] = c;
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			cout << arr[i][j] << ' ';
		cout << endl;
	}

	return 0;
}