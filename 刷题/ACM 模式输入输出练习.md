# ACM 模式——输入输出练习

> 题目来源：牛客网

## 1. 计算 A + B (1)

**输入描述:**

```cpp
输入包括两个正整数 a, b (1 <= a, b <= 10^9), 输入数据包括多组。
```

**输出描述:**

```cpp
输出 a + b 的结果
```

**输入例子1:**

```cpp
1 5
10 20
```

**输出例子1:**

```cpp
6
30
```

**题解：**

```cpp
#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        cout << a + b << endl;
    }
    return 0;
}
```

## 2. 计算 A + B (2)

**输入描述:**

```cpp
输入第一行包括一个数据组数 t (1 <= t <= 100)
接下来每行包括两个正整数 a, b(1 <= a, b <= 10^9)
```

**输出描述:**

```cpp
输出 a + b 的结果
```

**输入例子1:**

```cpp
2
1 5
10 20
```

**输出例子1:**

```cpp
6
30
```

**题解：**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << a + b << endl;
    }
    return 0;
}
```

## 3. 计算 A + B (3)

**输入描述:**

```cpp
输入包括两个正整数 a, b (1 <= a, b <= 10^9), 输入数据有多组, 如果输入为 0 0 则结束输入
```

**输出描述:**

```cpp
输出 a + b 的结果
```

**输入例子1:**

```cpp
1 5
10 20
0 0
```

**输出例子1:**

```cpp
6
30
```

**题解：**

```cpp
#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;
        cout << a + b << endl;
    }
    return 0;
}
```

## 4. 计算 A + B (4)

**输入描述:**

```cpp
输入数据包括多组。
每组数据一行,每行的第一个整数为整数的个数 n (1 <= n <= 100), n 为 0 的时候结束输入。
接下来 n 个正整数,即需要求和的每个正整数。
```

**输出描述:**

```cpp
每组数据输出求和的结果
```

**输入例子1:**

```cpp
4 1 2 3 4
5 1 2 3 4 5
0
```

**输出例子1:**

```cpp
10
15
```

**题解：**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int b;
            cin >> b;
            sum += b;
        }
        cout << sum << endl;
    }
    return 0;
}
```

## 5. 计算 A + B (5)

**输入描述:**

```cpp
输入的第一行包括一个正整数 t (1 <= t <= 100), 表示数据组数。
接下来 t 行, 每行一组数据。
每行的第一个整数为整数的个数 n (1 <= n <= 100)。
接下来 n 个正整数, 即需要求和的每个正整数。
```

**输出描述:**

```cpp
每组数据输出求和的结果
```

**输入例子1:**

```cpp
2
4 1 2 3 4
5 1 2 3 4 5
```

**输出例子1:**

```cpp
10
15
```

**题解：**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int b;
            cin >> b;
            sum += b;
        }
        cout << sum << endl;
    }
    return 0;
}
```

## 6. 计算 A + B (6)

**输入描述:**

```cpp
输入数据有多组, 每行表示一组输入数据。
每行的第一个整数为整数的个数 n (1 <= n <= 100)。
接下来 n 个正整数, 即需要求和的每个正整数。
```

**输出描述:**

```cpp
每组数据输出求和的结果
```

**输入例子1:**

```cpp
4 1 2 3 4
5 1 2 3 4 5
```

**输出例子1:**

```cpp
10
15
```

**题解：**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int b;
            cin >> b;
            sum += b;
        }
        cout << sum << endl;
    }
    return 0;
}
```

## 7. 计算 A + B (7)

**输入描述:**

```cpp
输入数据有多组, 每行表示一组输入数据。

每行不定有 n 个整数，空格隔开。(1 <= n <= 100)。
```

**输出描述:**

```cpp
每组数据输出求和的结果
```

**输入例子1:**

```c++
1 2 3
4 5
0 0 0 0 0
```

**输出例子1:**

```c++
6
9
0
```

