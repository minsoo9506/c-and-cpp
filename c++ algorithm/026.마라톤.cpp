// 마라톤
// 앞에 본인보다 작은 수가 있으면 추월이 가능하다

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;
	vector<int> ability(N);
	for (int i = 0; i < N; ++i)
		cin >> ability[i];

	// algorithm
	vector<int> final(N);
	for (int i = 0; i < N; ++i)
	{
		final[i] = i+1;
		for (int j = 0; j < i; ++j)
			if (ability[i] > ability[j]) final[i]--;
	}

	for (int i = 0; i < N; ++i)
		cout << final[i] << ' ';

	return 0;
}