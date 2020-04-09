#include <iostream>
#include <string>
using namespace std;

int main() 
{
	// input data
	string ch;
	cin >> ch;

	// algorithm
	int c(0), h(0), h_idx(0);
	
	if (ch[1] == 'H')
	{
		c = 1;
		h_idx = 1;
	}
	else
	{
		for (int i = 1; ch[i] != 'H'; ++i)
		{
			c = c * 10 + (ch[i] - 48); // 이 skill!! 까먹지 말자
			h_idx = i+1;
		}
	}

	cout << h_idx << endl;

	if (ch[h_idx + 1] == ch.size())
		h = 1;
	else
		for (int i = h_idx+1; i < ch.size() ; ++i)
			h = h * 10 + (ch[i] - 48);

	cout << 12 * c + 1 * h << endl;

	return 0;
}