#include <iostream>
#include <vector>
using namespace std;

int ch[10][10];
int n(0), cnt(0);
int arr[10][10] = { 0, };
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int xx(0), yy(0);

void DFS(int x, int y)
{
	if (x == 7 && y == 7) cnt++;
	else
		for (int i = 0; i < 4; ++i)
		{
			xx = x + dx[i];
			yy = y + dy[i];
			if (xx < 1 || xx>7 || yy < 1 || yy>7) continue;
			if(arr[xx][yy]==0 && ch[xx][yy]==0)
			{
				ch[xx][yy] = 1;
				DFS(xx,yy);
				ch[xx][yy] = 0;
			}
		}

}

int main()
{
	// input
	int x(0), y(0);
	cin >> n;

	// 인접행렬 만들기	
	for (int i = 1; i <= n; ++i)
	{
		cin >> x >> y;
		arr[x][y] = 1;
	}

	// algorithm
	DFS(1,1);
	cout << cnt << endl;

	return 0;
}