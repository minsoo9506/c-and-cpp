// 바로 앞의 수가 더 큰 경우 count

#include <iostream>
using namespace std;

int main() 
{
	// input data 만들기
	int N;
	cin >> N;
	int* p = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> p[i];
	}
	// 실행
	int cnt(0);
	for (int i = 0; i < N - 1; ++i)
	{
		if (p[i] > p[i + 1]) cnt++;
	}

	cout << cnt << endl;
	delete[] p;

	return 0;
}