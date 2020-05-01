#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	// input
	int n(0);
	cin >> n;

	// algorithm
	vector <int> a(n);
	int p2(0), p3(0), p5(0);
	a[0] = 1;
	int min(5);
	vector <int> tmp;

	for (int i = 1; i < n; i++) 
	{
		if (a[p2] * 2 < a[p3] * 3) min = a[p2] * 2;
		else min = a[p3] * 3;
		if (a[p5] * 5 < min) min = a[p5] * 5;
		
		if (min == a[p2] * 2) p2++;
		if (min == a[p3] * 3) p3++;
		if (min == a[p5] * 5) p5++;
		a[i] = min;
	}

	cout << a[n - 1] << endl;

	return 0;
}