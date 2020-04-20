#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() 
{
	// input data
	int n, target;
	cin >> n >> target;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];

	// algorithm
	sort(arr.begin(), arr.end()); // 정렬

	int left(0), mid(0), right(n-1);
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (target == arr[mid])
		{
			cout << mid + 1 << "번째" << endl;
			break;
		}
		else if (target > arr[mid]) right = mid - 1;
		else left = mid+1;
	}

	return 0;
}