#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
	// input
	int n;
	cin >> n;
	vector<int> input(n);
	for (int i = 0; i < n; ++i)
		cin >> input[i];
	
	// algorithm
	int num(1);
	stack<int> s;
	vector<char> output;

	for (int i = 0; i < n; ++i)
	{
		s.push(input[i]);
		output.push_back('P');
		while (true)
		{
			if (s.empty()) break;
			else
			{
				if (s.top() == num)
				{
					s.pop();
					num++;
					output.push_back('O');
				}
				else break;
			}
		}
	}

	if (!s.empty()) cout << "impossible" << endl;
	else
	{
		for (int i = 0; i < n; ++i)
			cout << output[i];
	}

	return 0;
}