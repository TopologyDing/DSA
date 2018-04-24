#include"vector.h"
#include<ctime>
#include<cstdio>
int main()
{
	vector<double> test1(20);
	for (int i = 0; i < test1.get_capacity(); i++)
	{
		test1.set_value(rand() % 10000, i);
	}
	vector<double>b(test1);
	for(int i=0;i<test1.get_capacity();i++)
	{
		cout << test1[i]<<" ";
	}
	cout << endl;
	test1.merge_sort(0,test1.get_capacity());
	cout << test1;
	test1.remove(test1.get_capacity());
	cout << test1;
	test1.remove(3, 10);
	cout << test1;
	cout<<test1.find(777)<<endl;//可以添加返回运行时间，便于比较算法之间的差异
	cout << test1.binary_find(777, 1, 0) << endl;
	system("pause");
	return 0;
}