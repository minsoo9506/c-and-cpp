// 연속된 수를 더해서 가장 큰 수를 return

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int N, k;
	cin >> N >> k;
	vector<int> c(N);
	for (int i = 0; i < N; ++i)
		cin >> c[i];

	// algorithm
	int temp = 0;
	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < k; ++i)
		temp += c[i];
	if (max < temp) max = temp;

	for (int i = k; i < N; ++i)
	{
		max = max + c[i] - c[i - k];
		max = (max < temp) ? temp : max;
	}

	cout << max << endl;

	return 0;
}