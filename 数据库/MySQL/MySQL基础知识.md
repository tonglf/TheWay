# MySQL day01

## 1、sql、DB、DBMS分别是什么，他们之间的关系？

​    **DB:** 

​       DataBase（**数据库**，数据库实际上在硬盘上以文件的形式存在）

​    **DBMS:** 

​       DataBase Management System（**数据库管理系统**，常见的有：MySQL Oracle DB2 Sybase SqlServer...）

​    **SQL:** 

​       **结构化查询语言**，是一门标准通用的语言。标准的 sql 适合于所有的数据库产品。

​       SQL属于高级语言。只要能看懂英语单词的，写出来的 sql 语句，可以读懂什么意思。

​       SQL语句在执行的时候，实际上内部也会先进行编译，然后再执行 sql。（ sql 语句的编译由 DBMS 完成。）

**总结：**

​    DBMS负责执行 sql 语句，通过执行 sql 语句来操作 DB 当中的数据。

​    DBMS -(执行)-> SQL -(操作)-> DB

## 2、什么是表？

​    **表：table**

​    表：table是数据库的基本组成单元，所有的数据都以表格的形式组织，目的是可读性强。

​    一个表包括行和列：

​       **行**：被称为**数据**/记录(data)

​       **列**：被称为**字段**(column)

| 学号(int) | 姓名(varchar) | 年龄(int) |
| :-------: | :-----------: | :-------: |
|    110    |     张三      |    20     |
|    120    |     李四      |    21     |

​    **每一个字段应该包括哪些属性？**

​       字段名、数据类型、相关的约束、字段长度。

## 3、学习MySQL主要还是学习通用的SQL语句，那么SQL语句包括增删改查，SQL语句怎么分类呢？

​    **DQL** **（数据查询语言）**:  **查询语句，凡是 select 语句都是DQL **。

​    **DML** **（数据操作语言）：**insert delete update，对表当中的**数据进行增删改**。

​    **DDL** **（数据定义语言）：**create drop alter，对表结构的增删改。

​    **TCL** **（事务控制语言）：**commit 提交事务，rollback回滚事务。(TCL中的T是Transaction)

​    **DCL （数据控制语言）:** grant授权、revoke撤销权限等。

## 4、导入数据（后期大家练习的时候使用这个演示的数据）

​    **第一步：登录mysql数据库管理系统**

​       dos命令窗口： mysql -uroot -p333

​    **第二步：查看有哪些数据库**

```mysql
show databases; 		# (不是SQL语句，属于MySQL的命令。)
```

​    **第三步：创建属于我们自己的数据库**

```mysql
create database bjpowernode; 	# (不是SQL语句，属于MySQL的命令。)
```

​    **第四步：使用bjpowernode数据**

```mysql
use bjpowernode; 			# (这个不是SQL语句，属于MySQL的命令。)
```

​    **第五步：查看当前使用的数据库中有哪些表？**

```mysql
show tables; 			# (不是SQL语句，属于MySQL的命令。)
```

​		刚刚创建的数据库中没有数据，表为空。

​    **第六步：初始化数据（数据导入，****source** **文件路径）**

```mysql
mysql> source D:\course\05-MySQL\resources\bjpowernode.sql
```

​    **第七步：查看导入数据后的数据库中有哪些表？**

```mysql
show tables; 		# (不是SQL语句，属于MySQL的命令。)
```

​		数据初始化完成之后，数据库有三张表：dept、emp、salgrade

## 5、bjpowernode.sql，这个文件以sql结尾，这样的文件被称为“sql脚本”。什么是sql脚本呢？

​    当一个文件的扩展名是 .sql，并且该文件中编写了大量的 sql 语句，我们称这样的文件为 sql 脚本。

​    注意：直接使用 source 命令可以执行sql脚本。

​    sql 脚本中的数据量太大的时候，无法打开，请使用 source 命令完成初始化。

## 6、删除数据库：

```mysql
drop database bjpowernode;
```

## 7、查看表结构：

```mysql
mysql> desc dept;
mysql> desc emp;
mysql> desc salgrade;
```

**表名称：dept**

描述：部门信息表

| 英文字段名称 | 中文描述 | 类型        |
| ------------ | -------- | ----------- |
| DEPTNO       | 部门编号 | INT(2)      |
| DNAME        | 部门名称 | VARCHAR(14) |
| LOC          | 位置     | VARCHAR(13) |

**表名称：emp**

描述：员工信息表

| 英文字段名称 | 中文描述 | 类型        |
| ------------ | -------- | ----------- |
| EMPNO        | 员工编号 | INT (4)     |
| ENAME        | 员工姓名 | VARCHAR(10) |
| JOB          | 工作岗位 | VARCHAR(9)  |
| MGR          | 上级领导 | INT (4)     |
| HIREDATE     | 入职日期 | DATE        |
| SAL          | 薪水     | DOUBLE(7,2) |
| COMM         | 津贴     | DOUBLE(7,2) |
| DEPTNO       | 部门编号 | INT(2)      |

注：DEPTNO 字段是外键，DEPTNO 的值来源于 dept 表的主键，起到了约束的作用

**表名称：salgrade**

描述：薪水等级信息表

| 英文字段名称 | 中文描述 | 类型 |
| ------------ | -------- | ---- |
| GRADE        | 等级     | INT  |
| LOSAL        | 最低薪水 | INT  |
| HISAL        | 最高薪水 | INT  |

## 8、查看表中的数据

```mysql
mysql> select * from emp;
mysql> select * from dept;
mysql> select * from salgrade;
```

## 9、常用命令

```mysql
mysql> select database(); 	# 查看当前使用的是哪个数据库

mysql> select version(); 	# 查看mysql的版本号。

\c   						# 命令，结束一条语句。

exit 						# 命令，退出mysql。
```

**创建数据库：**

```mysql
create database 数据库名称; 	# 创建数据库

use 数据库名称;				# 使用数据库，在数据库中建立表，因此创建表的时候必须要先选择数据库。
```

**查看其他库中的表：**

```mysql
show tables from <database name>;
```

## 10、查看创建表的语句：

```mysql
show create table emp;
```

## 11、简单的查询语句（DQL）

​    **语法格式：**

```mysql
select 字段名1,字段名2,字段名3,.... from 表名;
```

​    **提示：**

​       1、**任何一条 sql 语句以“;”结尾**

​       2、**sql 语句不区分大小写**

​    **查询员工的年薪？**（字段可以参与数学运算。）

```mysql
select ename,sal * 12 from emp;
```

​    **给查询结果的列重命名？**

```mysql
select ename,sal * 12 as yearsal from emp;
```

​    **别名中有中文？**

```mysql
select ename,sal * 12 as 年薪 from emp; 		# 错误
select ename,sal * 12 as '年薪' from emp;
```

​    **注意**：标准 sql 语句中要求字符串使用**单引号**括起来。虽然 mysql 支持双引号，尽量别用。

​    **as 关键字可以省略？**

```mysql
mysql> select empno, ename, sal * 12 yearsal from emp; 
```

​    **查询所有字段？**

```mysql
select * from emp; 		# 实际开发中不建议使用 *，效率较低。   
```

## 12、条件查询。

​    **语法格式：**

```mysql
select 字段,字段... from 表名 where 条件;
```

​    **执行顺序：先 from ，然后 where ，最后 select**

where支持如下运算符

