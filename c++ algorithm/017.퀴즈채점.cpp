// card_num이 주어지면
// 1부터 card_num까지 수를 더한 값을 맞췄는지 채점

#include <iostream>
#include <string>
using namespace std;

int main() 
{
	int student_num, card_num, student_answer;
	cin >> student_num;
	for (int i = 0; i < student_num; ++i)
	{
		int real_answer(0);
		cin >> card_num >> student_answer;
		for (int i = 1; i <= card_num; ++i)
			real_answer += i;
		string output = (real_answer == student_answer) ? "YES" : "NO";
		cout << output << endl;
		
	}

	return 0;
}