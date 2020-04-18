#include <iostream>
#include <vector>
#include <algorithm> // sort
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
	
	int n3 = n1 >= n2 ? n1 : n2;
	vector<int> array3(n3);

	// algorithm
	int p1(0), p2(0), p3(0);

	sort(array1.begin(), array1.end()); // 퀵정렬
	sort(array2.begin(), array2.end());

	while (p1 < n1 && p2 < n2)
	{
		if (array1[p1] < array2[p2]) p1++;
		else if (array1[p1] == array2[p2])
		{
			array3[p3++] = array1[p1++];
			p2++;
		}
		else p2++;
	}

	for (int i = 0; i <= p3; ++i)
		cout << array3[i] << ' ';

	return 0;
}