| 运算符            | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| =                 | 等于                                                         |
| <>或!=            | 不等于                                                       |
| <                 | 小于                                                         |
| <=                | 小于等于                                                     |
| >                 | 大于                                                         |
| >=                | 大于等于                                                     |
| between …  and …. | 两个值之间，**等同于** **>= and <=**                         |
| is null           | 为 null（ is not  null 不为空）                              |
| **and**           | 并且                                                         |
| **or**            | 或者                                                         |
| in                | 包含，相当于多个 or（ not in 不在这个范围中）                |
| not               | not 可以取非，主要用在 is 或 in 中                           |
| like              | like 称为模糊查询，支持 %或下划线匹配：**% 匹配任意个字符，下划线_，一个下划线只匹配一个字符** |

​    **查询工资等于 5000 的员工姓名？**

```mysql
select ename from emp where sal = 5000;
```

​    **查询 SMITH 的工资？**

```mysql
select sal from emp where ename = 'SMITH'; 	# 字符串使用单引号括起来，字符串不区分大小写。
```

​    **找出工资高于 3000 的员工？**

```mysql
select ename,sal from emp where sal > 3000;

select ename,sal from emp where sal >= 3000;

select ename,sal from emp where sal < 3000;

select ename,sal from emp where sal <= 3000;
```

​    **找出工资不等于 3000 的？**

```mysql
select ename,sal from emp where sal <> 3000;
select ename,sal from emp where sal != 3000;
```

​    **找出工资在1100和3000之间的员工，包括1100和3000？**

```mysql
select ename,sal from emp where sal >= 1100 and sal <= 3000;

select ename,sal from emp where sal between 1100 and 3000; # between...and...是闭区间 [1100，3000]

select ename,sal from emp where sal between 3000 and 1100; # 查询不到任何数据
```

​		**between and在使用的时候必须左小右大。**

​		between and 除了可以使用在数字方面之外，还可以使用在字符串方面。**字符串跟数字不一样，前闭后开**

```mysql
select ename from emp where ename between 'A' and 'C';	# 查询以第一个字母开头的字符串
select ename from emp where ename between 'A' and 'D';  # 左闭右开
```

​       **找出哪些人津贴为 NULL ？**

​           在数据库当中NULL不是一个值，代表什么也没有，为空。

​           **空不是一个值，不能用等号衡量，必须使用 is null 或者 is not null**

```mysql
select ename,sal,comm from emp where comm is null;

select ename,sal,comm from emp where comm = null;	# 查询为空，错误
```

​       **找出哪些人津贴不为 NULL ？**

```mysql
select ename,sal,comm from emp where comm is not null;
```

​       **找出哪些人没有津贴？**

```mysql
select ename,sal,comm from emp where comm is null or comm = 0;
```

​       **找出工作岗位是 MANAGER 和 SALESMAN 的员工？**

  ```mysql
  select ename,job from emp where job = 'MANAGER' or job = 'SALESMAN';
  ```

​       **and 和 or 联合起来用：找出薪资大于 1000 的并且部门编号是 20 或 30 部门的员工。**

```mysql
select ename,sal,deptno from emp where sal > 1000 and deptno = 20 or deptno = 30;   # 错误的

select ename,sal,deptno from emp where sal > 1000 and (deptno = 20 or deptno = 30); # 正确的。
```

​           注意：当运算符的优先级不确定的时候加小括号。

​       **in 等同于 or ：找出工作岗位是 MANAGER 和 SALESMAN 的员工？**

```mysql
select ename,job from emp where job = 'SALESMAN' or job = 'MANAGER';

select ename,job from emp where job in('SALESMAN', 'MANAGER');

select ename,job from emp where sal in(800, 5000); 		# in后面的值不是区间，是具体的值。
```

​       **not in:** **不在这几个值当中。**

```mysql
select ename,job from emp where sal not in(800, 5000);       
```

​       **模糊查询 like ?** 

​           **找出名字当中含有 O 的？**

​              （在模糊查询当中，必须掌握两个特殊的符号，一个是%，一个是\_） ==%代表任意多个字符，_代表任意1个字符==

```mysql
select ename from emp where ename like '%O%';
```

​           **找出名字中第二个字母是A的？**

```mysql
select ename from emp where ename like '_A%';
```

​           **找出名字中有下划线的？**

```mysql
select ename from t_user where name like '%_%';   # 错误
select ename from t_user where name like '%\_%';  # 正确
```

​           **找出名字中最后一个字母是T的？**

```mysql
select ename from emp where ename like '%T';
```

**注意**：

MySQL 在 windows 下是不区分大小写的，将 script 文件导入 MySQL 后表名也会自动转化为小写，结果再想要将数据库导出放到 linux 服务器中使用时就出错了。因为**在 linux 下表名区分大小写**而找不到表，查了很多都是说在 linux 下更改 MySQL 的设置使其也不区分大小写，但是有没有办法反过来让 windows 下大小写敏感呢。其实方法是一样的，相应的更改 windows 中 MySQL 的设置就行了。

具体操作：

​    在MySQL的配置文件my.ini中增加一行：

​    lower_case_table_names = 0

​    其中 0：区分大小写，1：不区分大小写

MySQL在 Linux 下数据库名、表名、列名、别名大小写规则是这样的：

　　  1、**数据库名与表名是严格区分大小写的；**

　　  2、表的别名是严格区分大小写的；

　　  3、列名与列的别名在所有的情况下均是忽略大小写的；

　　  4、变量名也是严格区分大小写的；其余 MySQL 在 Windows 下都不区分大小写

## 13、排序（升序、降序）

排序采用 **==order by==** 子句，order by 后面跟上排序字段，排序字段可以放多个，多个采用逗号间隔，**order by 默认采用升序**，如果存在where 子句那么 order by 必须放到 where 语句的后面。

**按照工资升序，找出员工名和薪资？**

```mysql
select ename, sal from emp order by sal;
```

注意：**默认是升序**。怎么指定升序或者降序呢？asc 表示升序，desc 表示降序。

```mysql
select ename, sal from emp order by sal; 		# 升序
select ename, sal from emp order by sal asc; 	# 升序
select ename, sal from emp order by sal desc; 	# 降序。
```

**按照工资的降序排列，当工资相同的时候再按照名字的升序排列。**

```mysql
select ename,sal from emp order by sal desc;
select ename,sal from emp order by sal desc, ename asc;
```

​    注意：越靠前的字段越能起到主导作用。只有当前面的字段无法完成排序的时候，才会启用后面的字段。

**找出工作岗位是 SALESMAN 的员工，并且要求按照薪资的降序排列。**

```mysql
select ename,job,sal from emp where job = 'SALESMAN' order by sal desc;
```

| 查询语句     | select 字段 | from表名 | where条件 | order by .... |
| ------------ | :---------: | :------: | :-------: | :-----------: |
| **执行顺序** |      3      |    1     |     2     |       4       |

​    ==order by是最后执行的==。

**使用字段位置进行排序：（order by 第几列，从 1 开始）**

```mysql
select * from emp order by 6;
```

​	不建议使用此种方式，采用数字含义不明确，程序不健壮。

## 14、分组函数？

​    **count 计数     sum 求和      avg 平均值     max 最大值      min 最小值**

​    记住：所有的分组函数都是对 “**某一组**” 数据进行操作的。

​    **找出工资总和？**

```mysql
select sum(sal) from emp;
```

​    **找出最高工资？**

```mysql
select max(sal) from emp;
```

​    **找出最低工资？**

