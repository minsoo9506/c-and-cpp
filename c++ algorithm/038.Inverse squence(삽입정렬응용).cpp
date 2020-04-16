#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int n;
	cin >> n;
	vector<int> input(n);
	vector<int> output(n);
	for (int i = 0; i < n; ++i)
		cin >> input[i];

	// algorithm
	int pos(0);
	for (int i = n-1; i >= 0; --i)
	{
		pos = i;
		for (int j = 0; j < input[i] ; ++j)
		{
			output[pos] = output[pos + 1];
			pos++;
		}
		output[pos] = i;
	}

	for (int i = 0; i < n; ++i)
		cout << output[i] << ' ' ;

	return 0;
}