# vector简单实现

```c++
#include <iostream>
#include <algorithm>
#include <assert.h>

template <typename T>
class myVector
{
public:
	myVector() : arr(0), m_size(0), m_capacity(0) { }
	myVector(unsigned int n, const T& t) : arr(0), m_size(0), m_capacity(0)
	{
		while (n--)
		{
			push_back(t);
		}
	}
	myVector(const myVector<T>& other) : arr(0), m_size(0), m_capacity(0)
	{
		*this = other;
	}

	myVector<T>& operator = (myVector<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		clear();
		m_size = other.m_size;			// 在 this 类内，this 与 other 互为友元，other 可以访问私有成员变量，
        							   // 效果等同于 theSize = other.size();
		m_capacity = other.m_capacity;	// theCapacity = other.capacity();
		arr = allocator(m_capacity);	//arr = new T[m_capacity];

		for (unsigned int i = 0; i < m_size; ++i)
		{
			arr[i] = other[i];
		}
		return *this;
	}

	~myVector()
	{
		clear();
	}

	T& operator[](unsigned int pos)
	{
		assert(pos < m_size);
		return arr[pos];
	}

	unsigned int size()
	{
		return m_size;
	}

	unsigned int capacity()
	{
		return m_capacity;
	}

	bool empty()
	{
		return m_size == 0;
	}

	void clear()
	{
		deallocator(arr);
		arr = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	void push_back(const T& t)
	{
		insert_after(m_size - 1, t);
	}

	void push_front(const T& t)
	{
		insert_before(0, t);
	}

	void insert_after(int pos, const T& t)
	{
		insert_before(pos + 1, t);
	}

	void insert_before(int pos, const T& t)
	{
		if (m_size == m_capacity)
		{
			T* oldArray = arr;
			if (m_capacity == 0)
			{
				m_capacity = 1;
			}
			else
			{
				m_capacity *= 2;
			}
			arr = allocator(m_capacity);
			for (unsigned int i = 0; i < m_size; ++i)
			{
				arr[i] = oldArray[i];
			}
			deallocator(oldArray);
		}
		for (int i = m_size++; i > pos; --i)
		{
			arr[i] = arr[i - 1];
		}
		arr[pos] = t;
	}

	bool erase(unsigned int pos)
	{
		if (pos < m_size)
		{
			--m_size;
			for (unsigned int i = pos; i < m_size; ++i)
			{
				arr[i] = arr[i + 1];
			}
			return true;
		}
		return false;
	}

private:
	T* allocator(unsigned int size)
	{
		return new T[size];
	}

	void deallocator(T* dlarr)
	{
		if (dlarr)
		{
			delete[] dlarr;
			dlarr = nullptr;
		}
	}

	T* arr;
	unsigned int m_size;
	unsigned int m_capacity;
};

void printfVector(myVector<int>& vec)
{
	for (unsigned int i = 0; i < vec.size() - 1; i++)
	{
		std::cout << vec[i] << ", ";
	}
	std::cout << vec[vec.size() - 1] << std::endl;
}

int main()
{
	myVector<int> myVector1;
	myVector<int> myVector2(10, 0);
	myVector2.push_front(1);
	myVector2.erase(11);
	printfVector(myVector2);		// 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	myVector1.push_back(2);
	std::cout << "size : " << myVector1.size() << "  capacity : " << myVector1.capacity() << std::endl;		// size: 1  capacity : 1		
	myVector1.push_front(1);
	std::cout << "size : " << myVector1.size() << "  capacity : " << myVector1.capacity() << std::endl;		// size: 2  capacity : 2
	printfVector(myVector1);		// 1, 2

	myVector1.insert_after(1, 3);
	std::cout << "size : " << myVector1.size() << "  capacity : " << myVector1.capacity() << std::endl;		// size: 3  capacity : 4
	printfVector(myVector1);		// 1, 2, 3

	myVector2 = myVector1;
	myVector2.insert_before(0, 0);
	myVector2.insert_before(1, -1);
	printfVector(myVector2);		// 0, -1, 1, 2, 3
}
```