```mysql
select min(sal) from emp;
```

​    **找出平均工资？**

```mysql
select avg(sal) from emp;
```

​    **找出总人数？**

```mysql
select count(*) from emp;
select count(ename) from emp;
```

​    分组函数一共5个。分组函数还有另一个名字：**多行处理函数**。多行处理函数的特点：==输入多行，最终输出的结果是 1 行==。

​    **分组函数自动忽略 NULL 。**

```mysql
select count(comm) from emp;
select sum(comm) from emp;
select sum(comm) from emp where comm is not null; # 不需要额外 where 条件排除空值。sum 函数自动忽略 NULL
```

​	 **找出工资高于平均工资的员工？**

```mysql
select avg(sal) from emp; # 平均工资
select ename,sal from emp where sal > avg(sal); # ERROR 1111 (HY000): Invalid use of group function
```

​           思考以上的错误信息：无效的使用了分组函数？

​              原因：SQL 语句当中有一个语法规则，**分组函数不可直接使用在 where 子句当中 **。 why  ???

​    怎么解释？

​       因为分组函数是在 group by 执行之后才会执行的，而 **group by 是在 where 执行之后才会执行的。**

​    **count(*) 和 count ( 具体的某个字段 )，他们有什么区别？**

​       ==count(*):不是统计某个字段中数据的个数，而是统计总记录条数。（和某个字段无关）==

​       count(comm): 表示统计 comm 字段中不为 NULL 的数据总数量。

​    **分组函数也能组合起来用：**

```mysql
select count(*),sum(sal),avg(sal),max(sal),min(sal) from emp;
```

​       +----------+----------+-------------+----------+----------+

​       | count(*) | sum(sal) | avg(sal) | max(sal) | min(sal) |

​       +----------+----------+-------------+----------+----------+

​       |   14 | 29025.00|2073.214286| 5000.00| 800.00 |

​       +----------+----------+-------------+----------+----------+

​    **找出工资高于平均工资的员工？**

​       第一步：找出平均工资

```mysql
select avg(sal) from emp;
```

​       第二步：找出高于平均工资的员工

```mysql
select ename,sal from emp where sal > 2073.214286;
```

​		合并：

```mysql
select ename,sal from emp where sal > (select avg(sal) from emp);
```

## 15、单行处理函数

​    **什么是单行处理函数？**

​       ==输入一行，输出一行==。

​    **计算每个员工的年薪？**

```mysql
select ename,(sal+comm)*12 as yearsal from emp;     
```

​       **重点：所有数据库都是这样规定的，只要有 NULL 参与的运算结果一定是 NULL 。**

​       **使用 ifnull 函数：**

```mysql
select ename,(sal + ifnull(comm, 0)) * 12 as yearsal from emp;
```

​    **ifnull()** **空处理函数？**

​       ifnull(可能为NULL的数据,被当做什么处理) ： 属于单行处理函数。

```mysql
select ename, ifnull(comm, 0) as comm from emp;   
```

## 16、group by 和 having

​    ==group by ： 按照某个字段或者某些字段进行**分组**。==

​    ==having : having是对分组之后的数据进行再次**过滤**。==

​    **案例：找出每个工作岗位的最高薪资。**

```mysql
select max(sal), job from emp group by job;   
```

​    注意：**分组函数一般都会和 group by 联合使用**，这也是为什么它被称为分组函数的原因。并且任何一个分组函数（count sum avg max min）都是在 group by 语句执行结束之后才会执行的。当一条 sql 语句没有 group by 的话，整张表的数据会自成一组。

```mysql
select ename,max(sal),job from emp group by job;
```

​    以上在 mysql 、Oracle 数据库当中会报错：语法错误。

​    记住一个规则：**当一条语句中有 group by 的话， select 后面只能跟 分组函数 和 参与分组 的字段。**

​    **每个工作岗位的平均薪资？**

```mysql
select job, avg(sal) from emp group by job;
```

**多个字段能不能联合起来一块分组？**

​    **案例：找出每个部门不同工作岗位的最高薪资。**

```mysql
select deptno,job,max(sal) from emp group by deptno,job;
```

​           ==分组顺序：先按 deptno 分组，再在 deptno 组内按 job 分组。==

​    **找出每个部门的最高薪资，要求显示薪资大于 2900 的数据。**

​       第一步：找出每个部门的最高薪资

```mysql
select max(sal),deptno from emp group by deptno;
```

​       第二步：找出薪资大于2900

```mysql
select max(sal),deptno from emp group by deptno having max(sal) > 2900;  #  这种方式效率低。

# 效率较高，建议能够使用where过滤的尽量使用where。
select max(sal),deptno from emp where sal > 2900 group by deptno; 
```

​    **找出每个部门的平均薪资，要求显示薪资大于 2000 的数据。**

​        第一步：找出每个部门的平均薪资

```mysql
select deptno,avg(sal) from emp group by deptno;
```

​        第二步：要求显示薪资大于2000的数据

```mysql
select deptno,avg(sal) from emp group by deptno having avg(sal) > 2000;   
```

​    where后面不能使用分组函数：

```mysql
select deptno,avg(sal) from emp where avg(sal) > 2000 group by deptno; 
# 错误了。这种情况只能使用 having 过滤。
```

## 17、总结一个完整的DQL语句怎么写？

| DQL语句  | select | from | where | group by | having | order by |
| -------- | ------ | ---- | ----- | -------- | ------ | -------- |
| 执行顺序 | 5      | 1    | 2     | 3        | 4      | 6        |

# MySQL day02

## 1、关于查询结果集的去重？

```mysql
mysql> select distinct job from emp;    # distinct关键字去除重复记录。

mysql> select ename, distinct job from emp;	# 错误
```

记住：**distinct 只能出现在所有字段的最前面，表示所有字段组合起来去重。**

```mysql
mysql> select distinct deptno, job from emp;    # deptno, job组合后去重
```

**案例：统计岗位的数量？**

```mysql
select count(distinct job) from emp;
```

## 2、连接查询

### 2.1、什么是连接查询？

​    **连接查询：也可以叫跨表查询，需要关联多个表进行查询**

### 2.2、连接查询的分类？

​    根据**语法出现的年代**来划分的话，包括：

​       SQL92（一些老的 DBA 可能还在使用这种语法。DBA：DataBase Administrator，数据库管理员）

​       SQL99（比较新的语法）

​    根据**表的连接方式**来划分，包括：

​       **内连接：**

​           等值连接（判断条件相等）

​           非等值连接（判断条件不相等）

​           自连接（自身连接）

​       **外连接：**

​           左外连接（左连接）

​           右外连接（右连接）

​       	全连接（这个不讲，很少用！）

### 2.3、在表的连接查询方面有一种现象被称为：笛卡尔积现象。（笛卡尔乘积现象）

**案例：找出每一个员工的部门名称，要求显示员工名和部门名。**

```mysql
select ename,dname from emp,dept;	# 查询结果有56条记录
```

**笛卡尔积现象**：当两张表进行连接查询的时候，没有任何条件进行限制，最终的查询结果条数是**两张表记录条数的乘积**。

**关于表的别名**：

```mysql
select e.ename,d.dname from emp e,dept d;
# select后的字段不加表名限制则会从 from 后的所有表（emp、dept）中查找含有该字段的数据，加上表名限制则只会在该表内查询
```

​    表的别名有什么好处？

​       第一：执行效率高。

​       第二：可读性好。

