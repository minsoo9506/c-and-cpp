#include <iostream>
using namespace std;

int main()
{
	long long N, sum(0), answer(0), nine(9);
	int cnt(0);

	cin >> N;

	while (nine < N)
	{
		cnt++;
		sum += nine;
		answer += sum * cnt;
		nine *= 10;
	}
	cnt++;
	answer += (N - sum) * cnt;
	
	cout << answer << endl;

	return 0;
}