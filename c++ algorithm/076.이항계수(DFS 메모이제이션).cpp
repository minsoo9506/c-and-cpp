#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[20][20];

int DFS(int n, int m)
{
	if (arr[n][m] != 0) return arr[n][m]; // DFS에서 중복된 부분을 계산하지 않고 메모이제이션!
	if (n == m || m == 0) return 1;
	else return arr[n][m] = DFS(n - 1, m - 1) + DFS(n - 1, m);
}

int main()
{
	// input
	int n(0), m(0);
	cin >> n >> m;

	// algorithm
	cout << DFS(n, m) << endl;

	return 0;
}