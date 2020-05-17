#include <iostream>
#include <vector>
using namespace std;

int ch[10];
int n(0), sum(0), max(0);
vector <pair<int, int>> arr[10];

void DFS(int v, int sum)
{
	if (v == n)
		max < sum ? sum : max;
	else
		for (int i = 0; i < arr[v].size(); ++i)
			if (ch[arr[v][i].first] == 0)
			{
				ch[arr[v][i].first] = 1;
				DFS(arr[v][i].first,sum + arr[v][i].second);
				ch[arr[v][i].first] = 0;
			}
}

int main()
{
	// input
	int x(0), y(0), z(0);
	cin >> n;

	// 인접리스트
	for (int i = 1; i <= n; ++i)
	{
		cin >> x >> y >> z;
		arr[x].push_back(make_pair(y,z));
	}

	// algorithm
	ch[1] = 1;
	DFS(1,0);
	cout << max << endl;

	return 0;
}