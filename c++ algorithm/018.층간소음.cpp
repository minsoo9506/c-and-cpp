// 특정 수를 넘는 연속적인 갯수

#include <iostream>
using namespace std;

int main() 
{
	int N, M;
	cin >> N >> M;
	int* p = new int[N];
	for (int i = 0; i < N; ++i)
		cin >> p[i];

	int output{ 0 }, cnt{ 0 };
	for (int i = 0; i < N; ++i)
	{
		if (p[i] > M) cnt++;
		else cnt = 0;
		if (output < cnt) output = cnt; // 매번 업데이트 해준다
	}

	cout << output << endl;
	delete[] p;

	return 0;
}