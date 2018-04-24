#pragma once
#include<iostream>
using namespace std;
typedef int item;

template<typename T>
class vector
{
public:
	vector(item c=3)
	{
		capacity = c;
		size = 2 * capacity;
		place = new T[size];
		memset(place, 0, sizeof(T)*capacity);
	}

	vector(const vector<T>&s, int low, int high)
	{
		if (!(low < high))
			cout << "the low position cannot be bigger than high position,please set again!" << endl;
		if (low < 0)
			low = 0;
		if (high > s.get_capacity())
			high = s.get_capacity();
		capacity = high - low;
		size = capacity * 2;
		place = new T[size];
		for (int i = 0; i < capacity; i++)
		{
			place[i] = s[i];
		}
	}

	vector(const vector<T>& s)//复制构造函数参数必须为引用,通常用const修饰
	{
		size = s.size;
		place = new T[size];
		for (int i = 0; i < capacity; i++)
		{
			place[i] = s.place[i];
		}
	}

	void expand()
	{
		if (capacity < size)
			return;
		T* old_place = place;
		if (size == 0)
			size = 1;
		place = new T[size*=2];
		for (int i = 0; i < capacity; i++)
		{
			place[i] = old_place[i];
		}
		delete[]old_place;
	}

	void shrink()
	{
		if (capacity >= size / 2)
			return;
		while (capacity < size / 2)
		{
			T* old_place = place;
			place = new T[size / 2];
			for (int i = 0; i < capacity; i++)
			{
				place[i] = old_place[i];
			}
			size = size / 2;
			delete[]old_place;
		}
	}

	void append(const T& s)
	{
		if (size > capacity)
		{
			place[capacity] = s;
		}
		else
		{
			this->expand();
			place[capacity] = s;
		}
		capacity++;
	}

	item get_capacity() const
	{
		return capacity;
	}

	int get_size() const
	{
		return size;
	}
	
	T* get_place()
	{
		return place;
	}

	bool empty()
	{
		if (capacity < 1)
			return true;
		else
			return false;
		
	}

	bool find(T a)//注意数组引用的方式
	{
		bool s = false;
		for (int i = 0; i < capacity; i++)
		{
			if (a == place[i])
			{
				s = true;
				return s;
			}
			else
				continue;
		}
		return s;
	}

	bool binary_find(T a,int m,int n)//need to debug
	{
		if (m-1 == n)
		{
			
			return(place[n] == a);
		}
		int half = (m + n) / 2;
		return(binary_find(a, m, half) || binary_find(a, half, n));
	}

	T& operator[](int i)
	{
		if (i > capacity)
		{
			cout << "wrong number" << endl;
		}
		return place[i];
	}

	friend ostream& operator<<(ostream &os,const vector<T>&t)
	{
		for (int i = 0; i < t.get_capacity(); i++)
		{
			os << t.place[i]<<" ";
		}
		os << endl;
		return os;
	}

	void set_value(T a,int i)
	{
		if (!(i < size))
			abort();
		place[i] = a;
	}

	void bubble_sort(int low, int high)
	{
		while (low+1 < high)
		{
			for (int i = low+1;i<high;i++)
			{
				if (place[i - 1] > place[i])
				{
					T temp;
					temp = place[i];
					place[i] = place[i - 1];
					place[i - 1] = temp;
				}
			}
			high--;
		}
	}

	void merge_sort(int low, int high)
	{
		if ((high - low) < 2)
			return;
		int middle = (low + high) / 2;
		merge_sort(low, middle);
		merge_sort(middle, high);

		T *a = new T[middle-low];
		T *b = new T[high - middle];
		T *c = place + low;

		for (int i = low; i < middle; i++)
		{
			a[i - low] = place[i];
		}
		for (int i = middle; i < high; i++)
		{
			b[i - middle] = place[i];
		}
		for (int i = 0, j = 0, k = 0; (j < (middle - low)) || (k < (high - middle));)
		{
			if (((a[j] <= b[k]) || (!(k < (high - middle)))) && (j < (middle - low)))
				c[i++] = a[j++];
			if (((a[j] > b[k]) || (!(j < (middle - low)))) && (k < (high - middle)))
				c[i++] = b[k++];
		}
		delete[]a;
		delete[]b;
	}

	bool remove(int position)
	{
		if (position >= capacity)
		{
			cout << "wrong operation" << endl;
			return false;
		}
		for (int i = position; i < capacity; i++)
		{
			place[i] = place[i + 1];
		}
	    shrink();
		capacity--;
		return true;
	}

	bool remove(int low, int high)
	{
		if ((high <= low) || (low < 0) || (high > capacity))
		{
			cout << "wrong operation" << endl;
			return false;
		}
		for (int i = high; i < capacity; i++)
		{
			place[low+i-high] = place[i];
		}
		capacity = capacity - (high - low);
		shrink();
		return true;
	}

	~vector()
	{
		delete[]place;
	}
protected:


private:
	T* place;
	item capacity;
	int size;
	bool is_sorted;
};