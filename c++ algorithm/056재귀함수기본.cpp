#include <iostream>
#include <vector>
using namespace std;

int rec(int n)
{
	if (n == 0) return 0;
	else
	{
		rec(n - 1);
		cout << n << ' ';
	}
}

int main()
{
	// input
	int n;
	cin >> n;
	
	// algorithm
	rec(n);

	return 0;
}