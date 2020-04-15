// Least Recently Used
// 삽입정렬응용
// 한정된 메모리에 data를 넣을때 
// memory에 있는 값이면 그 값을 맨앞으로 빼오고
// 나머지 숫자는 한칸씩 뒤로
// memory에 없는 값이면 한칸씩 뒤고 밀고
// 그 값을 맨앞에 넣는다

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// input data
	int sizeOfmemory, input_num;
	cin >> sizeOfmemory >> input_num;
	vector<int> input(input_num);
	vector<int> memory(sizeOfmemory);
	for (int i = 0; i < input_num; ++i)
		cin >> input[i];

	// algorithm
	int tmp_idx(-1);
	for (int i = 0; i < input_num; ++i)
	{
		for (int j = 0; j < sizeOfmemory; ++j)
			if (input[i] == memory[j])
			{
				tmp_idx = j;
				break;
			}

		if(tmp_idx != -1)
			for (int k = tmp_idx; k > 0; --k)
				memory[k] = memory[k - 1];
		else
			for (int k = sizeOfmemory-1; k > 0; --k)
				memory[k] = memory[k - 1];

		memory[0] = input[i];

		for (int z = 0; z < sizeOfmemory; ++z)
			cout << memory[z];
		cout << endl;
	}


	return 0;
}