### 2.4、怎么避免笛卡尔积现象？当然是加条件进行过滤。

思考：避免了笛卡尔积现象，会减少记录的匹配次数吗？

​    ==不会，次数还是56次。只不过显示的是有效记录。==

**案例：找出每一个员工的部门名称，要求显示员工名和部门名。**

```mysql
# SQL92，以后不用。
select e.ename, d.dname from emp e, dept d where e.deptno = d.deptno; 
```

### 2.5、内连接之等值连接：最大特点是：条件是等量关系。

**案例：查询每个员工的部门名称，要求显示员工名和部门名。**

```mysql
select e.ename, d.dname from emp e, dept d where e.deptno = d.deptno;	# SQL92:（太老，不用了）    
select e.ename,d.dname from emp e join dept d on e.deptno = d.deptno;	# SQL99：（常用的）
```

语法：

```mysql
... A inner join B on 连接条件 where ...   # inner可以省略的，带着 inner 目的是可读性好一些。
```

​    ==SQL99 语法结构更清晰一些：表的连接条件和后来的 where 条件分离了。==

### 2.6、内连接之非等值连接：最大的特点是：连接条件中的关系是非等量关系。

**案例：找出每个员工的工资等级，要求显示员工名、工资、工资等级。**

```mysql
select 
	e.ename,e.sal,s.grade
from
	emp e
inner join                 # inner可以省略
	salgrade s
on
	e.sal 
between s.losal and s.hisal;
```

### 2.7、自连接：最大的特点是：一张表看做两张表。自己连接自己。

**案例：找出每个员工的上级领导，要求显示员工名和对应的领导名。**

​	员工的领导编号 = 领导的员工编号

```mysql
select 
	a.ename as '员工名',b.ename as '领导名'
from
	emp a
inner join
	emp b
on
	a.mgr = b.empno;
```

### 2.8、外连接？

什么是外连接，和内连接有什么区别？

​    **内连接：**

​       假设A和B表进行连接，使用内连接的话，凡是 A 表和 B 表能够匹配上的记录查询出来，这就是内连接。AB 两张表没有主副之分，两张表是平等的。

​    **外连接：**

​       **==假设 A 和 B 表进行连接，使用外连接的话，AB 两张表中有一张表是主表，一张表是副表，主要查询主表中的数据，捎带着查询副表，当副表中的数据没有和主表中的数据匹配上，副表自动模拟出 NULL 与之匹配。==**

​    **外连接的分类？**

​       ==左外连接（左连接）==：表示左边的这张表是主表。

​       ==右外连接（右连接）==：表示右边的这张表是主表。

​    左连接有右连接的写法，右连接也会有对应的左连接的写法。

**案例：找出每个员工的上级领导？（所有员工必须全部查询出来。）**

```mysql
# 内连接
select a.ename '员工', b.ename '领导' from emp a inner join emp b on a.mgr = b.empno;

# 外连接：（左外连接）   outer是可以省略的
select a.ename '员工', b.ename '领导' from emp a left outer join emp b on a.mgr = b.empno;

# 外连接：（右外连接）   outer是可以省略的
select a.ename '员工', b.ename '领导' from emp b right outer join emp a on a.mgr = b.empno;
```

​	外连接最重要的特点是：**主表的数据无条件的全部查询出来**。

**案例：找出哪个部门没有员工？**

```mysql
select d.* from emp e right join dept d on e.deptno = d.deptno where e.empno is null;
```

### 2.9、三张表怎么连接查询？

**案例：找出每一个员工的部门名称以及工资等级。**

注意，解释一下：

```mysql
.... A join B join C on ...  # 表示：A表和B表先进行表连接，连接之后A表（连接之后的结果）继续和C表进行连接。

select e.ename,d.dname,s.grade from emp e 
	join dept d on e.deptno = d.deptno 
	join salgrade s on e.sal 
	between s.losal and s.hisal;
```

**案例：找出每一个员工的部门名称、工资等级、以及上级领导。**

```mysql
select  e.ename '员工',d.dname,s.grade,e1.ename '领导' from emp e 
	join dept d on e.deptno = d.deptno 
	join salgrade s on e.sal 
	between s.losal and s.hisal
    left join emp e1 on e.mgr = e1.empno;
```

## 3、子查询

### 3.1、什么是子查询？子查询都可以出现在哪里？

​    **select 语句当中嵌套 select 语句，被嵌套的 select 语句是子查询。**

​    子查询可以出现在哪里？

```mysql
select ...(select) from ...(select) where ...(select);
```

### 3.2、where子句中使用子查询

**案例：找出高于平均薪资的员工信息。**

```mysql
select * from emp where sal > avg(sal);  # 错误的写法，where 后面不能直接使用分组函数。
```

正确写法：

```mysql
# 第一步：找出平均薪资
select avg(sal) from emp;

# 第二步：where过滤
select * from emp where sal > 2073.214286;

# 第一步和第二步合并：
select * from emp where sal > (select avg(sal) from emp);   
```

### 3.3、from后面嵌套子查询

**案例：找出每个部门平均薪水的等级。**

```mysql
# 第一步：找出每个部门平均薪水（按照部门编号分组，求 sal 的平均值）
select deptno,avg(sal) as avgsal from emp group by deptno;

# 第二步：将以上的查询结果当做临时表 t，让t表和 salgrade s 表连接，条件是：t.avgsal between s.losal and s.hisal

select t.*,s.grade from
	(select deptno,avg(sal) as avgsal from emp group by deptno) t
join salgrade s on t.avgsal between s.losal and s.hisal;
```

**案例：找出每个部门平均的薪水等级。**

```mysql
# 第一步：找出每个员工的薪水等级。
select e.ename,e.sal,e.deptno,s.grade from emp e join salgrade s on e.sal between s.losal and s.hisal;

# 第二步：基于以上结果，继续按照 deptno 分组，求 grade 平均值。
select e.deptno,avg(s.grade) from emp e 
	join salgrade s on e.sal between s.losal and s.hisal group by e.deptno;
```

### 3.4、在select后面嵌套子查询。

**案例：找出每个员工所在的部门名称，要求显示员工名和部门名。**

```mysql
select e.ename,d.dname from emp e join dept d on e.deptno = d.deptno;

select e.ename,(select d.dname from dept d where e.deptno = d.deptno) as dname from emp e;
```

## 4、union （可以将查询结果集相加）

**案例：找出工作岗位是 SALESMAN 和 MANAGER 的员工？**

```mysql
# 第一种：
select ename,job from emp where job = 'MANAGER' or job = 'SALESMAN';

# 第二种：
select ename,job from emp where job in('MANAGER','SALESMAN');

# 第三种：union
select ename,job from emp where job = 'MANAGER' 
	union 
select ename,job from emp where job = 'SALESMAN';
```

**两张不相干的表中的数据拼接在一起显示？**

```mysql
select ename from emp
	union
select dname from dept;
```

**注意：**

- union拼接后数据的字段名为第一个查询字段名，即上述查询后的数据字段名为 ename;

- **union拼接的数据字段数必须一致，即前后拼接数据的列一致**，否则无法拼接，例：

 ```mysql
 # 拼接的数据必须两两相对应。不能一张表是一个数据，另一张表是两个数据，这样无法拼接！
 select ename,sal from emp
 	union
 select dname from dept; 
 ```

## 5、limit (重点中的重点，以后分页查询全靠它了。)

### 5.1、limit 是 mysql 特有的，其他数据库中没有，不通用。（Oracle中有一个相同的机制，叫做 rownum ）

