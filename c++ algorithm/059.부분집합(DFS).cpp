#include <iostream>
#include <vector>
using namespace std;

int n, ch[10];

void DFS(int L)
{
	if (L == n + 1)
	{
		for (int i = 0; i < n; ++i)
			if (ch[i] == 1) cout << i + 1 << ' ';
	}
	else
	{
		ch[L] = 1;
		DFS(L + 1);
		ch[L] = 0;
		DFS(L + 1);
	}
}

int main()
{
	// input
	int n;
	cin >> n;
	
	// algorithm
	DFS(1);

	return 0;
}