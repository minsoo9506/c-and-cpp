#include <iostream>
#include <vector>
using namespace std;

int ch[10];
int n(0), cnt(0);
vector <int> arr[10]; // vector를 10개 만든다

void DFS(int v)
{
	if (v == n) cnt++;
	else
		for (int i = 0; i < arr[v].size(); ++i)
			if(ch[arr[v][i]]==0)
			{
				ch[arr[v][i]] = 1;
				DFS(arr[v][i]);
				ch[arr[v][i]] = 0;
			}
			
}

int main()
{
	// input
	int x(0), y(0);
	cin >> n;

	// 인접리스트
	for (int i = 1; i <= n; ++i)
	{
		cin >> x >> y;
		arr[x].push_back(y);
	}

	// algorithm
	ch[1] = 1;
	DFS(1);
	cout << cnt << endl;

	return 0;
}