### 5.2、limit 取结果集中的部分数据，这是它的作用。

### 5.3、语法机制：

```mysql
limit startIndex, length
# startIndex 表示起始位置，从 0 开始，0 表示第一条数据。
# length 表示取几个
```

​    **案例：取出工资前 5 名的员工（思路：降序取前 5 个）**

```mysql
select ename,sal from emp order by sal desc;

# 取前5个：
select ename,sal from emp order by sal desc limit 0, 5;
select ename,sal from emp order by sal desc limit 5;	#（默认从0开始取）
```

### 5.4、limit是sql语句最后执行的一个环节：

| DQL语句  | select | from | where | group by | having | order by | limit |
| -------- | ------ | ---- | ----- | -------- | ------ | -------- | ----- |
| 执行顺序 | 5      | 1    | 2     | 3        | 4      | 6        | 7     |

### 5.5、案例：找出工资排名在第 4 到第 9 名的员工？

```mysql
select ename,sal from emp order by sal desc limit 3,6;
```

### 5.6、通用的标准分页 sql ？

每页显示3条记录：

第1页：0, 3

第2页：3, 3

第3页：6, 3

第4页：9, 3

第5页：12, 3

每页显示pageSize条记录：

**第pageNo页：(pageNo - 1) * pageSize, pageSize**

- pageSize是什么？是每页显示多少条记录

- pageNo是什么？显示第几页

java代码 {

​    int pageNo = 2; // 页码是2

​    int pageSize = 10; // 每页显示10条

​    limit (pageNo - 1) * pageSize, pageSize;

}

## 6、创建表：

​    建表语句的语法格式：

```mysql
create table 表名(
	字段名1 数据类型,
	字段名2 数据类型,
	字段名3 数据类型,
	....
);
```

​    关于MySQL当中字段的数据类型？以下只说常见的

​       **`int `**     整数型 (java 中的 int )

​       **`bigint`**  长整型 ( java 中的 long )

​       **`float`**    浮点型

​       **`char`**   定长字符串( string )

​       **`varchar`** 可变长字符串( StringBuffer / StringBuilder)

​       **`date`**    日期类型 （对应 Java 中的 java.sql.Date 类型）

​       **`BLOB`**  二进制大对象（存储图片、视频等流媒体信息） Binary Large OBject （对应java中的Object）

​       **`CLOB`**  字符大对象（存储较大文本，比如，可以存储4G的字符串。） Character Large OBject（对应java中的Object）

​       ......

​    **char和 varchar 怎么选择？**

​       **在实际的开发中，当某个字段中的数据长度不发生改变的时候，是定长的，例如：性别、生日等都是采用char。**

​       **当一个字段的数据长度不确定，例如：简介、姓名等都是采用varchar。**

​    BLOB和CLOB类型的使用？

​       电影表: t_movie

```mysql
create table t_movie(
	id(int),
    name(varchar),
    playtime(date),
    haibao(BLOB),
    history(CLOB)
);
```

​    **表名在数据库当中一般建议以：t_ 或者 tbl\_ 开始。**

​    创建学生表：

​       学生信息包括：学号、姓名、性别、班级编号、生日

​           学号：bigint           姓名：varchar           性别：char           班级编号：int           生日：char

```mysql
create table t_student(
	no bigint,
	name varchar(255),
	sex char(1),
	classno varchar(255),
	birth char(10)
);
```

## 7、insert语句插入数据

​    语法格式：

```mysql
insert into 表名(字段名1,字段名2,字段名3,....) values(值1,值2,值3,....)
```

​	插入：

```mysql
   drop table if exists t_student;     # 当这个表存在的话删除。
   
   create table t_student(
   	no bigint,
   	name varchar(255),
   	sex char(1) default 1,    # 默认填充1
   	classno varchar(255),
   	birth char(10)
   );
   
   insert into t_student(no,name,sex,classno,birth) values(1,'zhangsan','1','gaosan1ban', '1950-10-12');
   
   insert into t_student(name,sex,classno,birth,no) values('lisi','1','gaosan1ban', '1950-10-12',2);
   
   insert into t_student(name) values('wangwu'); # 除name字段之外，剩下的所有字段自动插入NULL。
   
   insert into t_student(no) values(3); 
   
   select * from t_student;
   
   insert into t_student(name) values('zhangsan');   
```

需要注意的地方：

​    当一条insert语句执行成功之后，表格当中必然会多一行记录。

​    即使多的这一行记录当中某些字段是NULL，后期也没有办法在执行

​    insert语句插入数据了，只能使用 update 进行更新。

```mysql
# 字段可以省略不写，但是后面的value对数量和顺序都有要求。
insert into t_student values(1,'jack','0','gaosan2ban','1986-10-23');

# 一次插入多行数据
insert into t_student (no,name,sex,classno,birth) values
	(3,'rose','1','gaosi2ban','1952-12-14'),(4,'laotie','1','gaosi2ban','1955-12-14');
```

## 8、表的复制

​    语法：

```mysql
# 将查询结果当做表创建出来。
create table 表名 as select 语句;    
```

## 9、将查询结果插入到一张表中？

```mysql
insert into dept1 select * from dept; # 将select后面的查询结果插入到dept1中
select * from dept1;
```

## 10、修改数据：update

语法格式：

```mysql
update 表名 set 字段名1 = 值1,字段名2 = 值2... where 条件;
```

​	注意：没有条件整张表数据全部更新。

**案例：将部门 10 的 LOC 修改为 SHANGHAI ，将部门名称修改为 RENSHIBU**

   ```mysql
   update dept1 set loc = 'SHANGHAI', dname = 'RENSHIBU' where deptno = 10;
   ```

**更新所有记录**

```mysql
update dept1 set loc = 'x', dname = 'y';
```

## 11、删除数据？

语法格式：

```mysql
 delete from 表名 where 条件;
```

​	注意：没有条件全部删除。

**删除 10 部门数据？**

```mysql
delete from dept1 where deptno = 10;
```

​    **删除所有记录？**

```mysql
delete from dept1;
```

​    **怎么删除大表中的数据？（重点）**

```mysql
truncate table 表名;	# 表被截断，不可回滚。永久丢失。
```

**删除表：**

```mysql
drop table 表名;（通用）  或  drop table if exists 表名;
```

## 12、表结构的修改

对于表结构的修改，这里不讲了，大家使用工具（ navicat ）完成即可，因为在实际开发中表一旦设计好之后，对表结构的修改是很少的，修改表结构就是对之前的设计进行了否定，即使需要修改表结构，我们也可以直接使用工具操作。修改表结构的语句不会出现在Java代码当中。

出现在java代码当中的sql包括：insert delete update select（这些都是表中的数据操作。）

增删改查有一个术语：**CRUD操作**

==**Create（增） 	Retrieve（检索）	 Update（修改） 	Delete（删除）**==

## 13、约束(Constraint)

### 13.1、什么是约束？常见的约束有哪些呢？

​    在创建表的时候，可以给表的字段添加相应的约束，添加约束的目的是为了保证表中数据的合法性、有效性、完整性。

​    常见的约束有哪些呢？

​       **非空约束 (not null)：**约束的字段不能为 NULL

​       **唯一约束 (unique)：**约束的字段不能重复

​       **主键约束 (primary key)：**约束的字段既不能为NULL，也不能重复（简称PK）

​       **外键约束 (foreign key)：**...（简称FK）

