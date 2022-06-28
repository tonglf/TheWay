# C 风格字符串常用函数

## 字符分类

定义于头文件 `<ctype.h>`，**若字符满足要求，返回非零值，否则返回 0**。

- `isalnum`   检查一个字符是否是字母或数字
- `isalpha`   检查一个字符是否是小写字母
- `isupper`   检查一个字符是否是大写字母
- `isdigit`   检查字符是否为数字
- `isblank`   检查一个字符是否是空格字符

 函数原型均为：`int fun( int ch );`，用法为：`函数名(字符)`，例如：`isalnum('9')`。

## 字符操作

定义于头文件 `<ctype.h>`

- `tolower`   将字符转换成小写
- `toupper`   将字符转换成大写

 函数原型均为：`int fun( int ch );`，用法为：`函数名(字符)`，例如：``tolower('A')`。

## 转换成数值格式

定义于头文件 `<stdlib.h>`

- `atof`  将字节字符串转换成浮点值
- `atoi\atol\atoll`   将字节字符串转换成整数值

函数原型均为：`int fun( const char *str );`，用法为：`函数名(字符串)`，例如：``atoi("123")`。

**示例：**

```cpp
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    printf("%i\n", atoi(" -123junk"));		// -123
    printf("%i\n", atoi("0"));				// 0
    printf("%i\n", atoi("junk"));         	// 0 无可进行的转换
    printf("%i\n", atoi("2147483648"));   	// -2147483648 UB ：在 int 范围外
}
```

## 字符串操作

**定义于头文件 `<string.h>`**

**`strcpy` 复制一个字符串给另一个**

- `char *strcpy( char *dest, const char *src );`

  **返回值：**

  - 返回 `dest` 的副本
  - 成功时返回零，失败时返回非零

示例：

```cpp
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *src = "Take the test.";
	//  src[0] = 'M' ; // 这会是未定义行为
    char dst[strlen(src) + 1]; // +1 以适应空终止符
    strcpy(dst, src);
    dst[0] = 'M'; // OK
    printf("src = %s\ndst = %s\n", src, dst);
}
// src : Take the test.
// dst : Make the test.
```

**`strcat` 连接两个字符串**

- `char *strcat( char *dest, const char *src );`

  **返回值：**

  - 返回 `dest` 的副本
  - 成功时返回零，失败时返回非零

示例：

```cpp
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
 
int main() 
{
    char str[50] = "Hello ";
    char str2[50] = "World!";
    strcat(str, str2);
    strcat(str, " ...");
    strcat(str, " Goodbye World!");
    printf("src = %s\n", src);		// Hello World! ... Goodbye World!
}
```

## 字符串检验

**定义于头文件 `<string.h>`**

**`strlen` 返回给定字符串的长度**，不包含'\0'

- `size_t strlen( const char *str );`

示例：

```cpp
int a = strlen("abc");		// 3
int b = strlen("ac ed");	// 5
int c = strlen(" a b ");	// 5
```

**`strcmp` 比较两个字符串**

- `int strcmp( const char *lhs, const char *rhs );`

  **返回值：**

  	- 若字典序中 `lhs` 先出现于 `rhs` 则为负值。 `lhs  <  rhs`
  	- 若 `lhs` 与 `rhs` 比较相等则为零。`lhs  =  rhs`
  	- 若字典序中 `lhs` 后出现于 `rhs` 则为正值。`lhs  >  rhs`

示例：

```cpp
int a = strcmp("one", "two");	// -1
int b = strcmp("two", "two");	// 0
int c = strcmp("two", "three");	// 1
```

**`strchr` 查找字符的首次出现**

- `char *strchr( const char *str, int ch );`

  **返回值:**

  - 指向 `str` 找到的字符的指针，若未找到该字符则为空指针。

示例：

```cpp
const char* p1 = strchr("hello", 'l');
printf("%s\n", p1);						// llo
const char* p3 = strchr("hello", 'a');
printf("%s\n", p3);						// (null)
```

**`strrchr` 查找字符的最后一次出现**

- `char *strrchr( const char *str, int ch );`

  **返回值:**

  - 指向 `str` 找到的字符的指针，若未找到该字符则为空指针。

示例：

```cpp
const char* p2 = strrchr("hello", 'l');
printf("%s\n", p2);						// lo
const char* p4 = strrchr("hello", 'a');
printf("%s\n", p4);						// (null)
```

**`strstr` 查找子串字符的首次出现**

- ` char *strstr( const char* str, const char* substr );`

  **返回值：**

   - 指向于 `str` 中找到的子串首字符的指针，或若找不到该子串则为空指针。若 `substr` 指向空字符串，则返回 `str` 。

示例：

```cpp
#include <stdio.h>
#include <string.h>

int main()
{
	const char* pos1 = strstr("one two three", "two");
	printf("%s\n", pos1);								// two three
	const char* pos2 = strstr("one two three", "four");
	printf("%s\n", pos2);								// (null)
	return 0;
}
```



