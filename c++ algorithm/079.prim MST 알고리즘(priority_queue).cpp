#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int ch[30];

struct Edge
{
	int e;
	int value;
	Edge(int a, int b)
	{
		e = a;
		value = b;
	}
	bool operator<(Edge& b) // 연산자오버로딩
	{
		return value > b.value;
	}
};


int main()
{
	// input
	priority_queue<Edge> Q;
	vector<pair<int, int>> map[30];
	int n, m;
	cin >> n >> m;;
	int a, b, c, res(0);
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b >> c;
		map[a].push_back(make_pair(b, c));
		map[b].push_back(make_pair(a, c));
	}

	// algorithm
	Q.push(Edge(1, 0));
	int v, cost;
	while (!Q.empty())
	{
		Edge tmp = Q.top();
		Q.pop();
		v = tmp.e;
		cost = tmp.value;
		if (ch[v] == 0)
		{
			res += cost;
			ch[v] = 1;
			for (int i = 0; i < map[v].size(); ++i)
				Q.push(Edge(map[v][i].first, map[v][i].second));
		}
	}

	cout << res << endl;
	return 0; 
}