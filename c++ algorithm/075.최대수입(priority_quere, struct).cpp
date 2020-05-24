#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Data
{
	int money;
	int when;
	Data(int a, int b)
	{
		money = a;
		when = b;
	}
	bool operator<(Data& b)
	{
		return when > b.when;
	}

};


int main()
{
	// input
	int n(0), max(0);
	cin >> n;
	int D(0), M(0);
	vector<Data> T;
	for (int i = 0; i < n; ++i)
	{
		cin >> D >> M;
		T.push_back(Data(D, M));
		if (M > max) max = M;
	}

	// algorithm
	priority_queue <int> pQ;
	int res(0);
	
	sort(T.begin(), T.end());

	int j = 0;
	for (int i = max; i >= 1; --i)
	{
		for (; j < n; j++)
		{
			if (T[j].when < i) break;
			pQ.push(T[j].money);
		}
		if (!pQ.empty())
		{
			res += pQ.top();
			pQ.pop();
		}
	}
	cout << res << endl;
	return 0;
}