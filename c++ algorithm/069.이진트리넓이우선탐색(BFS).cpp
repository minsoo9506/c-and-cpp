#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int ch[10];
	int front(-1), back(-1);
	vector <int> adj_list[10];
	int Q[100]; // 큐
	
	// input
	int n(0);
	int x(0), y(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		adj_list[x].push_back(y);  	// 인접리스트
		adj_list[y].push_back(x);
	}

	// algorithm
	// 큐 구현
	ch[1] = 1;
	Q[++back] = 1;
	while (front < back)
	{
		x = Q[++front];
		cout << x << ' ';
		for (int i = 0; i < adj_list[x].size(); ++i)
			if (ch[adj_list[x][i]] == 0)
			{
				ch[adj_list[x][i]] = 1;
				Q[++back] = adj_list[x][i];
			}
	}

	return 0;
}