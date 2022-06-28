# C++ 使用模板、引用求数组大小

## 核心代码

```cpp
template<typename T, int n>
inline int arr_size(T (&)[n])
{
     return n;
}
```

## 测试

```cpp
#include <iostream>
using namespace std;

template <typename T, int n>
inline int arr_size(T (&)[n])
{
    return n;
}

int main()
{
    int p[10];
    
    int n = arr_size(p);
    //int n = arr_size<int>(p);			// 可以调用模板函数
    //int n = arr_size<int, 10>(p);		// 可以调用模板函数
    
    cout << n << endl;			// 10
    return 0;
}
```

