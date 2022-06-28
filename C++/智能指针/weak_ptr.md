# weak_ptr

定义于头文件 `<memory>`，到 std::shared_ptr 所管理对象的弱引用

`std::weak_ptr` 是一种智能指针，它对被 std::shared_ptr管理的对象存在非拥有性（“弱”）引用。**在访问所引用的对象前必须先转换为 std::shared_ptr。**

`std::weak_ptr` 用来表达临时所有权的概念：当某个对象只有存在时才需要被访问，而且随时可能被他人删除时，可以使用 `std::weak_ptr` 来跟踪该对象。需要获得临时所有权时，则将其转换为 std::shared_ptr，此时如果原来的 std::shared_ptr 被销毁，则该对象的生命期将被延长至这个临时的 std::shared_ptr 同样被销毁为止。

`std::weak_ptr` 的另一用法是打断 std::shared_ptr 所管理的对象组成的环状引用。若这种环被孤立（例如无指向环中的外部共享指针），则 `shared_ptr` 引用计数无法抵达零，而内存被泄露。能令环中的指针之一为弱指针以避免此情况。

### reset

- 释放被管理对象的所有权。调用后 *this 不管理对象。

### swap

- 交换被管理对象

### use_count

- 返回管理该对象的 `shared_ptr` 对象数量

### expired

- 检查被引用的对象是否已删除

### lock

- 创建管理被引用的对象的`shared_ptr`

## 示例

```cpp
#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "use_count == " << gw.use_count() << ": ";
    if (auto spt = gw.lock()) { // 使用之前必须复制到 shared_ptr
		std::cout << *spt << "\n";
    }
    else {
         std::cout << "gw is expired\n";
    }
}
 
int main()
{
    {
        auto sp = std::make_shared<int>(42);
		gw = sp;
 
		observe();
    }
 
    observe();
}

// output:
// use_count == 1: 42
// use_count == 0: gw is expired
```

## 使用 weak_ptr 消除循环引用

```cpp
#include <iostream>
#include <memory>

class B;

class A {
public:
	std::shared_ptr<B> m_pb;
};

class B {
public:
	std::shared_ptr<A> m_pa;
};

int main()
{
	std::weak_ptr<A> w_pa;
	std::weak_ptr<B> w_pb;
	{
		std::shared_ptr<A> pa(new A);
		std::shared_ptr<B> pb(new B);

		pa->m_pb = pb;
		pb->m_pa = pa;

		w_pa = pa;
		w_pb = pb;

		std::cout << pa.use_count() << std::endl;		// 2
		std::cout << pb.use_count() << std::endl;		// 2
	}
	std::cout << w_pa.use_count() << std::endl;			// 1
	std::cout << w_pa.use_count() << std::endl;			// 1
}
```

上述代码中，pa 和 pb 之间相互引用，两个资源的引用计数为2，当调出作用域时，两个资源的引用数会减一，但两者的引用数还是1，致使资源并未被释放。

**解决方法：**

在类中定义的对方类指针，把其中一个改为 weak_ptr 就可以了，如下：

```cpp
#include <iostream>
#include <memory>

class B;

class A {
public:
	std::weak_ptr<B> m_pb;		// 改变处！！！
};

class B {
public:
	std::shared_ptr<A> m_pa;
};

int main()
{
	std::weak_ptr<A> w_pa;
	std::weak_ptr<B> w_pb;
	{
		std::shared_ptr<A> pa(new A);
		std::shared_ptr<B> pb(new B);

		pa->m_pb = pb;
		pb->m_pa = pa;

		w_pa = pa;
		w_pb = pb;

		std::cout << pa.use_count() << std::endl;		// 2
		std::cout << pb.use_count() << std::endl;		// 1
	}
	std::cout << w_pa.use_count() << std::endl;			// 0
	std::cout << w_pa.use_count() << std::endl;			// 0
}
```

如上所示，pb 的引用开始就是 1 ，当 pb 析构时，pb 的引用计数变为 0，B 得到释放，B 释放的同时也会使 A 的计数减一，同时 pa 析构时使 A 的计数减一，那么 A 的计数为 0，A 得到释放。
