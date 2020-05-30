#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dist[100];

struct Edge
{
	int start;
	int end;
	int val;
	Edge(int a, int b, int c)
	{
		start = a;
		end = b;
		val = c;
	}
};

int main()
{
	// input
	vector<Edge> Ed;

	int n, m;
	cin >> n >> m;;

	int a, b, c;
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b >> c;
		Ed.push_back(Edge(a, b, c));
	}
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = 100; // 최대값으로 일단 채우기
	}
	int s, e;
	cin >> s >> e;

	// algorithm
	int u, v, w;
	dist[s] = 0;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < Ed.size(); ++j)
		{
			u = Ed[j].start;
			v = Ed[j].end;
			w = Ed[j].val;
			if (dist[u] != 100 && dist[u] + w < dist[v])
				dist[v] = dist[u] + w;
		}
	}
	
	return 0; 
}