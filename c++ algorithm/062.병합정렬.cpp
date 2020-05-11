#include <iostream>
#include <vector>
using namespace std;

int n, input[10], tmp[10];
int p1(0), p2(0), p3(0);

// input에서 0이 아닌 1부터 시작

void divide(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		divide(left, mid);
		divide(mid + 1, right);

		p1 = left, p2 = mid + 1, p3 = left;
		while (p1 <= mid && p2 <= right)
		{
			if (input[p1] < input[p2]) tmp[p3++] = input[p1++];
			else tmp[p3++] = input[p2++];
		}
		while (p1 <= mid) tmp[p3++] = input[p1++];
		while (p2 <= right) tmp[p3++] = input[p3++];

		for (int i = left; i <= right; ++i)
			input[i] = tmp[i];
	}
}

int main()
{
	// input
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> input[i];
		
	// algorithm
	divide(1, n);

	for (int i = 1; i <= n; ++i)
		cout << input[i] << endl;

	return 0;
}