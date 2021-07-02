# GDB与Makefile

## GDB调式

### 基础指令：

`-g`：使用该参数编译可以执行文件，得到调试表。

`gdb ./a.out`
	
`list`： list 1  列出源码。根据源码指定 行号设置断点。

`b`：	b 20	在20行位置设置断点。

`run/r`:	运行程序

`n/next`: 下一条指令（会越过函数）

`s/step`: 下一条指令（会进入函数）

`p/print`：p i  查看变量的值。
	
`continue`：继续执行断点后续指令。

`finish`：结束当前函数调用。 

`quit`：退出gdb当前调试。

`Enter`：重复上调指令

### 其他指令：

`run`：使用run查找段错误出现位置。

`set args`： 设置main函数命令行参数 （在 start、run 之前）

`run 字串1 字串2 ...`: 设置main函数命令行参数

`info b`: 查看断点信息表

`b 20 if i = 5`：	设置条件断点。

`ptype`：查看变量类型。

`bt`：列出当前程序正存活着的栈帧。

`frame`： 根据栈帧编号，切换栈帧。

`display`：设置跟踪变量

`undisplay`：取消设置跟踪变量。 使用跟踪变量的编号。

### 用gdb 分析coredump 文件

#### 生成 coredump 文件

`coredump` 文件系统默认不会生成，可以使用命令 `ulimit -a` 查看所有：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625211421806.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

从图片中发现第一行 `core file size` 对应的大小为 0，即默认不生成`coredump` 文件，使用命令 `ulimit -c unlimited` ，让其生成该文件。

#### 产生 coredump 文件的原因

- **内存访问越界**，可能的具体原因是： 
  - 由于使用错误的下标，导致数组访问越界；
  - 搜索字符串时，依靠字符串结束符来判断字符串是否结束，但是字符串没有正常的使用结束符；
  - 使用strcpy, strcat, sprintf, strcmp，由casecmp 等字符串操作函数时，容易出现将目标字符串读／写越界的情况。应该使用strncpy, strlcpy, stmcat, strlcat, snpfintf, stmcmp,stmcasecmp 等函数防止读容易出现写越界。
- **多线程程序，使用了线程不安全的函数**。
- 多线程读写的数据未加锁保护。对于会被多个线程同时访问的全局数据，应该注意加锁保护，否则很容易造成coredump 。
- **非法指针**，包括使用空指针或随意使用指针转换。
- **堆栈溢出**。

#### gdb 定位cored ump 文件

首先编写 `test.cpp `文件，内容如下：

```cpp
#include <iostream>

int main()
{
    int b = 1;
    int* a;
    *a = b;
     return 0;
}  
```

使用g++进行编译：

```shell
g++ test.cpp -o test -g
```

编译完成后运行可执行文件` test` ，出现错误：==段错误 (核心已转储)==，利用 `ls` 查看当前文件夹，发现生成了 `core `文件：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625213216120.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

使用 gdb 进行调式，输入以下命令：

```bash 
gdb test core	# gdb 可执行文件 core
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625214733138.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

程序直接跳转至错误处，打印  `b` 和 `a `的值，发现 `a` 的值出错，应该改为 `*a = &b;`。

上述过程就是利用 coredump 进行调式。

若发现 “==段错误 (核心已转储)==”这个错误，可以直接使用命令：`gdb test`进入`gdb`调试，然后按`r`键直接跳转至错误处。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625214447978.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

## Makefile编写

makefile： 管理项目。

  命名：makefile   Makefile --- make 命令

###   1 个规则：

​    **目标：依赖条件**

​    **（一个tab缩进）命令**

​    1. 目标的时间必须晚于依赖条件的时间，否则，更新目标

​    2. 依赖条件如果不存在，找寻新的规则去产生依赖条件。

  **ALL：指定 makefile 的终极目标。**

###   2 个函数：

​    `src = $(wildcard ./*.cpp): `匹配当前工作目录下的所有.cpp 文件。将文件名组成列表，赋值给变量 src。 src = add.cpp sub.cpp div1.cpp 

​    `obj = \$(patsubst %.cpp, %.o, $(src)): `将参数3中，包含参数1的部分，替换为参数2。 obj = add.o sub.o div1.o

  **clean: (没有依赖)**

​    `-rm -rf $(obj) a.out` “-”：作用是，删除不存在文件时，不报错。顺序执行结束。

###   3 个自动变量：

​    `$@: `在规则的命令中，表示规则中的**目标**。 

​    `$^: `在规则的命令中，表示所有依赖条件。

​    `$<: `在规则的命令中，表示**第一个依赖条件**。如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则。

  **模式规则：**

​    %.o:%.c

​      gcc -c $< -o %@

  **静态模式规则：**

​    $(obj):%.o:%.c

​      gcc -c $< -o %@  

  **伪目标：**

​    `.PHONY: clean ALL`

  参数：

​    -n：模拟执行make、make clean 命令。

​    -f：指定文件执行 make 命令。       xxxx.mk

### 示例：

#### **源文件与头文件在同一目录下**

该文件夹下各个文件如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625202346673.png)

`makefile`内容如下：

```makefile
src = $(wildcard *.cpp)		# 获取文件夹下后缀名为 .cpp 的文件，存储到变量 src 中

obj = $(patsubst %.cpp, %.o, $(src)) # 在变量 src 中寻找后缀名为.cpp的文件，将其后缀名替换为.o存储到变量 obj 中
									# $ 运算符：用于解变量

ALL:a.out				# 声明最终生成文件


$(obj):%.o:%.cpp		# 目标：所有的 .o 文件，包含在变量 obj 中 依赖：所有的 .cpp 文件，包含在变量 obj 中
	g++ -c $< -o $@		# $< 逐个获取依赖，并生成 $@ 目标文件 .o


a.out:$(obj)			# 目标： a.out 依赖：所有的 .o 文件，包含在变量 obj 中，$ 解变量
	g++ $^ -o $@		# $^ 包含上面所有的依赖 $@ 目标文件


clean:
	-rm -rf $(obj) a.out	# 执行 make clean 时将清除所有的 .o 文件和 a.out 文件


PHONY: clean ALL		# 伪声明
```

在命令行执行 `make` 命令：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625203610279.png)

`ls `查看当前文件夹内文件：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625203635736.png)

运行可执行文件：

<img src="https://img-blog.csdnimg.cn/20210625203710421.png" alt="在这里插入图片描述" style="zoom:150%;" />

删除` .o `文件与可执行文件：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625203738376.png)

#### **源文件与头文件不在同一目录下**

源文件在 `src`下， 头文件在 `inc` 下， `obj` 用来存放生成的 `.o `文件，目前文件为空，`makefile`在当前文件夹下

<img src="https://img-blog.csdnimg.cn/20210625205206854.png" alt="在这里插入图片描述" style="zoom:150%;" />

`makefile`内容如下：

```makefile
src=$(wildcard ./src/*.cpp)

obj=$(patsubst ./src/%.cpp, ./obj/%.o,$(src))

inc_path = ./inc		# 定义头文件路径

myArgs = -Wall -g		# 定义编译时的参数

ALL:a.out

$(obj): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)	# 编译时需要的参数在后面添加
 
a.out:$(obj)
	g++ $^ -o $@ $(myArgs)

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL
```

`make` 之后，运行可执行文件：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210625205604142.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)