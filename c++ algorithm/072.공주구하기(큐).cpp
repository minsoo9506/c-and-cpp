#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{	
	// input
	int n(0), k(0);
	cin >> n >> k;

	// algorithm
	queue<int> Q;

	while (!Q.empty())
	{
		for (int i = 1; i < k; ++i)
		{
			Q.push(Q.front);
			Q.pop();
		}
		Q.pop();
		if (Q.size() == 1)
		{
			cout << Q.front << endl;
			Q.pop();
		}
	}
	return 0;
}