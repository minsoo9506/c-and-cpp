// A, B 가위바위보 누가 이겼는지

#include <iostream>
using namespace std;

int main() 
{
	// input data
	int N;
	cin >> N;
	int *A = new int[N];
	int *B = new int[N];
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	for (int i = 0; i < N; ++i)
		cin >> B[i];
	// algorithm
	for (int i = 0; i < N; ++i)
	{
		if (A[i] == B[i]) cout << 'D' << endl;
		else if (A[i] == 1 && B[i] == 3) cout << 'A' << endl;
		else if (A[i] == 2 && B[i] == 1) cout << 'A' << endl;
		else if (A[i] == 3 && B[i] == 2) cout << 'A' << endl;
		else cout << 'B' << endl;
	}
	delete[] A;
	delete[] B;
	return 0;
}