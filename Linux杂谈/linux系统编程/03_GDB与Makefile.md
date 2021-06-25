# GDB与Makefile

## GDB调式

### 基础指令：

-g：使用该参数编译可以执行文件，得到调试表。

gdb ./a.out
	
list： list 1  列出源码。根据源码指定 行号设置断点。

b：	b 20	在20行位置设置断点。

run/r:	运行程序

n/next: 下一条指令（会越过函数）

s/step: 下一条指令（会进入函数）

p/print：p i  查看变量的值。
	
continue：继续执行断点后续指令。

finish：结束当前函数调用。 

quit：退出gdb当前调试。

### 其他指令：

run：使用run查找段错误出现位置。

set args： 设置main函数命令行参数 （在 start、run 之前）

run 字串1 字串2 ...: 设置main函数命令行参数

info b: 查看断点信息表

b 20 if i = 5：	设置条件断点。

ptype：查看变量类型。

bt：列出当前程序正存活着的栈帧。

frame： 根据栈帧编号，切换栈帧。

display：设置跟踪变量

undisplay：取消设置跟踪变量。 使用跟踪变量的编号。

## Makefile编写

makefile： 管理项目。

  命名：makefile   Makefile --- make 命令

  1 个规则：

​    目标：依赖条件

​    （一个tab缩进）命令

​    \1. 目标的时间必须晚于依赖条件的时间，否则，更新目标

​    \2. 依赖条件如果不存在，找寻新的规则去产生依赖条件。

  ALL：指定 makefile 的终极目标。

  2 个函数：

​    src = $(wildcard ./*.c): 匹配当前工作目录下的所有.c 文件。将文件名组成列表，赋值给变量 src。 src = add.c sub.c div1.c 

​    obj = $(patsubst %.c, %.o, $(src)): 将参数3中，包含参数1的部分，替换为参数2。 obj = add.o sub.o div1.o

  clean: (没有依赖)

​    -rm -rf $(obj) a.out “-”：作用是，删除不存在文件时，不报错。顺序执行结束。

  3 个自动变量：

​    $@: 在规则的命令中，表示规则中的目标。 

​    $^: 在规则的命令中，表示所有依赖条件。

​    $<: 在规则的命令中，表示第一个依赖条件。如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则。

  模式规则：

​    %.o:%.c

​      gcc -c $< -o %@

  静态模式规则：

​    $(obj):%.o:%.c

​      gcc -c $< -o %@  

  伪目标：

​    .PHONY: clean ALL

  参数：

​    -n：模拟执行make、make clean 命令。

​    -f：指定文件执行 make 命令。       xxxx.mk