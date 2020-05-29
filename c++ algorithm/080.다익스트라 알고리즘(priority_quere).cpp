#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge
{
	int vex;
	int dis;
	Edge(int a, int b)
	{
		vex = a;
		dis = b;
	}
	bool operator<(const Edge& b) const // 연산자오버로딩 
	{									// dis가 작은게 우선순위 큐에서 앞으로
		return dis > b.dis;
	}
};

int main()
{
	// input
	priority_queue<Edge> Q;
	vector<pair<int, int>> map[30];
	int n, m;
	cin >> n >> m;;

	vector<int> dist(n + 1, 100);

	int a, b, c;
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b >> c;
		map[a].push_back(make_pair(b, c));
	}

	// algorithm
	Q.push(Edge(1, 0));
	dist[1] = 0;
	int now, cost;
	int next, nextDis;
	while (!Q.empty())
	{
		now = Q.top().vex;
		cost = Q.top().dis;
		Q.pop();
		if (cost > dist[now]) continue;
		for (int i = 0; i < map[now].size; ++i)
		{
			next = map[now][i].first;
			nextDis = map[now][i].second;
			if (dist[next] > nextDis)
			{
				dist[next] = nextDis;
				Q.push(Edge(next, nextDis));
			}
		}
	}

	for (int i = 2; i <= n; ++i)
	{
		if (dist[i] != 100) cout << dist[i] << endl;
		else cout << "impossible" << endl;
	}
	
	return 0; 
}