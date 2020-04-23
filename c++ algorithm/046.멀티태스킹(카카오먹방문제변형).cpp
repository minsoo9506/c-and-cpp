// 멀티태스킹(카카오 먹방문제 변형)
#include <iostream>
#include <vector>
using namespace std;


int main() 
{
	// input
	int n(0), lightout(0);
	int total(0);
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
		total == arr[i];
	}
	cin >> lightout;

	// algorithm
	int pos(-1), cnt(1), tmp(0);

	if (total < lightout)
	{
		cout << -1 << endl;
		return 0;
	}

	while (true)
	{
		pos++;
		if (pos > n - 1) pos = 0;
		if (arr[pos] == 0) continue; // 이 뒤에 내용 skip하고 반복문 처음으로 이동
		arr[pos]--;
		cnt++;
		if (cnt == lightout) break;
	}

	while (true)
	{
		pos++;
		if (pos > n - 1) pos = 0;
		if (arr[pos] != 0) break;
	}

	cout << pos << endl;

	return 0;
}