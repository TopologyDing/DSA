#pragma once
#include<cmath>
#include"D:\study\programming\CODE\C++\stack\stack\stack.h"
struct Queen{
	int x, y;
	Queen(int a=0, int b=0) :x(a), y(b) {};
	bool operator==(Queen const& q) {
		return((x == q.x) || (y == q.y) || (q.x + q.y == x + y) || (q.x - q.y == x - y));
	}
	bool operator!=(Queen const& q) {
		return(!(*this == q));
	}
};

//只能得到第一个版本,下一步完善成能够输出多个解的版本
void placeQueens(int N,stack<Queen>& solu) {
	Queen q(0, 0); 
	Queen output_queen;
	stack<Queen> output_stack;
	do {
		if (N <= q.y) {
			q = solu.pop(); q.y++; 
		}
		else { 
			while ((q.y < N) && (solu.find(q))) 
			{
				q.y++; 
			} 
			if (N > q.y) { 
				solu.push(q); 
				if (N <= solu.get_capacity()) {
					
					for (int i = 0; i < N; i++)
					{
						output_stack = solu;
						output_queen = solu.pop();
						for (int y = 0; y < output_queen.y; y++) {
							std::cout << "|";
							string s = std::to_string(y);
							int length = s.length();
							for (int i = 0; i < length; i++)
								std::cout << " ";
						}
						std::cout << "|" << output_queen.y;
						for (int y = output_queen.y + 1; y < N; y++) {
							std::cout << "|";
							string s = std::to_string(y);
							int length = s.length();
							for (int i = 0; i < length; i++)
								std::cout << " ";
						}
						std::cout << "|" << endl;
					}
				}
				q.x++; q.y = 0; 
			}
		}
	} while ((0 < q.x) || (q.y < N));
}