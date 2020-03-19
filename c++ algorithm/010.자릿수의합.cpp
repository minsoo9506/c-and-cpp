#include <iostream>
#include <limits>
using namespace std;


int digit_sum(int num)
{
	int sum(0);
	int n;
	while (num != 0)
	{
		n = num % 10;
		sum += n;
		num /= 10;
	}
	
	return sum;
}

int main()
{
	int N, num, sum;
	int max = INT_MIN;

	cin >> N;
	int *nums = new int[N];
	
	for (int i = 0; i < N; ++i)
	{
		cin >> nums[i];
		sum = digit_sum(nums[i]);
		if (sum > max)
			max = sum;
	}

	delete[] nums;
	cout << max << endl;
	
	return 0;
}