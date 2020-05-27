#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unf[100];

struct Edge
{
	int v1;
	int v2;
	int value;
	Edge(int a, int b, int c)
	{
		v1 = a;
		v2 = b;
		value = c;
	}
	bool operator<(Edge& b) // 연산자오버로딩
	{
		return value < b.value;
	}
};

int Find(int v)
{
	if (v == unf[v]) return v;
	else return unf[v] = Find(unf[v]);
}

int Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a != b) unf[a] = b;
}

int main()
{
	// input
	int n(0), m(0);
	cin >> n >> m;

	// algorithm
	for (int i = 1; i <= n; ++i)
		unf[i] = i;

	vector<Edge> Ed;
	int a(0), b(0), c(0);
	
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b >> c;
		Ed.push_back(Edge(a, b, c));
	}
	sort(Ed.begin(), Ed.end());

	int fa(0), fb(0), res(0);
	for (int i = 0; i < m; ++i)
	{
		fa = Find(Ed[i].v1);
		fb = Find(Ed[i].v2);
		if (fa != fb)
		{
			res += Ed[i].value;
			Union(Ed[i].v1, Ed[i].v2);
		}
	}
	cout << res << endl;
	return 0; 
}