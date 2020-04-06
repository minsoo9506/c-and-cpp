// N! 소인수분해

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;

	// algorithm
	vector<int> cnt = { 0,0 };
	int tmp(0);

	for (int i = 1;i <= N; ++i)
	{
		tmp = i;   
		while (tmp % 2 == 0) 
		{
			tmp /= 2;
			cnt[0]++;
			if (tmp == 1) break;
		}
		while (tmp % 5 == 0)
		{
			tmp /= 5;
			cnt[1]++;
			if (tmp == 1) break;
		}
	}

	cout << min(cnt[0], cnt[1]) << endl;

	return 0;
}