// Anagram
// 두 단어를 받고 단어를 이루는 글자가 나온 횟수가 같으면 Anagram (YES)

#include <iostream>
using namespace std;

int main() 
{
	int a[60], b[60];
	char first[101], second[101];
	
	cin >> first;
	for (int i = 0; first[i] != '\0'; ++i)
		if (65 <= first[i] && first[i] <= 90)
			a[first[i] - 65]++;
		else a[first[i] - 71]++;
	
	cin >> second;
	for (int i = 0; second[i] != '\0'; ++i)
		if (65 <= second[i] && second[i] <= 90)
			b[second[i] - 65]++;
		else b[second[i] - 71]++;

	for (int i = 0; i < 52; ++i)
	{
		if (a[i] != b[i])
		{
			cout << "NO" << endl;
			exit(0);
		}
	}
	cout << "YES" << endl;

	return 0;
}