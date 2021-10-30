# C++ 学习笔记
## C++编程技巧与规范
### 类和对象
- [第一节 静态对象的探讨与全局对象的构造顺序](./C++编程技巧与规范/1.1类和对象.md)
- [第二节 拷贝构造函数和拷贝赋值运算符](./C++编程技巧与规范/1.2类和对象.md)
- [第三节 类的 public 继承（ is - a 关系）及代码编写规则](./C++编程技巧与规范/1.3类和对象.md)
- [第四节 类与类之间的组合关系与委托关系](./C++编程技巧与规范/1.4类和对象.md)
- [第五节 类的 private 继承探讨](./C++编程技巧与规范/1.5类和对象.md)
- [第六节 不能被拷贝构造和拷贝赋值的类对象](./C++编程技巧与规范/1.6类和对象.md)
- [第七节 虚析构函数的内存泄漏问题深谈](./C++编程技巧与规范/1.7类和对象.md)
- [第八节 类设计中的一些技巧](./C++编程技巧与规范/1.8类和对象.md)
- [第九节 命名空间使用的一些注意事项](./C++编程技巧与规范/1.9类和对象.md)
- [第十节 类定义的相互依赖与类的前项声明](./C++编程技巧与规范/1.10类和对象.md)

### 引用计数基础理论和实战

- [第一节 shared_ptr 实现及 string 存储简单说明](./C++编程技巧与规范/2.1引用计数基础理论和实战.md)
- [第二节 写时复制的 string 类 （copy-on-write）](./C++编程技巧与规范/2.2写时复制的string类.md)

## 设计模式

### 设计模式原则

- [设计模式原则](./设计模式/设计模式原则.md)
- [单一职责原则](./设计模式/单一职责原则.md)
- [接口隔离原则](./设计模式/接口隔离原则.md)
- [依赖倒置原则](./设计模式/依赖倒置原则.md)
- [里氏替换原则](./设计模式/里氏替换原则.md)
- [开闭原则](./设计模式/开闭原则.md)
- [迪米特原则](./设计模式/迪米特原则.md)
- [合成复用原则](./设计模式/合成复用原则.md)

### 常用设计模式

- [单例模式 Singleton](./设计模式/01单例模式.md)
- [工厂方法 Factory Method](./设计模式/02工厂方法.md)
- [抽象工厂 Abstract Factory](./设计模式/03抽象工厂.md)
- [原型模式 Prototype](./设计模式/04原型模式.md)
- [模板方法 Template Method](./设计模式/05模板方法.md)
- [策略模式 Strateg](./设计模式/06策略模式.md)
- [策略模式-简单版 Strateg](./设计模式/06策略模式-简单版.md)
- [观察者模式 Observer](./设计模式/07观察者模式.md)
- [装饰器模式 Decorator](./设计模式/08装饰器模式.md)
- [桥接模式 Bridge](./设计模式/09桥接模式.md)
- [代理模式 proxy](./设计模式/10代理模式.md)
- [状态模式 State](./设计模式/11状态模式.md)
- [建造者模式 Builder](./设计模式/12建造者模式.md)
- [享元模式 Flyweight](./设计模式/13享元模式.md)

## 智能指针

- [unique_ptr](./智能指针/unique_ptr.md)

- [shared_ptr](./智能指针/shared_ptr.md)

- [weak_ptr](./智能指针/weak_ptr.md)

## C++ 知识点

- [C++的四种类型转换](./C++知识点/C++的四种类型转换.md) 
- [多参数模板的使用](./C++知识点/多参数模板的使用.md)
- [内存对齐](./C++知识点/内存对齐.md)
- [C 风格字符串常用函数](./C++知识点/C风格字符串常用函数.md)
- [泛型编程-模板与STL](./C++知识点/泛型编程-模板与STL.md)
- [输出操作符重载的类内、类外实现](./C++知识点/输出操作符重载的类内、类外实现.md)
- [C++ 使用模板、引用求数组大小](./C++知识点/C++使用模板、引用求数组大小.md)
- [内存分配函数该怎么写？指针传递也发生拷贝？](./C++知识点/内存分配函数该怎么写？指针传递也发生拷贝？.md)
- [不同进制之间的相互转换](./C++知识点/不同进制之间的相互转换.md)

## 手撕代码

- [strcpy 函数](./手撕代码/完整版的strcpy函数.md)
- [string 函数](./手撕代码/手写string类.md)
- [写时复制的 string 类 （copy-on-write）](./C++编程技巧与规范/2.2写时复制的string类.md)
- [shared_ptr](./手撕代码/shared_ptr代码实现.md)
- [vector 简单实现](./手撕代码/vector简单实现.md)
- [LRU Cache](./手撕代码/LRUCache.md)

