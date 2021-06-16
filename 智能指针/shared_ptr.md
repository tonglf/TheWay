# shared_ptr

定义于头文件 `<memory>`，拥有共享对象所有权语义的智能指针。

```c++
template< class T > class shared_ptr;
```

`std::shared_ptr` 是通过指针保持对象共享所有权的智能指针。多个 `shared_ptr` 对象可占有同一对象。下列情况之一出现时销毁对象并解分配其内存：

- 最后剩下的占有对象的 `shared_ptr` 被销毁；
- 最后剩下的占有对象的 `shared_ptr` 被通过 operator= 或 reset() 赋值为另一指针。

### operator=

- 对 `shared_ptr` 赋值

### reset

- 替换所管理的对象

### swap

- 交换所管理的对象

### get

- 返回存储的指针

### use_count

- 返回 `shared_ptr` 所指对象的引用计数

```cpp
#include <memory> 
#include <iostream> 
 
void fun(std::shared_ptr<int> sp)
{
    std::cout << "fun: sp.use_count() == " << sp.use_count() << '\n'; 
}
 
int main() 
{ 
    auto sp1 = std::make_shared<int>(5);
    std::cout << "sp1.use_count() == " << sp1.use_count() << '\n'; 
 
    fun(sp1);
}

// output:
// sp1.use_count() == 1
// fun: sp.use_count() == 2
```

###  unique

- 检查 *this 是否管理当前对象的仅有 `shared_ptr` 实例，即是否 use_count() == 1 。

```c++
#include <memory> 
#include <iostream> 
 
int main() 
{ 
    auto sp1 = std::make_shared<int>(5);
    std::cout << std::boolalpha;
    std::cout << "sp1.unique() == " << sp1.unique() << '\n'; 
 
    std::shared_ptr<int> sp2 = sp1; 
    std::cout << "sp1.unique() == " << sp1.unique() << '\n'; 
}

// output:
// sp1.unique() == true
// sp1.unique() == false
```

## 实现shared_ptr

参考`shared_ptr代码实现`

