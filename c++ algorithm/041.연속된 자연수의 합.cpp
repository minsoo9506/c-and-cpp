#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int n;
	cin >> n;

	// algorithm
	int tmp(0), b(2), cnt(0);
	tmp = n - 1;

	while (tmp > 0)
	{
		tmp -= b;
		if (tmp % b == 0)
		{
			for (int i = 1; i < b; ++i)
				cout << (tmp / b) + i << " + ";
			cout << (tmp / b) + b << " = " << n << endl;
			cnt++;
		}
		b++;
	}

	cout << cnt << endl;

	return 0;
}