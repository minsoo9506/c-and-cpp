#include <iostream>
#include <vector>
using namespace std;

int n, dvd;
vector<int> arr(n);

int Count(int s) 
{
	int i, cnt = 1, sum = 0;
	for (i = 0; i < n; i++) 
	{
		if (sum + arr[i] > s) 
		{
			cnt++;
			sum = arr[i];
		}
		else sum = sum + arr[i];
	}
	return cnt;
}

int main() 
{

	int lt(0), rt(0), mid(0), res(0), m(0);

	cin >> n >> dvd;
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
		rt += arr[i];
	}

	while (lt <= rt) {
		mid = (lt + rt) / 2;
		if (Count(mid) <= m) {
			res = mid;
			rt = mid - 1;
		}
		else lt = mid + 1;
	}

	cout << res << endl;

	return 0;
}