**题解：**

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a, sum = 0;
    while (cin >> a)
    {
        sum += a;
        if (cin.get() == '\n')
        {
            cout << sum << endl;
            sum = 0;
        }
    }
    return 0;
}
```

## 8. 字符串排序 (1)

**输入描述:**

```c++
输入有两行，第一行 n

第二行是 n 个空格隔开的字符串
```

**输出描述:**

```c++
输出一行排序后的字符串，空格隔开，无结尾空格
```

**输入例子1:**

```c++
5
c d a bb e
```

**输出例子1:**

```c++
a bb c d e
```

**题解：**

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    vector<string> vs;
    
    while (n--)
    {
        cin >> s;
        vs.push_back(s);
    }
    
    sort(vs.begin(), vs.end());
    for (int i = 0; i < vs.size() - 1; ++i)
    {
        cout << vs[i] << " ";
    }
    cout << vs[vs.size() - 1] << endl;
    
    return 0;
}
```

## 9. 字符串排序 (2)

**输入描述:**

```c++
多个测试用例，每个测试用例一行。

每行通过空格隔开，有 n 个字符，n ＜ 100
```

**输出描述:**

```c++
对于每组测试用例，输出一行排序过的字符串，每个字符串通过空格隔开
```

**输入例子1:**

```c++
a c bb
f dddd
nowcoder
```

**输出例子1:**

```c++
a bb c
dddd f
nowcoder
```

**题解：**

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    string s;
    vector<string> vs;
    vector<vector<string>> vvs;
    
    while (cin >> s)
    {
        vs.push_back(s);
        if (cin.get() == '\n')
        {
            sort(vs.begin(), vs.end());
            vvs.push_back(vs);
            vs.clear();
        }
    }
    
    for (int i = 0; i < vvs.size(); ++i)
    {
        for (int j = 0; j < vvs[i].size(); ++j)
        {
            cout << vvs[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

## 10. 字符串排序(3)

**输入描述:**

```cpp
多个测试用例，每个测试用例一行。
每行通过,隔开，有 n 个字符，n ＜ 100
```

**输出描述:**

```c++
对于每组用例输出一行排序后的字符串，用','隔开，无结尾空格
```

**输入例子1:**

```c++
a,c,bb
f,dddd
nowcoder
```

**输出例子1:**

```c++
a,bb,c
dddd,f
nowcoder
```

**题解：**

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    string s;
    vector<string> vs;
    
    while (getline(cin, s))
    {
        vs.clear();
        stringstream iss(s);
        
        while (getline(iss, s, ','))
        {
            vs.push_back(s);
        }
        
        sort(vs.begin(), vs.end());
        for (int i = 0; i < vs.size() - 1; ++i)
        {
            cout << vs[i] << ",";
        }
        cout << vs[vs.size() - 1] << endl;
    }
    return 0;
}
```

## 11. 自测本地通过提交为 0

每年前几场在线笔试编程题的时候，总有同学询问为什么我本地测试通过，自测也通过，提交代码系统却返回通过率 0。

这不是系统的错，可能是因为

1. 你对题目理解错了，你的代码只过了样例或你自己的数据

2. 你的代码逻辑有问题，你的代码只过了样例或你自己的数据

总之就是你的代码只是过了样例和自测数据，后台的测试数据你根本不可见，要多自己思考。

谨记：

当你笔试的时候怀疑系统或者题目数据有问题的时候请务必先怀疑自己的代码!

**输入描述:**

```c++
输入有多组测试用例，每组空格隔开两个整数
```

**输出描述:**

```c++
对于每组数据输出一行两个整数的和
```

**输入例子1:**

```c++
1 1
```

**输出例子1:**

```c++
2
```

**题解：**

```cpp
#include <iostream>
using namespace std;
 
int main()
{
    long long a, b;
    while (cin >> a >> b)
    {
        cout << a + b << endl;
    }
    return 0;
}
```