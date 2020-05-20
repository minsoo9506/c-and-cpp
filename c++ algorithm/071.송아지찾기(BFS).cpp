#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{	
	// input
	int s(0), e(0);
	cin >> s >> e;

	// algorithm
	int x(0), pos(s);
	int d[3] = { -1,1,5 };
	int ch[100];
	queue<int> Q;

	ch[s] = 0;
	Q.push(s);
	while (!Q.empty())
	{
		x = Q.front();
		Q.pop();
		for (int i = 0; i < 3; ++i)
		{
			pos += d[i];
			if (pos == e)
			{
				cout << ch[x] + 1 << endl;
				exit(0);
			}

			if (ch[pos] == 0)
			{
				ch[pos] = ch[x] + 1;
				Q.push(pos);
			}
		}
	}
	return 0;
}