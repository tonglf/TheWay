# unique_ptr

定义于头文件 `<memory>`，拥有独有对象所有权语义的智能指针

```c++
template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;
```

`std::unique_ptr` 是通过指针占有并管理另一对象，并在 `unique_ptr` 离开作用域时释放该对象的智能指针。

在下列两者之一发生时用关联的删除器释放对象：

- 销毁了管理的 `unique_ptr` 对象

- 通过 operator=或 reset() 赋值另一指针给管理的 `unique_ptr` 对象。

`unique_ptr` 亦可以不占有对象，该情况下称它为*空 (empty)*。

`std::unique_ptr` 有两个版本：

- 1) 管理单个对象（例如以 new 分配）

- 2) 管理动态分配的对象数组（例如以 new[] 分配）

只有非 const 的 `unique_ptr` 能转移被管理对象的所有权给另一 `unique_ptr` 。若对象的生存期为 const std::unique_ptr 所管理，则它被限定在创建指针的作用域中。

### operator=  
- 为`unique_ptr`赋值

```c++
#include <iostream>
#include <memory>
 
struct Foo {
    Foo() { std::cout << "Foo\n"; }
    ~Foo() { std::cout << "~Foo\n"; }
};
 
int main() 
{
    std::unique_ptr<Foo> p1;
 
    {
        std::cout << "Creating new Foo...\n";
        std::unique_ptr<Foo> p2( std::make_unique<Foo>() );
        // p1 = p2; // 错误！不能复制 unique_ptr
        p1 = std::move(p2);
        std::cout << "About to leave inner block...\n";
 
        // Foo 实例将继续生存，尽管 p2 离开作用域
    }
 
    std::cout << "About to leave program...\n";
}

// 输出：
   	// Creating new Foo...
	// Foo
	// About to leave inner block...
	// About to leave program...
	// ~Foo
```

### reset

- 替换被管理对象

### release  

- 返回一个指向被管理对象的指针，并释放所有权

```c++
#include <memory>
#include <iostream>
#include <cassert>
 
struct Foo {};
 
int main()
{
    std::cout << "Creating new Foo...\n";
    std::unique_ptr<Foo> up(new Foo());
 
    std::cout << "About to release Foo...\n";
    Foo* fp = up.release();
 
    assert (up.get() == nullptr);
    std::cout << "Foo is no longer owned by unique_ptr...\n";
 
    delete fp;
}
```

### swap  
- 交换被管理对象
```cpp
#include <iostream>
#include <memory>
 
struct Foo {
    Foo(int _val) : val(_val) { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
    int val;
};
 
int main()
{
    std::unique_ptr<Foo> up1(new Foo(1));
    std::unique_ptr<Foo> up2(new Foo(2));
 
    up1.swap(up2);
 
    std::cout << "up1->val:" << up1->val << std::endl;		// 2
    std::cout << "up2->val:" << up2->val << std::endl;		// 1
}
```

### get  

- 返回指向被管理对象的指针，如果无被管理对象，则为 nullptr

```cpp
#include <iostream>
#include <string>
#include <memory>
 
int main()
{
    std::unique_ptr<std::string> s_p(new std::string("Hello, world!"));
    std::string *s = s_p.get();
    std::cout << *s << '\n';		// Hello, world!
}
```

### std::make_unique

 - 创建管理一个新对象的独占指针

```cpp
    // 使用默认构造函数。
    std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
    // 使用匹配这些参数的构造函数
    std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
    // 创建指向 5 个元素数组的 unique_ptr 
    std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);

#include <iostream>
#include <memory>
 
struct Vec3
{
    int x, y, z;
    // C++20 起不再需要以下构造函数
    Vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) { }
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
    {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
    }
};
 
int main()
{
    // 使用默认构造函数。
    std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
    // 使用匹配这些参数的构造函数
    std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
    // 创建指向 5 个元素数组的 unique_ptr 
    std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);
 
    std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
              << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
              << "make_unique<Vec3[]>(5):   " << '\n';
    for (int i = 0; i < 5; i++) {
        std::cout << "     " << v3[i] << '\n';
    }
}

// output：
// make_unique<Vec3>():      {x:0 y:0 z:0}
// make_unique<Vec3>(0,1,2): {x:0 y:1 z:2}
// make_unique<Vec3[]>(5):   
//     	{x:0 y:0 z:0}
//      {x:0 y:0 z:0}
//      {x:0 y:0 z:0}
//      {x:0 y:0 z:0}
//      {x:0 y:0 z:0}
```

