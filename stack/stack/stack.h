#pragma once
#include"D:\study\programming\CODE\C++\vector_self\vector_self\vector.h"
template<typename T>
class stack :public vector<T> {
public:
	stack(int s=0);
	void push(const T& s);
	T pop();
	T top();
};

template<typename T>
stack<T>::stack(int s) 
	:vector<T>::vector(s)
{

}

template<typename T>
void stack<T>::push(const T& s)
{
	this->append(s);
}

template<typename T>
T stack<T>::pop()
{
	T a=this->get_place()[this->get_capacity()-1];
	this->remove(this->get_capacity()-1);
	return a;
}

template<typename T>
T stack<T>::top()
{
	return(this->get_place()[this->get_capacity() - 1]);
}