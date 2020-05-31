#include <iostream>
#include <vector>
using namespace std;

int n, r, cnt(0);
int a[10], res[10], ch[10];

int DFS(int L)
{
	if (L == r)
	{
		for (int j = 0; j < L; ++j)
			cout << res[j] << endl;
		cnt++;
	}
	else
		for(int i = 1 ; i <=n ; ++i)
			if (ch[i] == 0)
			{
				res[L] = a[i];
				ch[i] = 1;
				DFS(L + 1);
				ch[i] = 0;
			}
}

int main()
{
	// input
	cin >> n >> r;
	for (int i = 0; i < n; ++i)
		cin >> a[i];

	// algorithm
	DFS(0);
	cout << cnt << endl;

	return 0; 
}