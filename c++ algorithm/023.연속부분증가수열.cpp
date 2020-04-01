// 점점 커지는 횟수

#include <iostream>
#include <vector>
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
	int temp = 1;
	int max = 1;

	for (int i = 1; i < N; ++i)
	{
		if (num[i - 1] <= num[i])
			temp += 1;
		else
		{
			max = (max < temp) ? temp : max;
			temp = 1;
		}
	}

	cout << max << endl;

	return 0;
}