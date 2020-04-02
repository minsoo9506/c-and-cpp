// jolly jumper

#include <iostream>
#include <vector>
#include <algorithm> // abs
#include <numeric>   // accumulate
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;
	vector<int> num(N);
	for (int i = 0; i < N; ++i)
		cin >> num[i];

	// algorithm
	int index = 0;
	vector<int> data(N); // 0으로 초기화
	for (int i = 0; i < N - 1; ++i)
	{
		index = abs(num[i] - num[i + 1]);
		if (index >= 0 && index < N && data[index] == 0)
			data[index] = 1;
		else
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;

	return 0;
}