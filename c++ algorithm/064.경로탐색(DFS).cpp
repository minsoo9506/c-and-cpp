#include <iostream>
#include <vector>
using namespace std;

int ch[10];
int n(0), cnt(0);
int arr[10][10] = { 0, };

void DFS(int v)
{
	if (v == n) cnt++;
	else
		for (int i = 1; i <= n; ++i)
			if (arr[v][i] == 1 && ch[i] == 0)
			{
				ch[i] = 1;
				DFS(i);
				ch[i] = 0;
			}
}

int main()
{
	// input
	int input[10][3];
	int n(0), m(0);
	int x(0), y(0);
	cin >> n >> m;

	// 인접행렬 만들기	
	for (int i = 1; i <= m; ++i)
	{
		cin >> x >> y;
		arr[x][y] = 1;
	}

	// algorithm
	ch[1] = 1;
	DFS(1);
	cout << cnt << endl;

	return 0;
}