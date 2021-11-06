# Effective STL

## 50 条有效使用 STL 的经验

# 容器

## 1、慎重选择容器类型

**容器类型：**

> **序列容器：vector、string、deque、list、forward_list、array**
>
> **关联容器：set、multiset、map、multimap、unordered_set、unordered_map、unordered_multiset、unordered_multimap**
>
> **容器适配器：stack、queue、priority_queue**

**如何在 vector、deque 和 list 中做出选择？**

> vector、list 和 deque 为程序员提供了不同的复杂性， 使用时要对此做出权衡。
>
> vector 是默认应使用的序列类型；
>
> 当需要频繁地在序列中间 做插入和删除操作时，应使用 list;
>
> 当大多数插入和删除操作发生在序列的头部和尾部时，deque 是应考虑的数据结构。

**选择容器时最终要的一些问题**

- **你是否需要在容器的任意位置插入新元素？**

  ​	如果需要，就选择序列容器；关联容器是不行的。

- **你是否关心容器中的元素是如何排序的？**

  ​	如果不关心， 则哈希容器是一个可行的选择方案；否则，你要避免哈希容器。

- **你需要哪种类型的迭代器？**

  ​	如果它们必须是随机访问迭代器， 则对容器的选择就被限定为 vector、deque 和 string。如果要求使用双向迭代器， 那么你必须避免 forward_list (见第 50 条）以及哈希容器的一个常见实现（见第25条）。

- **当发生元素的插入或删除操作时， 避免移动容器中原来的元素是否很重要？**

  ​	如果是，就要避免连续内存的容器（见第5 条）。

- **容器中数据的布局是否需要和 C 兼容？**

  ​	如果需要兼容， 就只能选择 vector（见第 16 条）。

- **元素的查找速度是否是关键的考虑因素？**

  ​	如果是，就要考虑哈希容器（见第25条）、 排序的 vector (见第 23 条）和标准关联容器一一或许这就是优先顺序。

- **如果容器内部使用了引用计数技术(reference counting), 你是否介意？**

  ​	如果是， 就要避免使用 string，因为许多 string 的实现都使用了引用计数。当然，你需要某种表示字符串的方法，这时你可以考虑 vector\<char>。

- **对插入和删除操作，你需要事务语义 (transactional semantics) 吗？也就是说，在插入和删除操作失败时，你需要回滚的能力吗？**

  ​	如果需要，你就要使用基于节点的容器。如果对多个元素的插入操作（即针对一个区间的形式——见第 5 条）需要事务语义， 则你需要选择 list, 因为在标准容器中， 只有 list 对多个元素的插入操作提供了事务语义。对那些希望编写异常安全 (exception-safe)代码的程序员，事务语义显得尤为重要。（使用连续内存的容器也可以获得事务语义， 但是要付出性能上的代价， 而且代码也显得不那么直截了当。 更多细节，请参考 Sutter 的 Exceptional C++[8] 中的第 17 条。）

- **你需要使迭代器、指针和引用变为无效的次数最少吗？**

  ​	如果是这样， 就要使用基于节点的容器， 因为对这类容器的插入和删除操作从来不会使迭代器、 指针和引用变为无效（除非它们指向了一个你正在删除的元素）。 而针对连续内存容器的插入和删除操作一般会使指向该容器的迭代器、 指针和引用变为无效。

- **如果序列容器的迭代器是随机访问类型， 而且只要没有删除操作发生， 且插入操作只发生在容器的末尾， 则指向数据的指针和引用就不会变为无效， 这样的容器是否对你有帮助？**

  ​	这是非常特殊的情形， 但如果你面对的情形正是如此， 则 deque 是你所希望的容器。（有意思的是， 当插入操作仅在容器末尾发生时， deque 的迭代器有可能会变为无效。deque 是惟—的、 迭代器可能会变为无效而指针和引用不会变为无效的 STL 标准容器）。



## 2、不要试图编写独立于容器类型的代码

> **不要试图编写独立于容器类型的代码**

很多成员函数仅当其容器为某一类型时才存在，即一些成员函数是一些容器所特有的。

假设你想编写对大多数通用的容器都适用的代码，那么显然，你的程序只能使用它们功能的交集，这会使得一些成员函数、迭代器等等都不可使用，这使得你的容器效率大大降低，达不到想要的效果。

> **当你意识到自己选择的容器类型不是最佳的，想要使用另一种容器类型，应该如何操作呢？**

我们平时通常如下定义：

```cpp
class Widget{...};		// 自定义类型

vector<Widget> vw;

Widget bestWidget;
...
vector<Widget>::iterator i = find(vw.begin(), vw.end(), bestWidget);
```

假设以上代码，我们不想使用 `vector` 存储 `Widget` 了，那如何修改呢？只能将所有的`vector` 替换成 `list` 或者其他，这种修改是麻烦的。

所以要如下定义：

```cpp
class Widget{...};		// 自定义类型

typedef vector<Widget> WidgetContainer;
WidgetContainer cw;

Widget bestWidget;
...
WidgetContainer::iterator i = find(cw.begin(), cw.end(), bestWidget);
```

这样就使得改变容器类型要容易的多，只需将第三行的`vector` 替换成 `list`，仅仅一处修改。

这就是封装的效果。

**要想减少在替换容器类型时所需要修改的代码，可以把容器隐藏到一个类中，并尽量减少那些通过类接口（而使外部）可见的、与容器相关的信息。**

比如，你想创建一个顾客列表，不要直接使用`list`。相反，创建一个 `CustomerList` 类，并把 `list` 隐藏在其私有部分：

```cpp
class CustomerList {
private:
    typedef list<Customer> CustomerContainer;
    typedef CustomerContainer::iterator CCIterator;
    
    CustomerContainer customers;
    
public:
    ...
};
```

当然，以上这些改变，仍需要检查更改之后的容器与更改之前的容器在使用成员函数、迭代器等方面是否受到影响，如果在封装方面的实现细节做的很好，那么更改容器类型所受的影响应该可以减至最小。



## 3、确保容器中的对象拷贝正确而高效

一旦一个对象被保存到容器中，它经常会进一步被拷贝。当 `vector`、`string`、`deque` 进行元素的插入或删除操作时，现有元素的位置通常会被移动（复制）。

**如果向容器中填充对象，而对象的拷贝操作又很费时，那么向容器中填充对象这一简单的操作将会成为程序的性能瓶颈。放入容器中的对象越多，拷贝所需要的内存和时间就越多。**

当然，**在存在继承关系的情况下，拷贝动作会导致剥离（slicing）。即，如果你创建了一个存放基类对象的容器，却向其中插入派生类的对象，那么在派生类对象被拷贝进容器时，它所特有的部分（即派生类中的信息）将会丢失。**

使拷贝动作高效、正确，并防止剥离问题的发生的一个简单办法是**使用容器包含指针而不是对象**。进一步，避免内存泄漏可以传入智能指针。



## 4、调用 empty 而不是检查 size() 是否为 0

**`empty` 对所有的标准容器都是常数时间操作，而对一些 `list` 实现，`size` 耗费线性时间。**



## 5、区间成员函数优先与之对应的单元素成员函数

区间成员函数是指像 STL 算法一样，使用两个迭代器参数来确定该成员操作所执行的区间。

例如：给定 v1 和 v2 两个`vector`，使 v1 的内容和 v2 的后半部分相同的最简单的操作是什么？

```cpp
// 1.
v1.assign(v2.begin() + v2.size() / 2, v2.end);

// 2.
for (vector<Widget>::const_iterator ci = v2.begin() + v2.size() / 2; ci != v2.end(); ++ci)
    vi.push_back(*ci);
```

上述两种方法显然第一种方法更好，省去了显式的循环以及频繁的调用 `push_back` 函数。

**在哪些情况下使用区间操作大有好处？**

- **区间创建：** 所有标准容器都提供了如下形式的构造函数

```cpp
container::container(InputIterator begin, InputIterator end);
```

- **区间插入：** 

```cpp
// 标准序列容器
void container::insert(iterator position, InputIterator begin, InputIterator end);

// 标准关联容器
void container::insert(InputIterator begin, InputIterator end);

// 使用区间的 insert，省去了 push_front、push_back、front_inserter、back_inserter 的循环调用
```

- **区间删除：**

```cpp
// 标准序列容器
iterator container::erase(iterator begin, iterator end);	// 返回下一个有效的迭代器
	
// 标准关联容器
void container::erase(iterator begin, iterator end);		// 当前迭代器失效，后面的迭代器不失效
```

- **区间赋值:**

```cpp
void container::assign(InputIterator begin, InputIterator end);
```

**区间成员函数的优点：**

1. 区间成员函数写起来更容易；
2. 更能清楚表达你的意图；
3. 效率更高（使用单元素的成员函数比使用区间成员函数需要更多地调用内存分配子，更频繁的拷贝对象，或者做冗余的操作）。



## 6、当心 C++ 编译器最烦人的分析机制

下面的代码声明了一个带 `double` 参数并返回 `int` 的函数：

```cpp
int f(double d);

int f(double (d));		// 参数 d 两边的括号是多余的

int f(double)			// 省略了参数名称
```

再看三个函数声明：

```cpp
int g(double(*pf)());	// 函数 g，它的参数是一个指向不带任何参数的函数指针，该函数返回 double

int g(double pf());		// pf 用非指针的形式来声明，跟上面的声明意思一样

int g(double ());		// 参数名 pf 被忽略了
```

假设你有一个存有整数的文件，想把这个文件复制到一个 `list` 中，下面的做法：

```cpp
ifstream dataFile("ints.dat");
list<int> data(istram_iterator<int>(dataFile), istream_iterator<int>());
```

这种做法的思路是把一对 `istream_iterator` 传入到 `list` 的构造函数中，从而把文件中的整数复制到 `list` 中。

但这是错误的，达不到你想要的效果。

这里只是声明了一个函数，`data`，其返回值是 `list<int>`。这个 `data` 函数有两个参数：

- 第一个参数的名称是 `dataFile`。它的类型为 `istram_iterator<int>`。`dataFile` 两边的括号是多余的，会被忽略。
- 第二个参数没有名称。它的类型是指向不带参数的函数的指针，该函数返回一个 `istream_iterator<int>`。

你也曾遇到过下面这个错误：

```cpp
class Widget {...};		// 假定 Widget 有默认构造函数
Widget W();
```

它没有声明为 `w` 的 `Widget`，而是声明了一个名为 `w` 的函数，该函数不带任何参数，并返回 `Widget`。

现在，我们想用文件的内容初始化 `list<int>` 对象，必须绕过某一种分析机制。

把形式参数的声明用括号括起来是非法的，但给函数参数加上括号却是合法的，所以通过增加一对括号，强迫编译器按我们的方式来工作：

```cpp
list<int> data((istram_iterator<int>(dataFile)), istream_iterator<int>());
```

这种声明 `data` 的方式是正确的，但是，有些编译器不能通过编译。

更好的方式是在对  `data`  的声明中避免使用匿名的 `istram_iterator` 对象（尽管匿名对象是一种趋势），而是给这些迭代器一个名称：

```cpp
ifstream dataFile("ints.dat");
istram_iterator<int> dataBegin(dataFile);
istream_iterator<int> dataEnd;
list<int> data(dataBegin, dataEnd);
```

这种命名的迭代器对象与通常的 `STL` 程序风格相违背，但使得编译器没有二义性。



## 7、如果容器中包含了通过 new 操作创建的指针，切记在容器对象析构前将指针 delete 掉

下面的代码直接导致内存泄漏：

```cpp
void doSomething()
{
    vector<Widget*> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
        vwp.push_back(new Widget);
    ...
}
```

你可以这样删除它们：

```cpp
void doSomething()
{
    vector<Widget*> vwp;
    ...							// 同上
    for (vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i)
        delete *i;
}
```

而这种 `for` 循环不如 `for_each` 看起来那么清楚：

```cpp
struct DeleteObject{
    template<typename T>
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

void doSomething()
{
    vector<Widget*> vwp;
    ...							// 同上
    for_each(vwp.begin(), vwp.end(), DeleteObject());
}
```

但这两种解决方法仍然不是异常安全的。如果 `Widget` 已经被创建出来而对 `for_each` 的调用还没有开始时有异常抛出，则会有资源泄漏发生。

使用智能指针可解决该问题：

```cpp
void doSomethin()
{
    typedef std::shared_ptr<Widget> SPW;
    vector<SPW> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
    {
        vwp.push_back(SPW(new Widget));
    }
}

// 或

void doSomethin()
{
    vector<std::shared_ptr<Widget>> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
    {
        std::shared_ptr<Widget> p(new Widget);
        vwp.push_back(p);
    }
}
```

**当你使用指针的容器，而其中的指针应该被删除时，为了避免内存泄漏，你必须使用引用计数形式的智能指针对象代替指针，或者当容器被析构时手动删除其中的每个指针**。



## 8、切勿创建包含 auto_ptr 的容器对象

当你复制一个 `auto_ptr` 时，它所指向得对象所有权被移交到复制的 `auto_ptr` 上，而它自身被置为 `NULL`，即：复制一个 `auto_ptr` 意味着改变它的值：

```cpp
auto_ptr<Widget> pw1(new Widget);	// pw1 指向一个 Widget
auto_ptr<Widget> pw2(pw1);			// pw2 指向 pw1 的 Widget；pw1 被置为 NULL( Widget 的所有权从 pw1 转移到 pw2 上)

pw1 = pw2;							// 现在 pw1 又指向 Widget 了； pw2 被置为 NULL
```

不要创建包含 `auto_ptr` 的容器对象，因为在 STL 中，某些算法（如：` sort`）在底层实现的时候可能会定义临时的变量，将值传递到临时变量时，自身的值已经不存在了，这会导致错误。

C++ 11 已经将 `auto_ptr`  抛弃了。



## 9、慎重选择删除元素的方法

**要产出容器中的元素应该怎么做？**

- **要删除容器中有特定值的所有对象：**
  如果容器是 vector 、 string 或 deque, 则使用 erase-remove 习惯用法。
  如果容器是 list 则使用 list::remove。
  如果容器是一个标准关联容器， 则使用它的 erase 成员函数。

```cpp
// vector 、 string 或 deque
c.erase(remove(c.begin(), c.end(), 1936), c.end());

// list
c.remove(1936);

// 关联容器
c.erase(1936);
```

>**remove 函数：**
>
>​	从范围 `[first, last)` 移除所有满足特定判别标准的元素（**将需要移出的元素移动到容器的末尾，保持剩余元素的相对顺序而容器的物理大小保持不变**），并返回范围新结尾的尾后迭代器。
>
>```cpp
>#include <algorithm>
>#include <string>
>#include <iostream>
>#include <cctype>
> 
>int main()
>{
>    std::string str1 = "Text with some   spaces";
>    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());
>    std::cout << str1 << '\n';
> 
>    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
>    str2.erase(std::remove_if(str2.begin(), 
>                              str2.end(),
>                              [](unsigned char x){return std::isspace(x);}), 
>               str2.end());
>    std::cout << str2 << '\n';
>}
>```
>
>输出：
>
>```cpp
>Textwithsomespaces
>Textwithsomewhitespaces
>```

- **要删除容器中满足特定判别式（条件）的所有对象：**
  如果容器是 vector、 string 或 deque, 则使用 erase-remove_if 习惯用法。
  如果容器是 list. 则使用 list::remove_if。
  如果容器是一个标准关联容器， 则使用 remove_copy _if 和 swap, 或者写一个循环来 遍历容器中的元素， 记住当把迭代器传给 erase 时， 要对它进行后缀递增。

```cpp
// 特定判别式（条件）
bool badValue(int );

// vector、string 或 deque
c.erase(remove_if(c.begin(), c.end(), badValue), c.end());

// list
c.remove_if(badValue);

// 关联容器
AssocContainer<int> c;
...
AssocContainer<int> goodValues;		// 保存不被删除的值的临时容器
romove_copy_if(c.begin(), c.end(), inserter(goodValues, goodValues.end()), badValue);
c.swap(goodValues);			// 交换 c 和 goodValues 内容
```

- **要在循环内部做某些（除了删除对象之外的）操作：**
  如果容器是一个标准序列容器， 则写一个循环来遍历容器中的元素， 记住每次调 用 erase 时， 要用它的返回值更新迭代器。
  如果容器是一个标准关联容器， 则写一个循环来遍历容器中的元素， 记住当把迭代器传给 erase 时， 要对迭代器做后缀递增。

```cpp
// 序列容器 vector、 string 或 deque
for (SeqContainer<int>::iterator i = c.begin(); i != c.end(); )
{
    if (badValue(*i))
    {
        i = erase(i);		// 序列容器删除某个迭代器，当前迭代器与其之后的迭代器会失效，但会返回下一个有效的迭代器
    }
    else
        ++i;
}

// 关联容器
for (SeqContainer<int>::iterator i = c.begin(); i != c.end(); )
{
    if (badValue(*i))
    {
        erase(i++);		// 关联容器删除某个迭代器，当前迭代器失效，但其之后的迭代器不会失效，利用 i++ 指向下一个迭代器即可
    }
    else
        ++i;
}
```



## 10、了解分配子（allocator）的约定和限制

**如果你希望编写自 定义的分配子，都需要记住哪些内容：**

- 你的分配子是—个模板，模板参数 T 代表你为它分配内存的对象的类型。
- 提供类型定义 pointer 和 reference，但是始终让 pointer 为 T*，reference 为 T&。
- 千万别让你的分配子拥有随对象而不同的状态（per-objectstate）。通常，分配子不应该有非静态的数据成员。
- 记住，传给分配子的 allocate 成员函数的是那些要求内存的对象的个数，而不是所需的字节数。同时要记住，这些函数返回 T* 指针（通过 pointer 类型定义），即使尚未有 T 对象被构造出来。

- 一定要提供嵌套的 rebind 模板，因为标准容器依赖该模板。



## 11、理解自定义分配子的合理用法





## 12、切勿对 STL 容器的线程安全性有不切实际的依赖

现在考虑下面的代码。它在一个 `vector<int>` 中查找值为 5 的第一个元素，如果找到了，就把该元素究为 0。

```cpp
vector<int> v;
...
vector<int>::iterator first5(find(v.begin(), v.end(), 5));	// 第 1 行
if (first5 != v.end())										// 第 2 行
    *first5 = 0;											// 第 3 行
```

在一个多线程环境中，可能在第 1 行刚刚完成后，另一个不同的线程会更改 v 中的数据。如果这种更改真的发生了， 那么第 2 行对 first5 和 v.end 是否相等的检查将会变得没有意义， 因为 v 的值将会与在第 1 行结束时不同。 事实上， 这一检查会产生不确定的行为，因为另外一个线程可能会夹在第 1 行和第 2 行中间，使 first5 变得无效， 这第二个线程或许会执行一个插入操作使得 vector 重新分配它的内存（这会使 vector 所有的迭代器变得无效）。类似地， 第 3 行对 *first5 的赋值也是不安全的，因为另一个线程可能在第 2 行和第 3 行之间执行， 该线程可能会使 first5 无效， 例如可能会删除它所指向的元素（或者至少是曾经指向过的元素）。

上面的代码要做到线程安全， v 必须从第 1 行到第 3 行始终保持在锁住状态。在这种情况下， 你必须手工做同步控制。

 ```cpp
 vector<int> v;
 ...
 getMutexFor(v);
 vector<int>::iterator first5(find(v.begin(), v.end(), 5));	// 第 1 行
 if (first5 != v.end())										// 第 2 行
     *first5 = 0;											// 第 3 行
 releaseMutexFor(v);
 ```

为面向对象的方案是创建个 Lock 类， 它在构造函数中获得一个互斥体，在析构函数中释放它， 从而尽可能地减少 getMutexFor 调用没有相对应的 releaseMutexFor 调用的可能性。

```cpp
template<typename Container> 
class Lock{ 
public: 
    Lock(const Container& container) : c (container)
    {
        getMutexFor(c);
    }
    ~Lock()
    {
        releaseMutexFor(c);
    }
private:
    const Container c;
};

vector<int> v;
...
{										// 创建新的代码块
    Lock<vector<int>> lock(v);			// 获取互斥体
	vector<int>::iterator first5(find(v.begin(), v.end(), 5));	// 第 1 行
	if (first5 != v.end())										// 第 2 行
    	*first5 = 0;											// 第 3 行
}										// 代码块结束，自动释放互斥体
```

使用类（如 Lock）来管理资源的生存期的思想通常被称为＂获得资源时即初始化” (resource acquisition is initialization) 。



# vector 和 string

## 13、vector 和 string 优先于动态分配的数组

如果使用 `new` 来分配内存时，你通常需要搭配 `delete`，并且需要正确的配对。

`vector` 和 `string` 消除了上述的负担，因为它们自己管理内存。当元素被加入到容器中时，它们内存会增长；而当 `vector` 和 `string` 被析构时，它们的析构函数会自动析构容器中的元素并释放包含这些元素的内存。而且，`vector` 和 `string`  是功能完全的 `STL` 序列容器，凡是适合于序列容器的 `STL` 算法，都可以使用。

如果你正在动态的分配数组，那么你可能要做更多的工作，为了减轻自己的负担，请使用 `vector` 或 `string`。



## 14、使用 reserve 来避免不必要的重新分配

STL 容器，它们会自动增长以便容纳下放入其中的数据，对于 `vector` 和 `string`，增长过程是这样来实现的：每当需要更多空间时，就调 用与 `realloc` 类似的操作。这一类似于 `realloc` 的操作分为 4 部分：

> 1. 分配一块大小为当前容量的某个倍数的新内存。在大多数实现中，`vector` 和 `string`的容量每次以 2（Linux 为 2 倍，VS 2017 为 1.5 倍） 的倍数增长，即，每当容器前要扩张时，它们的容量即加倍。
> 2. 把容器的所有元索从旧的内存拷贝到新的内存中。
> 3. 析构掉旧内存中的对象。
> 4. 释放旧内存。

考虑到以上这些分配、释放、拷贝和析构步骤，这个过程会非常耗时。

通常有两种方式来使用 reserve 以避免不必要的重新分配。

- 第一种方式是， 若能确切知道或大致预计容器中最终会有多少元素， 则此时可使用 reserve。 在这种情况下， 可以简单地预留适当大小的空间。 
- 第二种方式是， 先预留足够大的空间（根据你的需要而定）， 然后，当把所有数据都加入以后，再去除多余的容量。 



## 15、注意 string 实现的多样性

string 实现的方式是多样的，这些不同实现的区别如下：

- string 的值可能会被引用计数，也可能不会。很多实现在默认情况下会使用引用计数 但它们通常提供了关闭默认选择的方法， 往往是通过预处理宏来做到这一点。第13 条给出了你想将其关闭的一种特殊情况，但其他的原因也可能会让你这样做。 比如，**只有当字符串被频繁拷贝时，引用计数才有用**，而有些应用并不经常拷贝内存，这就不值得使用引用计数了。
- string 对象大小的范围可以是一个 `char*` 指针的大小的 1 倍到 7 倍。
- 创建一个新的字符串值可能需要零次、一次或两次动态分配内存。
- string 对象可能共享，也可能不共享其大小和容量信息。
- string 可能支持，也可能不支持针对单个对象的分配子。
- 不同的实现对字符内存的最小分配单位有不同的策略。



## 16、了解如何把 vector 和 string 数据传给旧的 API

人们一直试图从数组中解放出来，转向使用 vector；同样努力地试图从 `char*` 指针转向 string 对象 。但障碍仍然存在， 最常见的一个障碍是， 旧的 C API 还存在， 它们使用数组和 `char*`  指针来进行数据交换而不是 vector 或 string 对象。

**解决方法：**

> 如果你有一 个 vector v，而你需耍得到一个指向 v 中数据的指针， 从而可把 v 中的数据作为数组来对待， 那么只需使用 `&v[0]` 就可以了。对于siring s，对应的形式是 `s.c_str()`。

如果我们希望把 v 传给一个如下所示的 C API：

```cpp
void doSomething(const int* pInts, size_t numInts); 
```

正确的做法是这样：

```cpp
if (!v.empty())		// 避免 v.size() 为 0，那么 &v[0] 会产生一个指向不存在东西的指针
{
    doSomething(&v[0], v.size());		
    // doSomething(&*v.begin(), v.size()); // 直接使用迭代器不行，需要解引用再引用，故不建议使用迭代器
}
```

`&v[0]` 这种得到容器中数据指针的方式对于 vector 是适用的，但对于 string 却是不可靠的。 因为： 

1. string 中的数据不一定存储在连续的内存中： 
2. string 的内部表示不一定是以空字符结尾的。 这也正说明了为什么在 string 中存在成员函数 c_str。 c_str 函数返回一个指向字符串的值的指针，而且该指针可用于 C。 囚此， 我们可以把一个字符串 s 传给下面的函数：

```cpp
void doSomething(const char* pString); 

doSomething(s.c_str());
```

**利用 vector，使其他容器与 C API 相容：**

```cpp
size_t fillArray(double* pArray, size_t arraySize); // 使用 fillArray 向 vd 中写入数据
vector<double> vd(maxNumDoubles); 
vd.resize(fillArray(&vd[O],vd.size()));

deque<double> d(vd.begin(), vd.end()); 	// 把数据拷贝到 deque 中
list<double> l(vd.begin(), vd.end()); 	// 把数据拷贝到 list 中
set<double> s(vd. begin(), vd. end());  // 把数据拷贝到 set 中                  
```

而且这意味着，除了 vector 和 string 以外的其他 STL 容器也能把它们的数据传递给 C API。你只需把每个容器的元素拷贝到一个 vector中，然后传给该 API：

```cpp
void doSomething(const int* plnts, size_t numlnts);
set<int> intSet;
...
vector<int> V(intSet.begin(),intSet.end()); // 把 set 的数据拷贝到 vector 
if (!v.empty())
    doSomething(&v[0], v.size()); // 把数据传给API   
```



## 17、使用 “swap 技巧” 除去多余的容量

为了避免 vector、string 仍占用不再需要的内存，你希望有一种方法能把它的容量从以前的最大值缩减到当前需要的数量。这种对容量的缩减通常被称为"**shrink to fit**" (压缩至适当大小）。

```cpp
class Contestant {...};
vector<Contestant> contestants;
contestants.push_back(...);				// 大量的 push_back
contestants.erase(...);/pop_back();		// 删除其中一部分数据    

// 使用 swap 去除多余的容量
vector<Contestant> (contestants).swap(contestants);
// vector<Contestant> temp(contestants).swap(contestants);	有名正常的 vector
// vector<Contestant> (contestants).swap(contestants);		匿名临时的 vector，都调用拷贝构造函数
```

表达式 `vector<Contestant> (contestants)` 创建一个临时的向量，它是 `contestants` 的拷贝：这是由 vector 的拷贝构造函数来完成的。然而，**vector 的拷贝构造函数只为所拷贝的元素分配所需要的内存，所以这个临时向量没有多余的容量。**然后我们把临时向量中的数据和 `contestants` 中的数据做 `swap` 操作，在这之后，`contestants` 具有了被去除之后的容量，即原先临时变量的容量，而临时变l量的容量则变成了原先 `contestants` 腌肿的容量。到这时（在语句结尾）， 临时向量被析构，从而释放了先前为 `contestants` 所占据的内存。

同样的方式也适用于 string：

```cpp
string s;
...					// 让 s 变大，然后删除它的大部分字符
string(s).swap(s); // 对 s 做 shrink-to-fit
```

swap 技巧的一种变化形式可以用来消除一个容器，并使其容量变为该实现下的最小值。只要与一个用默认构造函数创建的 vector 或string 做交换 (swap) 就可以了：

```cpp
vector<Contestant> v;
string s; 
...
vector<Contestant> ().swap(v); 
string ().swap(s); 
```

关于 swap 技巧， 或者关于一般性的 swap，在做 swap 的时候， 不仅两个容器的内容被交换，同时它们的迭代器、指针和引用也将被交换 ( string 除外）。在 swap 发生后， 原先指向某容器中元素的迭代器、 指针和引用依然有效， 并指向同样的元素，但是， 这些元素已经在另一个容器中了。

其实，在 C++ 11 中，已经有了 `shrink_to_fit` 函数，对于想清楚容器多余的容量，可以直接调用该函数：

```cpp
vector<Contestant> v;
string s; 
...
// 清除多余容量    
v.shrink_to_fit();
s.shrink_to_fit();

// 将容器清空
v.clear();
s.clear();

v.shrink_to_fit();
s.shrink_to_fit();
```



## 18、避免使用 vector\<bool>

作为—个STL容器， `vector<bool>` 只有两点不对。 首先，它不是一个 STL 容器。 其次，它并不存储 `bool`。

如果 `vector<bool>` 是一个容器， 那么下面这段代码必须可以被编译：

```cpp
vector<bool> v; 
bool *pb = &v[0];	// 编译错误
```

但是它不能编译。 不能编译的原因是， `vector<bool>` 是 一个假的容器，它并不真的储存 `bool`， 相反，为了节省空间，它储存的是 `bool` 的紧凑表示。在一个典型的实现中，储存在 `vector` 中的每个 `bool` 仅占一个二进制位，一个 8 位的字节可容纳 8 个 `bool` 。在内部，`vector<bool>` 使用了与位域（bitfield）一样的思想， 来表示它所存储的那些 `bool` ，实际上它只是假装存储了这些 `bool`。

位域与 `bool` 相似，它只能表示两个可能的值，但是在 `bool` 和看似 `bool` 的位域之间有一个很重要的区别：你可以创建一个指向 `bool` 的指针， 而指向单个位的指针则是不允许的。

**那么当你需要 `vector<bool>` 时， 应该使用什么呢？**

- 第一种是 `deque<bool>`，`deque<bool>` 是一个 STL 容器， 而且它确实存储 `bool`。

- 第二种可以替代 `vector<bool>`的选择是 `bitset`。`bitset` 不是 STL 容器， 但它是标准 C++ 库的一部分。与 STL 容器不同的是， 它的大小（即元素的个数）在编译时就确定了，所以它不支持插入和删除元素，也不支持迭代器。但是， 与 `vector<bool>` 一样， 它使用了 一种紧凑表示，只为所包含的每个值提供一位空间。 它提供了 `vector<bool>` 特有的加成员函数， 以及其他 一些特有的、对位的集合有意义的成员函数。如果你不需要迭代器和动态地改变大小， 那么你可能会发现 `bitset` 很适合你的需要。



# 关联容器



# 迭代器



# 算法



# 函数子、函数子类、函数及其他



# 在程序中使用 STL