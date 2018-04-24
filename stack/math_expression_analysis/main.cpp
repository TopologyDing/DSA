#include"D:\study\programming\CODE\C++\stack\stack\stack.h"
#include<iostream>
#include<string>

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
const char pri[9][9] = { //运算符优先等级 [栈顶] [当前]
    /*              |-------------------- 当 前 运 算 符 --------------------| */
    /*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

Operator optr2num(char op)
{
	switch (op)
	{
	case '+':return ADD;
	case '-':return SUB;
	case '*':return MUL;
	case '/':return DIV;
	case '^':return POW;
	case '!':return FAC;
	case '(':return L_P;
	case ')':return R_P;
	case '\0':return EOE;
	default:exit(-1);
	}
}

char compare(char a, char b)
{

	return(pri[optr2num(a)][optr2num(b)]);
}

int calc(int m, int n, char s)
{
	switch (s) 
	{
	case '+':return m + n;
	case '-':return m - n;
	case '*':return m * n;
	case '/':
		if (n == 0)
			abort();
		else
			return(n/m);
	case '^':return pow(m, n);
	default:exit(-1);
	}
}

int fac(int s)
{
	if (s == 1)
		return 1;
	while (s > 0)
		return(s*fac(s-1));
}

int main()
{
	string str;
	/*cout << "please enter a math expression:" << endl;
	getline(cin, str);
	cout << str<<endl;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		cout << str[i] << endl;
	}*/
	str = "(1+2)*(5!+32/2)";
	char* s = new char[str.length()+1];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		s[i] = str[i];
	}
	s[str.length()] = '\0';
	stack<int> s1;
	stack<char> s2;
	s2.push('\0');
	int i = 0;
	while(!s2.empty())
	{
		if (('0' <= s[i]) && (s[i] <= '9'))
		{
			s1.push((int)(s[i] - '0'));
			i = i + 1;
			while ('0' <= s[i] && s[i] <= '9')
			{
				s1.push((int)(s[i] - '0') + 10 * s1.pop());
				i = i + 1;
			}
		}
		else
		{
			switch (compare(s2.top(), s[i]))
			{
			case '>':
			{
				char optr = s2.pop();
				if ('!' == optr)
				{
					s1.push(fac(s1.pop()));
				}
				else
				{
					int m = s1.pop();
					int n = s1.pop();
					s1.push(calc(m, n, optr));
				}
				break;
			}
			case '=':
			{
				s2.pop();
				i++;
				break;
			}
			case '<':
			{
				s2.push(s[i]);
				i++;
				break;
			}
			}
		}
	}
	cout << "final s1:"<<s1.pop()<<endl;
	delete[] s;
	system("pause");
	return 0;
}

