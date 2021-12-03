# 完整版的 strcpy 函数

```c
char* strcpy(char* strDest, const char* strSrc)				// 将源字符串加 const，表明其为输入参数
{
    assert((strDest != nullptr) && (strSrc != nullptr));	// 对源地址和目的地址加非 0 断言
    
    char* address = strDest;
    
    while ((*strDest++ = *strSrc++) != '\0');
    
    return address;				// 为了实现链式操作，将目的地址返回
}
```

