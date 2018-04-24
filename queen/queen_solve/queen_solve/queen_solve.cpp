#include"queen.h"
#include<string>
#include<iostream>

int main()
{
	stack<Queen> queen_ptr;
	int n;
	std::cout << "please set the scale of the problem:";
	std::cin >> n;
	placeQueens(n,queen_ptr);
	Queen q;

	for (int i = 0; i < n; i++)
	{
		q = queen_ptr.pop();
		for (int y = 0; y < q.y; y++) {
			std::cout << "|";
			string s = std::to_string(y);
			int length = s.length();
			for (int i = 0; i < length; i++)
				std::cout << " ";
		}
		std::cout << "|" << q.y;
		for (int y = q.y + 1; y < n; y++) {
			std::cout << "|";
			string s = std::to_string(y);
			int length = s.length();
			for (int i = 0; i < length; i++)
				std::cout << " ";
		}
		std::cout << "|" << endl;
	}
	system("pause");
	return 0;
}