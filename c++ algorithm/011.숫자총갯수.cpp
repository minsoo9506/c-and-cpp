#include <iostream>
using namespace std;

int main()
{
	int N, tmp;
	int cnt = 0;
	cin >> N;

	for (int i = 1; i <= N; ++i)
	{
		tmp = i;
		while (tmp > 0)
		{
			tmp /= 10;
			cnt++;
		}
	}
	cout << cnt << endl;

	return 0;
}