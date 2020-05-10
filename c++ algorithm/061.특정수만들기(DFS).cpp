#include <iostream>
#include <vector>
using namespace std;

int n, input[10];
int total(0);
int cnt(0);

void DFS(int depth, int sum)
{	
	if (depth == n)
	{
		if (total == sum) cnt++;
		return;
	}
	else
	{
		DFS(depth + 1, sum + input[depth]);
		DFS(depth + 1, sum);
		DFS(depth + 1, sum - input[depth]);
	}
}

int main()
{
	// input
	cin >> n >> total;
	for (int i = 0; i < n; ++i)
		cin >> input[i];
		
	// algorithm
	DFS(0, 0);

	if (cnt) cout << cnt << endl;
	else cout << -1 << endl;

	return 0;
}