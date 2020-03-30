// A, B 카드놀이 큰 수가 이긴다

#include <iostream>
using namespace std;

int main() 
{
	// input data
	int A[10], B[10];
	for (int i = 0; i < 10; ++i)
		cin >> A[i];
	for (int i = 0; i < 10; ++i)
		cin >> B[i];

	// algorithm
	int scoreA = 0, scoreB = 0, lastWin = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (B[i] < A[i])
		{
			scoreA += 3;
			lastWin = 1;
		}
		else if (A[i] < B[i])
		{
			scoreB += 3;
			lastWin = 2;
		}
		else
		{
			scoreA += 1;
			scoreB += 1;
		}
	}

	cout << "A score : " << scoreA << endl;
	cout << "B score : " << scoreB << endl;

	if (scoreA == scoreB)
	{
		if (lastWin == 0) cout << 'D' << endl;
		else if (lastWin == 1) cout << 'A' << endl;
		else cout << 'B' << endl;
	}
	else if (scoreA < scoreB) cout << 'B' << endl;
	else cout << 'A' << endl;

	return 0;
}