​       检查约束(check)：注意 Oracle 数据库有check 约束，但是 mysql 没有，目前 mysql 不支持该约束。

### 13.2、非空约束 not null

   ```mysql
   drop table if exists t_user;
   
   create table t_user(
   	id int,
   	username varchar(255) not null,
   	password varchar(255)
   );
   
   insert into t_user(id,password) values(1,'123'); 
   # 编译错误，约束username字段不能为空！ERROR 1364 (HY000): Field 'username' doesn't have a default value
   
   insert into t_user(id,username,password) values(1,'lisi','123');
   ```

# Mysql days03

## 1、约束

### 1.1、唯一性约束(unique)

  唯一性约束修饰的字段具有唯一性，不能重复。但可以为 null。

 **案例：给某一列添加 unique**

```mysql
drop table if exists t_user;

create table t_user(
	id int,
	username varchar(255) unique # 列级约束
);

insert into t_user values(1,'zhangsan');     

insert into t_user values(2,'zhangsan'); 
# 出现编译错误，唯一性约束，该字段与上一行字段重复，但可以为null！ERROR 1062 (23000) : Duplicate entry 'zhangsan' for key 'username'
```

 **案例：给两个列或者多个列添加 unique**

```mysql
drop table if exists t_user;      
create table t_user(          
    id int,          
    usercode varchar(255),          
    username varchar(255),          
    unique(usercode,username)  # 多个字段联合起来添加一个约束 unique 【表级约束】      
);

drop table if exists t_user;
create table t_suer(          
    id int,
    usercode varchar(255) unique,
    username varchar(255) unique 
);  # 两个字段各自不能重复，列级约束
```

  注意：not null 约束只有列级约束，没有表级约束。

### 1.2、主键约束

 怎么给一张表添加主键约束呢？

```mysql
drop table if exists t_user;

create table t_user(
	id int primary key, 		# 列级约束
	username varchar(255),
	email varchar(255)
);
```

   id是主键，因为添加了**主键约束，主键字段中的数据不能为 null，也不能重复。**

**主键相关的术语？**

   主键约束 ： primary key

   主键字段 :  id 字段添加 primary key 之后，id 叫做主键字段

   主键值 ：   id 字段中的每一个值都是主键值。

**主键有什么作用？**

   根据主键字段的字段数量来划分：

​    **单一主键** (推荐的，常用的。)

​    **复合主键**(多个字段联合起来添加一个主键约束) (复合主键不建议使用，因为复合主键违背三范式。)

   根据主键性质来划分：

​      **自然主键** ：主键值最好就是一个和业务没有任何关系的自然数。(这种方式是推荐的)

​      **业务主键** : 主键值和系统的业务挂钩，例如：拿着银行卡的卡号做主键、拿着身份证号做为主键。(不推荐使用)最好不要拿着和业务挂钩的字段做为主键。因为以后的业务一旦发生改变的时候，主键也可能需要随着发生变化，但有的时候没有办法变化，因为变化可能会导致主键重复。

**一张表的主键约束只能有1个。(必须记住)**

使用表级约束方式定义主键：

```mysql
drop table if exists t_user;

create table t_user(
	id int,
	username varchar(255),
	primary key(id)
);
```

以下内容是演示一下复合主键，不需要掌握：

```mysql
drop table if exists t_user;

create table t_user(
	id int,
	username varchar(255),
	password varchar(255),
	primary key(id,username)
);
```

**mysql 提供主键值自增： (非常重要)**

 ```mysql
 drop table if exists t_user;
 
 create table t_user(
 	id int primary key auto_increment, # id 字段自动维护一个自增的数字，从1开始，以1递增。
 	username varchar(255)
 );
 
 insert into t_user(username) values('a');
 insert into t_user(username) values('b');
 insert into t_user(username) values('c');
 select * from t_user;
 ```

   提示：Oracle 当中也提供了一个自增机制，叫做：序列( sequence )对象。

### 1.3、外键约束

关于外键约束的相关术语：

   **外键约束**：foreign key

   **外键字段**：添加有外键约束的字段

   **外键值**：外键字段中的每一个值。

业务背景：

   **请设计数据库表，用来维护学生和班级的信息？**

- 第一种方案：一张表存储所有数据

| no(pk) | name | classno | classname |
| :----: | :--: | :-----: | :-------: |
|   1    | zs1  |   101   |  高三1班  |
|   2    | zs2  |   101   |  高三1班  |
|   3    | zs3  |   102   |  高三2班  |
|   4    | zs4  |   102   |  高三2班  |
|   5    | zs5  |   102   |  高三2班  |

​      缺点：冗余。【不推荐】

- 第二种方案：两张表(班级表和学生表)

​     t_class 班级表

| cno(pk) |  cname  |
| :-----: | :-----: |
|   101   | 高三1班 |
|   102   | 高三2班 |

​     t_student 学生表

| sno(pk) | sname | classno(该字段添加外键约束fk) |
| :-----: | :---: | :---------------------------: |
|    1    |  zs1  |              101              |
|    2    |  zs2  |              101              |
|    3    |  zs3  |              102              |
|    4    |  zs4  |              102              |
|    5    |  zs5  |              102              |

​	将以上表的建表语句写出来：

   t_student 中的 classno 字段引用 t_class 表中的 cno 字段，此时 t_student 表叫做子表。t_class 表叫做父表。

   删除数据的时候，先删除子表，再删除父表。

   添加数据的时候，先添加父表，再添加子表。

   创建表的时候，先创建父表，再创建子表。

   删除表的时候，先删除子表，再删除父表。

 ```mysql
 drop table if exists t_student;
 drop table if exists t_class;
 
 create table t_class(
 	cno int,
 	cname varchar(255),
 	primary key(cno)
 );
 
 create table t_student(
 	sno int,
 	sname varchar(255),
 	classno int,
 	primary key(sno),
 	foreign key(classno) references t_class(cno)
 );
 
 insert into t_class values(101,'xxxxx');
 insert into t_class values(102,'yyyyy');
 insert into t_student values(1,'zs1',101);
 insert into t_student values(2,'zs2',101);
 insert into t_student values(3,'zs3',102);
 
 select * from t_class;
 select * from t_student;
 
 insert into t_student values(4,'lisi',103); 
 # 编译错误，引用的103，父表中没有该字段！ERROR 1452 (23000) : Cannot add or update a child row :aforeign key constraint fails (bjpowernode INT YT......)
 ```

 \* 外键值可以为 NULL？

   **外键可以为 null**。

 \* 外键字段引用其他表的某个字段的时候，被引用的字段必须是主键吗？

   注意：**被引用的字段不一定是主键，但至少是具有 unique 约束，具有唯一性，不可重复**！

## 2、存储引擎？

###   2.1、完整的建表语句

```mysql
CREATE TABLE t_x (
	id int(11) DEFAULT NULL
) ENGINE = InnoDB DEFAULT CHARSET = utf8; 
```

   注意：在MySQL当中，凡是标识符使用飘号（反引号）括起来的。最好别用，不通用。

   建表的时候可以指定存储引擎，也可以指定字符集。

  ==**mysql默认使用的存储引擎是 InnoDB 方式。**==

   **默认采用的字符集是UTF-8。**

###   2.2、什么是存储引擎呢？

​    存储引擎这个名字只有在 mysql 中存在。(Oracle 中有对应的机制，但不叫做存储引擎。Oracle 中没有特殊的名字，就是"表的存储方式")

