// 가장 많이 나온 수
// 100의 자리수에서 가장 많이 사용된 수를 return
#include <iostream>
using namespace std;

int main()
{
	char N[101]; // 자연수 100자리 넣도록 (null character +1)
	int digit = 0;
	int count[10] = {};
	cin >> N;

	for (int i = 0; N[i] != '\0' ; ++i)
	{
		digit = N[i] - 48;
		count[digit]++;
	}

	int max = 0;
	int answer = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (count[i] >= max)
		{
			max = count[i];
			answer = i;
		}
	}

	cout << answer << endl;

	return 0;
}