// 3의 갯수는? large
#include <iostream>
// #include <vector>
// #include <algorithm>
using namespace std;

int main() 
{
	// input data
	long num = 0;
	cin >> num;

	// algorithm
	int cnt(0), left(0), current(0), right(0), k(1);
	while (left > 0)
	{
		left = num / (k * 10);
		current = num % (k * 10);
		right = num % k;

		if (current > 3) cnt += (left + 1) * k;
		else if (current == 3) cnt += (left * k) + (right + 1);
		else cnt += left * k;

		k *= 10;
	}

	cout << cnt << endl;

	return 0;
}