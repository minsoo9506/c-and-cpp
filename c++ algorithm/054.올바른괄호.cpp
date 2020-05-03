#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
	stack<char> s;
	char input[30];
	// input
	cin >> input;
	
	// algorithm
	int flag(1); // YES 의미

	for (int i = 0; input[i] != '\0'; ++i)
	{
		if (input[i] == '(') s.push('(');
		else
		{
			if (s.empty())
			{
				flag = 0;
				break;
			}
			s.pop();
		}
	}

	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}