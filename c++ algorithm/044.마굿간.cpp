#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, horse;

int Count(vector<int> arr, int mid)
{
	int cnt = 1, pos(0);
	for (int i = 0; i < n; i++) 
	{
		pos = arr[0];
		if (arr[i] - pos >= mid)
		{
			pos = arr[i];
			cnt++;
		}
	}
	return cnt;
}

int main() 
{
	int lt(0), rt(0), mid(0), res(0);

	cin >> n >> horse;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];

	sort(arr.begin(), arr.end());

	lt = arr[0];
	rt = arr[n - 1];

	while (lt <= rt) 
	{
		mid = (lt + rt) / 2;
		if (Count(arr, mid) >= horse) 
		{
			res = mid;
			lt = mid + 1;
		}
		else rt = mid - 1;
	}

	cout << res << endl;

	return 0;
}