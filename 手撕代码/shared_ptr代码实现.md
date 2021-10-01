# shared_ptr代码实现

```cpp
#include <iostream>

template <typename T>
class SmartPtr {
public:
	SmartPtr(T *p);								// SmartPtr<int> p(new int(2));
	SmartPtr(const SmartPtr<T>& orig);			// SmartPtr<int> q(p);
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs);// q = p;
	~SmartPtr();

	T& operator*();							// 为了能把智能指针当成普通指针操作定义解引用操作
	T* operator->();						// 定义取成员操作
	T* operator+(int i);					// 定义指针加一个常数

	template <typename T>
	friend int operator-(SmartPtr<T>& t1, SmartPtr<T>& t2);

	unsigned getCount()
	{
		return *use_count;
	}

private:
	T *ptr;						// 底层真实的指针
	unsigned *use_count;		// 保存当前对象被多少指针引用计数
};

template <typename T>
SmartPtr<T>::SmartPtr(T *p)
{
	ptr = p;
	try 
    {
		use_count = new unsigned(1);
	}
	catch (...)
	{
		delete ptr;
		ptr = nullptr;
		delete use_count;
		use_count = nullptr;
	}
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& orig)
{
	this->use_count = orig.use_count;		// 引用计数保存在一块内存，所有的 SmartPtr 对象的引用计数都指向这里
	this->ptr = orig.ptr;
	++(*use_count);			// 当前对象的引用计数加 1
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& rhs)
{							// 不检查自我赋值也可以，因为首先 ++*(rhs.use_count); 确保 (--(*use_count)) != 0
	++(*rhs.use_count);
	if ((--(*use_count)) == 0)
	{
		delete ptr;
		ptr = nullptr;
		delete use_count;
		use_count = nullptr;
	}
	ptr = rhs.ptr;
	*use_count = *(rhs.use_count);
	return *this;
}

template <typename T>
SmartPtr<T>::~SmartPtr()
{
	if (--(*use_count) == 0)
	{
		delete ptr;
		ptr = nullptr;
		delete use_count;
		use_count = nullptr;
	}
}

template <typename T>
T& SmartPtr<T>::operator*()
{
	return *ptr;
}

template <typename T>
T* SmartPtr<T>::operator->()
{
	return ptr;
}

template <typename T>
T* SmartPtr<T>::operator+(int i)
{
	T* temp = ptr + i;
	return temp;
}

template <typename T>
int operator-(SmartPtr<T>& t1, SmartPtr<T>& t2)
{
	return *t1.ptr - *t2.ptr;
}

int main()
{
	SmartPtr<int> p(new int(5));
	SmartPtr<int> p2(p);
	SmartPtr<int> p3 = p;
	std::cout << p.getCount() << std::endl;		// 3

	*p = 6;
	std::cout << p.getCount() << std::endl;		// 3
	std::cout << *p3 << std::endl;				// 6

	SmartPtr<int> b(new int(9));
	std::cout << b - p << std::endl;			// 3
}
```
