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



## 6、



## 7、



## 8、



## 9、



## 10、



## 11、



# vector 和 string



# 关联容器



# 迭代器



# 算法



# 函数子、函数子类、函数及其他



# 在程序中使用 STL