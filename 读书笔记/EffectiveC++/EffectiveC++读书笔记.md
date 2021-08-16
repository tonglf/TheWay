# Effective C++ 改善程序与设计的55个具体做法
@[TOC](目录)
## 1、让自己习惯C++ <br> &emsp;&emsp;Accusoming Yourself to C++
&emsp;条款01：视C++为一个语言联邦
&emsp;条款02：尽量以const，enum，inline 替换 #define
&emsp;条款03：尽可能使用const
&emsp;条款04：确定对象被使用前先被初始化

链接: [Effective C++ 第一章 让自己习惯C++](https://blog.csdn.net/weixin_45867382/article/details/116494053)

## 2、构造/析构/赋值运算 <br> &emsp;&emsp;Constructors,Destructors,and Assignment Operators
&emsp;条款05：了解 C++ 默默编写并调用哪些函数

&emsp;条款06：若不想使用编译器自动生成的函数，就该明确拒绝

&emsp;条款07：为多态基类声明 virtual 析构函数

&emsp;条款08：别让异常逃离析构函数

&emsp;条款09：绝不在构造和析构过程中调用 virtual 函数

&emsp;条款10：令 operator= 返回一个 *reference to *this*

&emsp;条款11：在 operator= 中处理“自我赋值”

&emsp;条款12：复制对象时勿忘其每一个成分

链接: [Effective C++ 第二章 构造/析构/赋值运算](https://blog.csdn.net/weixin_45867382/article/details/116494250)

## 3、资源管理 <br> &emsp;&emsp;Resource Management
&emsp;条款13：以对象管理资源

&emsp;条款14：在资源管理类中小心 coping 行为

&emsp;条款15：在资源管理类中提供对原始资源的访问

&emsp;条款16：成对使用 new  和 delete 时要采取相同形式

&emsp;条款17：以独立语句 newed 对象置入智能指针

链接: [Effective C++ 第三章 资源管理](https://blog.csdn.net/weixin_45867382/article/details/116494312)

## 4、设计与声明 <br> &emsp;&emsp;Designs and Declarations
&emsp;条款18：让接口容易被正确使用，不易被误用

&emsp;条款19：设计 class 犹如设计 type

&emsp;条款20：宁以 pass-by-reference-to-const 替换 pass-by-value

&emsp;条款21：必须返回对象时，别妄想返回其 reference

&emsp;条款22：将成员变量声明为 private

&emsp;条款23：宁以 non-member、non-friend 替换 member 函数

&emsp;条款24：若所有参数皆需类型转换，请为此采用 non-member 函数

&emsp;条款25：考虑写出一个不抛异常的 swap 函数

链接: [Effective C++ 第四章 设计与声明](https://blog.csdn.net/weixin_45867382/article/details/116494349)


## 5、实现 <br> &emsp;&emsp;Implementations
&emsp;条款26：尽可能延后变量定义式的出现时间

&emsp;条款27：尽量少做转型动作

&emsp;条款28：避免返回 handles 指向对象内容的部分

&emsp;条款29：为“异常安全”而努力是值得的

&emsp;条款30：透彻了解 inlining 的里里外外

&emsp;条款31：将文件间的编译依存关系降至最低

链接: [Effective C++ 第五章 实现](https://blog.csdn.net/weixin_45867382/article/details/116494395)

## 6、继承与面向对象设计 <br> &emsp;&emsp;Inheritance and Object-Oriented Design
&emsp;条款32：确定你的 public 继承塑模出 **is-a** 关系

&emsp;条款33：避免遮掩继承而来的名称

&emsp;条款34：区分接口继承和实现继承

&emsp;条款35：考虑 virtual 函数以外的其他选择

&emsp;条款36：绝不重新定义继承而来的 non-virtual 函数

&emsp;条款37：绝不定义继承而来的缺省参数值

&emsp;条款38：通过复合塑模出 **has-a** 或 “根据某物实现出”

&emsp;条款39：明智而审慎地使用 private 继承

&emsp;条款40：明智而审慎地使用多重继承

链接: [Effective C++ 第六章 继承与面向对象设计](https://blog.csdn.net/weixin_45867382/article/details/116494432)
## 7、模板与泛型编程 <br> &emsp;&emsp;Templates and Generic Programming
&emsp;条款41：了解隐式接口和编译期多态

&emsp;条款42：了解 typename 的双重意义

&emsp;条款43：学习处理模板化基类内的名称

&emsp;条款44：将与参数无关的代码抽离 templates

&emsp;条款45：运用成员函数模板接受所有兼容类型

&emsp;条款46：需要类型转换时请为模板定义非成员函数

&emsp;条款47：请使用 traits classes 表现类型信息

&emsp;条款48：认识 template 元编程

链接: [Effective C++ 第七章 模板与泛型编程](https://blog.csdn.net/weixin_45867382/article/details/116494484)

## 8、定制new和delete <br> &emsp;&emsp;Customizing new and delete
&emsp;条款49：了解 new-handler 的行为

&emsp;条款50：了解 new 和 delete 的合理替换时机

&emsp;条款51：编写 new 和 delete 时需固守常规

&emsp;条款52：写了 *placement* new 也要写 *placement* delete

链接: [Effective C++ 第八章 定制new和delete](https://blog.csdn.net/weixin_45867382/article/details/116494515)
## 9、杂项讨论 <br> &emsp;&emsp;Miscellany
&emsp;条款53：不要轻忽编译器的警告

&emsp;条款54：让自己熟悉包括 TRI 在内的标准程序库

&emsp;条款55：让自己熟悉 Boost

链接: [Effective C++ 第九章 杂项讨论](https://blog.csdn.net/weixin_45867382/article/details/116494564)
