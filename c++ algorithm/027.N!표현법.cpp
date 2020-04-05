// N! 소인수분해

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;

	// algorithm
	vector<int> cnt(N+1);
	int tmp(0);
	int j(0);

	for (int i = 1;i <= N; ++i)
	{
		tmp = i; // 소인수분해할 수
		j = 2;   // 2부터 나누기 시작
		while (true) // 소인수분해
		{
			if (tmp % j == 0)
			{
				cnt[j]++;
				tmp /= j;
			}
			else j++;
			
			if (tmp == 1) break;
		}
	}

	for (int i = 1; i <= N; ++i)
		if (cnt[i] != 0) cout << cnt[i] << ' ';

	return 0;
}