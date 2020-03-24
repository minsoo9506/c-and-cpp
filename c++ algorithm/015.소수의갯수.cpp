/// 소수의 갯수

#include <iostream>
using namespace std;

bool isPrime(int x) {
	bool flag = true;
	for (int i = 2; i*i <= x; ++i) {
		if (x % i == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

int main() 
{
	int n, cnt(0);
	cin >> n;

	for (int i = 2; i <= n; i++) 
		if (isPrime(i)) cnt++;
	cout << cnt << endl;

	return 0;
}