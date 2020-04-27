// 앞 옆에서 본 블록의 수를 통해
// 쌓을 수 있는 블록의 최댓값

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// input
	int n(0);
	cin >> n;
	vector <int> front(10);
	vector <int> right(10);
	for (int i = 0; i < n; ++i)
		cin >> front[i];
	for (int i = 0; i < n; ++i)
		cin >> right[i];

	// algorithm
	int arr[10][10];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			arr[j][i] = front[i];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (arr[j][i] > right[j]) arr[j][i] = right[j];
	
	int sum(0);
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j)
			sum += arr[i][j];

	cout << sum << endl;

	return 0;
}