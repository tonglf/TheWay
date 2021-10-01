# LRU Cache

## LRU 算法简介

LRU 全称 Least Recently Used，也就是**最近最少使用**的意思，是一种内存管理算法，最早应用与 Linux 操作系统。LRU 算法基于一种假设：==长期不被使用的数据，在未来被用到的几率也不大，因此，**当数据所占内存达到一定阈值时，我们要移除掉最近最少被使用的数据**。==

## 代码实现

```cpp
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
private:
	struct CacheNode
	{
		int key;
		int value;
		CacheNode(int k, int v) : key(k), value(v) { }
	};

public:
	LRUCache(int capacity) : m_capacity(capacity) { }

	int get(int key)
	{
		if (m_cacheMap.find(key) == m_cacheMap.end())
		{
			return -1;
		}

		// 把当前访问的节点移到链表的头部，并且更新 map 中该节点的地址
        // 把 m_cacheList 中 key 对应的迭代器放置到 m_cacheList.begin() 位置上
		m_cacheList.splice(m_cacheList.begin(), m_cacheList, m_cacheMap[key]); 
		m_cacheMap[key] = m_cacheList.begin();
		return m_cacheMap[key]->value;
	}

	void set(int key, int value)
	{
		if (m_cacheMap.find(key) == m_cacheMap.end())
		{
			if (m_cacheList.size() == m_capacity)
			{
				m_cacheMap.erase(m_cacheList.back().key);
				m_cacheList.pop_back();
                --m_capacity;
			}
			// 插入新节点到链表头部，并且在 map 中增加该节点
			m_cacheList.push_front(CacheNode(key, value));
			m_cacheMap[key] = m_cacheList.begin();
            ++m_capacity;
		}
		else
		{
			// 更新节点的值，把当前访问的节点移到链表头部，并且更新 map 中该节点的地址
			m_cacheMap[key]->value = value;
			m_cacheList.splice(m_cacheList.begin(), m_cacheList, m_cacheMap[key]);
			m_cacheMap[key] = m_cacheList.begin();
		}
	}

private:
	list<CacheNode> m_cacheList;
	unordered_map<int, list<CacheNode>::iterator> m_cacheMap;
	int m_capacity;
};
```

## 测试

```cpp
// 在类中加入打印链表的函数
class LRUCache
{
    // ...
	void printList()
	{
		list<CacheNode>::iterator itor = m_cacheList.begin();
		for (; itor != m_cacheList.end(); itor++)
		{
			cout << "key : " << itor->key << " | " << "value : " << itor->value << endl;
		}
		cout << endl;
	}    
    // ...
};

void main()
{
	LRUCache cache( 5 );

	cache.set( 1, 100 );
	cache.set( 2, 200 );
	cache.set( 3, 300 );
	cache.set( 4, 400 );
	cache.set( 5, 500 );

	cache.printList();

	cache.get( 3 );
	cache.get( 2 );

	cache.printList();

	cache.set( 6, 600 );
	cache.set( 5, 700 );

	cache.printList();
}
```

**输出结果：**

```cpp
key : 5 | value : 500
key : 4 | value : 400
key : 3 | value : 300
key : 2 | value : 200
key : 1 | value : 100

key : 2 | value : 200
key : 3 | value : 300
key : 5 | value : 500
key : 4 | value : 400
key : 1 | value : 100

key : 5 | value : 700
key : 6 | value : 600
key : 2 | value : 200
key : 3 | value : 300
key : 4 | value : 400
```

## 附：splice 函数用法

**splice 函数**: **从一个 list 转移元素给另一个。** 不复制或移动元素，仅重指向链表结点的内部指针。

**函数原型：**

```cpp
// 1、从 other 转移所有元素到 *this 中。元素被插入到 pos 所指向的元素之前。操作后容器 other 变为空。若 other 与 *this 指代同一对象则行为未定义。
void splice( const_iterator pos, list&& other );

// 2、从 other 转移 it 所指向的元素到 *this 。元素被插入到 pos 所指向的元素之前。
void splice( const_iterator pos, list&& other, const_iterator it );

// 3、从 other 转移范围 [first, last) 中的元素到 *this 。元素被插入到 pos 所指向的元素之前。若 pos 是范围 [first,last) 中的迭代器则行为未定义。
void splice( const_iterator pos, list&& other,
             const_iterator first, const_iterator last );
```

**测试：**

```cpp
#include <iostream>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
void main ()
{
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    std::list<int> list2 = { 10, 20, 30, 40, 50 };
 
    auto it = list1.begin();
    std::advance(it, 2);
 
    // 将 list2 中的所有元素放置带 it 位置上，此时 list2 为空，it 位置在插入的 list2 之后
    list1.splice(it, list2);
 
    std::cout << "list1: " << list1 << "\n";	// list1:  1 2 10 20 30 40 50 3 4 5
    std::cout << "list2: " << list2 << "\n";	// list2: 
 
    // 将 list1 从 it 到 list1.end() 中的所有元素放置到 list2.begin() 位置上
    list2.splice(list2.begin(), list1, it, list1.end());
 
    std::cout << "list1: " << list1 << "\n";	// list1:  1 2 10 20 30 40 50
    std::cout << "list2: " << list2 << "\n";	// list2:  3 4 5
}
```



