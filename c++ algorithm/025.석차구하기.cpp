// 석차구하기 (브루트 포스 방법)

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;
	vector<int> score(N);
	for (int i = 0; i < N; ++i)
		cin >> score[i];

	// algorithm
	vector<int> a(N);

	for (int i = 0; i < N; ++i)
	{
		a[i]++; // 전부 0으로 초기화됐으므로 기본적으로 1을 더한다.
		for (int j = 0; j < N; ++j)
		{
			if (score[i] > score[j]) a[j]++;
		}
	}
	
	for (int i = 0; i < N; ++i)
		cout << a[i] << endl;

	return 0;
}