## Linux 杂谈

- [top、ps 命令](./Linux杂谈/top、ps.md)
- [clang-tidy](./Linux杂谈/clang-tidy.md)

### Linux 系统编程

- [Linux 基本命令](./Linux杂谈/Linux系统编程/01_Linux基本命令.md)
- [Linux 常用工具](./Linux杂谈/Linux系统编程/02_Linux常用工具.md)
- [GDB 与 Makefile](./Linux杂谈/Linux系统编程/03_GDB与Makefile.md)
- [系统函数：open、close、read、write](./Linux杂谈/Linux系统编程/04_系统函数.md)
- [进程](./Linux杂谈/Linux系统编程/05_进程.md)
- [进程间通信](./Linux杂谈/Linux系统编程/06_进程间通信.md)
- [线程](./Linux杂谈/Linux系统编程/07_线程.md)

### Linux 网络编程

- [Linux 下常用的网络命令](./Linux杂谈/Linux网络编程/Linux下常用的网络命令.md)
- [CS 模型 - TCP](./Linux杂谈/Linux网络编程/CS模型-TCP.md)
- [多进程并发服务器](./Linux杂谈/Linux网络编程/多进程并发服务器.md)
- [多线程并发服务器](./Linux杂谈/Linux网络编程/多线程并发服务器.md)
- [多线程详解](./Linux杂谈/Linux网络编程/多线程详解.md)
- [多路 IO 转接 - select](./Linux杂谈/Linux网络编程/多路IO转接-select.md)
- [多路 IO 转接 - poll](./Linux杂谈/Linux网络编程/多路IO转接-poll.md)
- [多路 IO 转接 - epoll](./Linux杂谈/Linux网络编程/多路IO转接-epoll.md)
- [epoll 事件模型 LT、ET](./Linux杂谈/Linux网络编程/epoll事件模型LT、ET.md)
- [CS 模型 - UDP](./Linux杂谈/Linux网络编程/CS模型-UDP.md)
- [线程池](./Linux杂谈/Linux网络编程/线程池/线程池.md)
- [手写线程池 - C语言版](./Linux杂谈/Linux网络编程/手写线程池 - C语言版.md)
- [网络编程实战](./Linux杂谈/Linux网络编程/网络编程实战.md)
- [五大 IO 模型](./Linux杂谈/Linux网络编程/五大IO模型.md)
- [select 、poll 和 epoll 对比](./Linux杂谈/Linux网络编程/select、poll和epoll对比.md)

## 数据库

[linux下数据库的安装与配置](./数据库/linux下数据库的安装与配置.md)

### MySQL 3306

- [MySQL 基础知识](./数据库/MySQL/MySQL基础知识.md)
- [MySQL 练习题](./数据库/MySQL/MySQL练习题.md)
- [MySQL 实战45讲](./数据库/MySQL/MySQL实战45讲/00MySQL实战45讲.md)

### Redis 6379

- [Redis 常用五大数据类型](./数据库/Redis/Redis常用五大数据类型.md)

## 刷题

- [ACM 模式——输入输出练习](./刷题/ACM 模式——输入输出练习.md)
- [二叉树前中后遍历--统一的递归、迭代写法](./刷题/二叉树前中后遍历--统一的递归、迭代写法.md)
- [数组，找到每个元素后面比它大的第一个数](./刷题/数组，找到每个元素后面比它大的第一个数.md)
- [剑指offer](./刷题/剑指offer.md)
- [十大排序算法](./刷题/十大排序算法.md)
- [二分法练习题](./刷题/二分法练习题.md)
- [LeetCode 热题 HOT 100 题](./刷题/LeetCode热题HOT100.md)
- [反转链表](./刷题/反转链表.md)
- [面试中遇到的算法题](./刷题/面试中遇到的算法题.md)

## 读书笔记

[Effective C++](./读书笔记/EffectiveC++/EffectiveC++读书笔记.md)

[More Effective C++](./读书笔记/MoreEffectiveC++/MoreEffectiveC++.md)

[Effective STL](./读书笔记/Effective STL/Effective STL.md)

秋招面经总结

- [秋招面经总结 C++ 篇](./读书笔记/秋招面经总结C++/秋招面经总结 C++ 篇.md)
- [秋招面经总结 STL 篇](./读书笔记/秋招面经总结C++/秋招面经总结 STL 篇.md)
- [秋招面经总结 MySQL 篇](./读书笔记/秋招面经总结C++/秋招面经总结 MySQL 篇.md)