​    mysql 支持很多存储引擎，每个存储引擎都对应了一种不同的存储方式。    

​	每一个存储引擎都有自己的优缺点，需要在合适的时机选择合适的存储引擎。

###   2.3、查看当前mysql支持的存储引擎？

```mysql
show engines \G
```

###   2.4、常见的存储引擎？

- **MyISAM**

```mysql
Engine: MyISAM
Support: YES
Comment: MyISAM storage engine
Transactions: NO
XA: NO
Savepoints: NO
```

​    MyISAM 这种存储引擎不支持事务。

​    MyISAM 是 mysql 最常用的存储引擎，但是这种存储引擎不是默认的。

​    MyISAM 采用三个文件组织一个表：

​      	xxx.frm(存储格式的文件)

​          xxx.MYD(存储表中数据的文件)

​          xxx.MYI(存储表中索引的文件)

​    优点：可被压缩，节省存储空间。并且可以转换为只读表，提高检索效率。

​    缺点:不支持事务。

- **InnoDB**

```mysql
Engine: InnoDB
Support: DEFAULT
Comment: Supports transactions, row-level locking, and foreign keys
Transactions: YES
XA: YES
Savepoints: YES   
```

 优点：支持事务、行级锁、外键等。这种存储引擎数据的安全得到保障。

​    表的结构存储在 xxx.frm 文件中

​    数据存储在 tablespace 这样的表空间中(逻辑概念)，无法被压缩，无法转换成只读。

​    这种 InnoDB 存储引擎在 MySQL 数据库崩溃之后提供自动恢复机制。

​    InoDB 支持级联删除和级联更新。

- **MEMORY**

```mysql
Engine: MEMORY
Support: YES
Comment: Hash based, stored in memory, useful for temporary tables
Transactions: NO
XA: NO
Savepoints: NO
```

​     缺点：不支持事务。数据容易丢失。因为所有数据和索引都是存储在内存当中的。

​     优点：查询速度最快。

​     以前叫做 HEPA 引擎。

## 3、事务(Transaction)

###   3.1、什么是事务？

​    一个事务是一个完整的业务逻辑单元，不可再分。

​    比如：银行账户，从A账户向B账户转账 10000 元，需要执行两条 update 语句。

```mysql
update t_act set balance = balance - 10000 where actno = 'act-001';
update t_act set balance = balance + 10000 where actno = 'act-002';
```

  以上两条DML语句必须同时成功，或者同时失败，不允许出现一条成功，一条失败。

  想要保证以上的两条DML语句同时成功或者同时失败，那么就要使用数据库的"**事务机制**"。

###   3.2、和事务相关的语句只有：DML语句。(insert delete update)

​    为什么？因为他们这三个语句都是和数据库表当中的"数据"相关的。

​    事务的存在是为了保证数据的完整性，安全性。

###   3.3、假设所有的业务都能使用1条 DML 语句搞定，还需要事务机制吗？

  不需要事务机制。但实际情况不是这样的，通常一个"事务【业务】"需要多条 DML 语句共同联合完成。

###   3.4、事务的特性？

事务包括四大特性：**ACID**

​    **A:原子性**：事务是最小的工作单元，不可再分。

​    **B:一致性**：事务必须保证多条 DML 语句同时成功或者同时失败。

​    **C:隔离性**：事务 A 与事务 B 之间具有隔离。

​    **D:持久性**：持久性说的是最终数据必须持久化到硬盘中，事务才算成功结束。

###   3.5、关于事务之间的隔离性？

  事务隔离性存在隔离级别，理论上隔离级别包括4个：

- **第一级别：读未提交( read uncommitted )**

​        对方事务还没有提交，我们当前事务可以读取到对方未提交的数据。

​        读未提交存在**脏读**( Dirty Read ) 现象：表示读到了脏数据。

- **第二级别：读已提交( read committed )**

​        对方事务提交之后的数据我方可以读取到。

​        读已提交存在的问题是：不可重复读。

- **第三级别：可重复读(repeatable read)**

​        这种隔离级别解决了：不可重复读问题。

​        这种隔离级别存在的问题是：读取到的数据是幻象。

- **第四级别：序列化读/串行化读**

​        解决了所有问题。

​        效率低，需要事务排队。

Oracle 数据库默认的隔离级别是：第二级别，读已提交。

mysql 数据库默认的隔离级别是：第三级别，可重复读。

###   3.6、演示事务：

​    **mysql 事务默认情况下是自动提交的。**

​      (什么是自动提交？只要执行任意一条 DML 语句则提交一次。)	怎么关闭默认提交？`start transaction;`

 建表：

```mysql
drop table if exists t_user;

create table t_user(
	id int primary key auto_increment,
	username varchar(255)
);
```

**演示：mysql 中的事务是支持自动提交的，只要执行一条 DML 语句，则提交一次。**

```mysql
mysql> insert into t_user(username) values('zs');    # 插入一条语句

mysql> select * from t_user;      # 查看，显示一条数据

mysql> rollback;    # 回滚

mysql> select * from t_user;      # 查看，显示一条数据
```

注：回滚未起作用，表明执行一条DML语句，事务自动提交。

**演示：使用 start transaction;  关闭自动提交机制。**

```mysql
mysql> select * from t_user;      	# 查看，显示一条数据

mysql> start transaction;     		# 开启事务

mysql> insert into t_user(username) values("lisi"); 	# 插入数据

mysql> select * from t_user;  		# 查看，显示两条数据

mysql> insert into t_user(username) values("wangwu"); 	# 插入数据

mysql> select * from t_user;  		# 查看，显示三条数据

mysql> rollback;  					# 回滚

mysql> select * from t_user;  		# 查看，显示一条数据
```

注：事务未结束开启回滚，回到事务开启的位置，插入的数据均失效，回滚之后，该事务结束。

```mysql
mysql> start transaction;     		# 开启事务
mysql> insert into t_user(username) values("wangwu");    # 插入数据
mysql> insert into t_user(username) values("object");       # 插入数据
mysql> insert into t_user(username) values("joke");        # 插入数据
mysql> insert into t_user(username) values("xiaozhaozhao");# 插入数据

mysql> select * from t_user;      # 查看，显示1+4=5条数据（主键自增从4开始，之前插入过2，3两条数据，虽然他们失效了）
mysql> commit;     				  # 提交事务，该事务结束
mysql> select * from t_user;      # 查看，显示5条数据
mysql> rollback;   				  # 回滚
mysql> select * from t_user;   	  # 查看，显示5条数据
```

注：回滚并未起作用，原因是 commit 已经将事务提交，此次事务已经结束。

​    **rollback : 回滚。**

​    **commit ： 提交。**

​    **start transaction : 关闭自动提交机制。**

**回滚到某节点：**

```mysql
start transaction；

…操作1

savepoint a;

…操作2

savepoint b;

…操作3

rollback a;
```

回滚到节点a，则a之前的操作1保存，a节点后的操作2和操作3失效。

**演示两个事务，假如隔离级别：**

​    演示第1级别：读未提交

```mysql
set global transaction isolation level read uncommitted;
```

​    演示第二级别；读已提交

```mysql
set global transaction isolation level read committed;   
```

​    演示第三级别: 可重复读

```mysql
set global transaction isolation level repeatable read;
```

​    演示第四级别: 序列化（串行化）

```mysql
set global transaction isolation level serializable;
```

  mysql远程登录：mysql -h192.168.151.18 -uroot -p444

