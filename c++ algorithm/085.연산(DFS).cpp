#include <iostream>
#include <vector>
using namespace std;

vector<int> a;
int n, max(0), min(0);
int op[4] = { 1 };

void DFS(int L, int sum)
{
	if (L == n)
	{
		if (sum > max) max = sum;
		if (sum < min) min = sum;
	}
	else
	{
		if (op[0])
		{
			op[0]--;
			DFS(L + 1, sum + a[L]);
			op[0]++;
		}
		if (op[1])
		{
			op[1]--;
			DFS(L + 1, sum - a[L]);
			op[1]++;
		}
		if (op[2])
		{
			op[2]--;
			DFS(L + 1, sum * a[L]);
			op[2]++;
		}
		if (op[3])
		{
			op[3]--;
			DFS(L + 1, sum / a[L]);
			op[3]++;
		}
	}
}

int main()
{
	// input
	cin >> n;
	int tmp;
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		a.push_back(tmp);
	}
	// algorithm
	DFS(1, a[0]);
	cout << max << endl;
	cout << min << endl;
		
	return 0; 
}