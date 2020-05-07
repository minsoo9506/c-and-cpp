#include <iostream>
#include <vector>
using namespace std;

void rec(int v)
{
	if (v > 7) return;
	else
	{
		rec(v * 2);
		rec(v * 2 + 1);
		cout << v << ' '; // 후향
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