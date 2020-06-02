#include <iostream>
#include <vector>
using namespace std;

vector<int> T, P;
int n, res = 0;

void DFS(int L, int sum)
{
	if (L == n + 1)
	{
		if (sum > res) res = sum;
	}
	else
	{
		if (L + T[L] <= n + 1) DFS(L + T[L], sum + P[L]); // if(L + T[L] <= n + 1) 는 해당범위를 넘어가는 경우 방지
		else DFS(L + 1, sum);
	}
}

int main()
{
	// input
	cin >> n;
	T.push_back(0);
	P.push_back(0);
	int a, b;
	for (int i = 0; i <= n; ++i)
	{
		cin >> a >> b;
		T.push_back(a);
		P.push_back(b);
	}
	// algorithm
	DFS(1, 0);
	cout << res << endl;
		
	return 0; 
}