#include <iostream>
#include <vector>
using namespace std;


int main() 
{
	// input
	int n(0), k(0);
	cin >> n >> k;
	vector<int> arr(n);

	// algorithm
	int pos(-1), cnt(0), out_count(0);

	while (true)
	{
		pos++;
		if (pos > n - 1) pos = 0;
		if (arr[pos] == 0)
		{
			cnt++;
			if (cnt == k)
			{
				arr[pos] = 1;
				cnt = 0;
				out_count++;
			}
		}
		if (out_count == n - 1) break;
	}

	for (int i = 0; i < n; ++i)
	{
		if (arr[i] == 0) cout << i+1 << endl;
	}

	return 0;
}