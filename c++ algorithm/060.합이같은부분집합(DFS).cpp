#include <iostream>
#include <vector>
using namespace std;

int n, input[10];
int total(0);
int flag(0);

void DFS(int depth, int sum)
{	
	if (flag) return;
	if (total == sum * 2) flag = 1;
	if (depth == n) return;
	else
	{
		DFS(depth + 1, sum + input[depth]);
		DFS(depth + 1, sum);
	}
}

int main()
{
	// input
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> input[i];
		total += input[i];
	}
		
	// algorithm
	DFS(0, 0);

	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}