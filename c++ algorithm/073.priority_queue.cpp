#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{	
	// input
	int n(0);

	// algorithm
	priority_queue <int> pQ;

	while (true)
	{
		cin >> n;
		if (n == -1) break;
		else if (n == 0)
		{
			if (pQ.empty()) cout << -1 << endl;
			else
			{
				cout << pQ.top() << endl;
				pQ.pop();
			}
		}
		else pQ.push(n);
	}

	return 0;
}