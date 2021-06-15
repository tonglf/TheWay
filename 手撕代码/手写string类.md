# 手写 string 类

```cpp
#ifndef __MYSTRING__
#define __MYSTRING__

#include <cstring>
#include <iostream>

class String
{
public:
	String(const char* cstr = 0);			// 构造函数
	String(const String& str);				// 拷贝构造函数
	String(String&& str);					// 移动构造函数
	String& operator=(const String& str);	// 拷贝赋值函数
	~String();								// 析构函数

	char* get_c_str() const { return m_data; }

private:
	char* m_data;
};

// 构造函数
inline
String::String(const char* cstr)
{
	if (cstr) {
		m_data = new char[strlen(cstr) + 1];
		strcpy(m_data, cstr);
	}
	else {
		m_data = new char[1];
		*m_data = '\0';
	}
}

// 拷贝构造函数
inline
String::String(const String& str)
{
	m_data = new char[strlen(str.m_data) + 1];
	strcpy(m_data, str.m_data);
}

// 移动构造函数
inline
String::String(String&& str) : m_data(str.m_data)
{
	str.m_data = nullptr;
}

// 拷贝赋值函数
inline
String& String::operator=(const String& str)
{
	if (this == &str)
	{
		return *this;
	}

	delete[] m_data;
	m_data = new char[strlen(str.m_data) + 1];
	strcpy(m_data, str.m_data);
	return *this;
}

// 拷贝赋值函数		另外的写法
//inline
//String& String::operator=(const String& str)
//{
//	String* temp = new char[strlen(str.m_data) + 1];
//	delete[] m_data;
//	strcpy(m_data, temp);
//	return *this;
//}

// 析构函数
inline
String::~String()
{
	delete[] m_data;
}

// 输出操作符重载需设置成非成员函数
std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.get_c_str();
	return os;
}

#endif
```

