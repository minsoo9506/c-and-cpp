// 두 배열 합치기
// 병합정렬 예비학습

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int n1;
	cin >> n1;
	vector<int> array1(n1);
	for (int i = 0; i < n1; ++i)
		cin >> array1[i];

	int n2;
	cin >> n2;
	vector<int> array2(n2);
	for (int i = 0; i < n2; ++i)
		cin >> array2[i];

	vector<int> array3(n1+n2);

	// algorithm
	int p1(0), p2(0), p3(0);

	while (p1 <= n1 - 1 && p2 <= n2 - 1)
	{
		if (array1[p1] <= array2[p2]) array3[p3++] = array1[p1++];
		else array3[p3++] = array2[p2++];
	}

	while (p1 <= n1 - 1) { array3[p3++] = array1[p1++]; }
	while (p2 <= n2 - 1) { array3[p3++] = array2[p2++]; }

	for (int i = 0; i < n1 + n2; ++i)
		cout << array3[i] << ' ';

	return 0;
}