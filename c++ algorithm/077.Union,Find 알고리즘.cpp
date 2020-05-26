#include <iostream>
#include <vector>
using namespace std;

int unf[1000];

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
	int a(0), b(0);
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b;
		Union(a, b);
	}
	cin >> a >> b;
	a = Find(a);
	b = Find(b);
	if (a == b) cout << "YES";
	else cout << "NO";
	return 0;
}