## 4、索引

###   4.1、什么是索引？有什么用？

​    索引就相当于一本书的目录，通过目录可以快速的找到对应的资源。

​    在数据库方面，查询一张表的时候有两种检索方式：

​      第一种方式：全表扫描

​      第二种方式：根据索引检索(效率很高)

​    索引为什么可以提高检索效率呢？

​      其实最根本的原理是缩小了扫描的范围。

​    索引虽然可以提高检索效率，但是不能随意的添加索引，因为索引也是数据库当中的对象，也需要数据库不断的维护。是有维护成本的。

​    比如：表中的数据经常被修改，这样就不适合添加索引，因为数据一旦修改，索引需要重新排序，进行维护。

​    添加索引是给某一个字段，或者说某些字段添加索引。

```mysql
select ename,sal from emp where ename = 'SMITH';
```

​    当ename字段没有添加索引的时候，以上sql语句会进行全表扫描，扫描ename字段中所有的值。

​    当ename字段添加索引的时候，以上sql语句会根据索引扫描，快速定位。

###   4.2、怎么创建索引对象？怎么删除索引对象？

​    创建索引对象：

```mysql
create index 索引名称 on 表名(字段名);  
```

​    删除索引对象：

```mysql
drop index 索引名称 on 表名;     
```

###   4.3、什么时候考虑给字段添加索引？(满足什么条件)

- 数据量庞大。(根据客户的需求，根据线上的环境)

* 该字段很少的 DML 操作。(因为字段进行修改操作，索引也需要维护)

* 该字段经常出现在 where 子句中。(经常根据哪个字段维护)

###   4.4、注意：主键具有 unique 约束的字段会自动添加索引。

​    根据主键查询效率较高，尽量根据主键检索。

###   4.5、查看 sql 语句的执行计划：

```mysql
mysql> explain select ename,sal from emp where sal = 5000;
```

  给薪资sal字段添加索引：

```mysql
create index emp_sal_index on emp(sal);

mysql> explain select ename,sal from emp where sal = 5000;    # rows检索次数减少了
```

###   4.6、索引底层采用的数据结构是：B + Tree

###   4.7、索引的实现原理？

通过 B+ Tree 缩小扫描范围，底层索引进行了排序，分区，索引会携带数据在表中的"物理地址"，最终通过索引检索到数据之后，获取到关联的物理地址，通过物理索引检索到数据之后，获取到关联的物理地址，通过物理地址定位表中的数据，效率是最高的。

   ```mysql
   select ename from emp where ename = 'SMITH';
   ```

通过索引转换为：

```mysql
select ename from emp where 物理地址 = 0x123;
```

###   4.8、索引的分类？

​    单一索引：给单个字段添加索引

​    复合索引：给多个字段联合起来添加一个索引

​    主键索引：主键上会自动添加索引

​    唯一索引：有unique约束的字段会自动添加索引

​    ......

###   4.9、索引什么时候失效？

```mysql
select ename from emp where ename like ' %A% ';
```

​    模糊查询的时候，第一个通配符使用的是%，这个时候索引是是失效的。

## 5、视图(view)

###   5.1、什么是视图？

​    站在不同的角度去看到数据。(同一张表的数据，通过不同的角度去看待)

###   5.2、怎么创建视图？怎么删除视图？

```mysql
create view myview as select empno,ename from emp;
drop view myview;
```

  注意：只有DQL语句才能以试图对象的方式创建出来。

###   5.3、对试图进行增删改查，会影响到原表数据。(通过视图影响原表数据，不是直接操作的原表)

  可以对试图进行 CRUD 操作。

###   5.4、面向视图操作？

```mysql
create table emp_bak as select * from emp;

create view myview1 as select empno,ename,sal from emp_bak;

update myview1 set ename = 'hehe',sal = 1 where empno 7369; 	# 通过视图修改原表数据。

delete from myview1 where empno = 7369; 						# 通过试图删除原表数据。
```

###   5.5、试图的作用？

​    试图可以隐藏表的实现细节。保密级别较高的系统，数据库只对外提供相关的视图，java 程序员只对视图对象进行 CRUD。

## 6、DBA命令

###   6.1、在数据库当中的数据导出

  **在 windows 的 DOS 命令窗口中执行：(导出整个库)**

注：不进入mysql

```mysql
# 命令       数据库名称    路径及文件名  账户及密码
mysqldump bjpowernode>D:\bjpowernode.sql -uroot -p999		# 导出整个库

mysqldump bjpowernode emp>D:\bjpowernode.sql -uroot -p999	# 导出数据库中指定的表
```

###   6.2、导入数据

```mysql
create database bjpowernode;  	# 创建数据库
use bjpowernode;           		# 进入该数据库
source D:\bjpowernode.sql   	# 导入数据库
```

## 7、数据库设计三范式(重点内容，面试经常会问)

###   7.1、什么是设计范式？

​    设计表的依据。按照这三个范式设计的表不会出现数据冗余。

###   7.2、三范式都是哪些？

- **第一范式：任何一张表都应该有主键，并且每一个字段原子性不可再分。**

- **第二范式：建立在第一范式的基础上，所有非主键字段完全依赖主键，不能产生部份依赖。**

​      多对多？三张表，关系表两个外键。

 t_student学生表     

| sno(pk) | sname |
| :-----: | :---: |
|    1    | 张三  |
|    2    | 李四  |
|    3    | 王五  |

t_teacher  讲师表         

| tno(pk) | tname  |
| :-----: | :----: |
|    1    | 王老师 |
|    2    | 张老师 |
|    3    | 李老师 |

t_student_teacher_relation 学生讲师关系表

| id(pk) | sno(fk) | tno(fk) |
| ------ | ------- | ------- |
| 1      | 1       | 3       |
| 2      | 1       | 1       |
| 3      | 2       | 2       |
| 4      | 2       | 3       |

- **第三范式：建立在第二范式的基础上，所有非主键字段直接依赖主键，不能产生传递依赖。**

​      一对多？两张表，多的表加外键。

班级t_class

​      cno(pk)     cname

​      \-------------------------------

​       1       班级1

​       2       班级2

学生t_student

| sno(pk) | sname | classno(fk) |
| ------- | ----- | ----------- |
| 101     | 张1   | 1           |
| 102     | 张2   | 2           |
| 103     | 张3   | 2           |
| 104     | 张4   | 1           |
| 105     | 张5   | 2           |

​     提醒：在实际的开发中，以满足客户需求为主，有的时候会拿冗余换执行速度。

###   7.3、一对一怎么设计？

 一对一设计有两种方案：**主键共享**

  t_user_login 用户登陆表

| id(pk) | username | password |
| ------ | -------- | -------- |
| 1      | zs       | 123      |
| 2      | ls       | 456      |

  t_user_detail 用户详细信息表

| id(pk+fk) | realname | tel     |
| --------- | -------- | ------- |
| 1         | 张三     | 1112234 |
| 2         | 李四     | 1432412 |

 一对一设计有两种方案: **外键唯一**。

 t_user_login 用户登陆表

| id(pk) | username | password |
| ------ | -------- | -------- |
| 1      | zs       | 123      |
| 2      | ls       | 456      |

 t_user_detail 用户详细信息表

| id(pk) | realname | tel       | userid(fk+unique) |
| ------ | -------- | --------- | ----------------- |
| 1      | 张三     | 111111114 | 1                 |
| 2      | 李四     | 121432412 | 2                 |

 