#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int ch[10];
	int dis[10];
	vector <int> adj_list[10];
	queue<int> Q;
	
	// input
	int n(0);
	int x(0), y(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		adj_list[x].push_back(y);  	// 인접리스트
	}

	// algorithm
	ch[1] = 1;
	Q.push(1);
	while (!Q.empty())
	{
		x = Q.front();
		Q.pop();
		for (int i = 0; i < adj_list[x].size(); ++i)
			if (ch[adj_list[x][i]] == 0)
			{
				ch[adj_list[x][i]] = 1;
				Q.push(adj_list[x][i]);
				dis[adj_list[x][i]] = dis[x] + 1;
			}
	}
	for (int i = 2; i < n; ++i)
		cout << dis[i] << endl;
	return 0;
}