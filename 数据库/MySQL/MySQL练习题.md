# MySQL练习题

## 1.取得每个部门最高薪水的人员名称

第一步：求出每个部门的最高薪水
select
	e.deptno,max(e.sal) as maxsal
from
	emp e
group by
	e.deptno;
+--------+---------+
| deptno | maxsal  |
+--------+---------+
|     10 | 5000.00 |
|     20 | 3000.00 |
|     30 | 2850.00 |
+--------+---------+
将以上查询结果当成一个临时表t(deptno,maxsal)
select 
	e.deptno,e.ename,t.maxsal,e.sal
from
	(select
			e.deptno,max(e.sal) as maxsal
		from
			emp e
		group by
			e.deptno)t
join
	emp e
on
	t.deptno = e.deptno
where
	t.maxsal = e.sal
order by
	e.deptno;
+--------+-------+---------+---------+
| deptno | ename | maxsal  | sal     |
+--------+-------+---------+---------+
|     10 | KING  | 5000.00 | 5000.00 |
|     20 | SCOTT | 3000.00 | 3000.00 |
|     20 | FORD  | 3000.00 | 3000.00 |
|     30 | BLAKE | 2850.00 | 2850.00 |
+--------+-------+---------+---------+

## 2.哪些人的薪水在部门平均薪水之上

第一步：求出每个部门的平均薪水
select
	e.deptno,avg(e.sal) as avgsal
from
	emp e
group by 
	e.deptno;
+--------+-------------+
| deptno | avgsal      |
+--------+-------------+
|     10 | 2916.666667 |
|     20 | 2175.000000 |
|     30 | 1566.666667 |
+--------+-------------+
将以上查询结果当成临时表t(deptno,avgsal)

select
	t.deptno,e.ename
from
	(select
		e.deptno,avg(e.sal) as avgsal
	from
		emp e
	group by 
		e.deptno) t
join
	emp e
on
	e.deptno = t.deptno
where
	e.sal > t.avgsal;
+--------+-------+
| deptno | ename |
+--------+-------+
|     30 | ALLEN |
|     20 | JONES |
|     30 | BLAKE |
|     20 | SCOTT |
|     10 | KING  |
|     20 | FORD  |
+--------+-------+

## 3.取得部门中（所有人的）平均薪水等级

### 3.1 取得部门中所有人的平均薪水的等级

第一步：求出部门的平均薪水
select
	e.deptno,avg(e.sal) as avgsal
from
	emp e
group by
	e.deptno;
将以下查询结果当成临时表t(deptno,avgsal)
+--------+-------------+
| deptno | avgsal      |
+--------+-------------+
|     10 | 2916.666667 |
|     20 | 2175.000000 |
|     30 | 1566.666667 |
+--------+-------------+

select * from salgrade;
+-------+-------+-------+
| GRADE | LOSAL | HISAL |
+-------+-------+-------+
|     1 |   700 |  1200 |
|     2 |  1201 |  1400 |
|     3 |  1401 |  2000 |
|     4 |  2001 |  3000 |
|     5 |  3001 |  9999 |
+-------+-------+-------+

select 
	t.deptno,t.avgsal,s.grade
from
	(select
			e.deptno,avg(e.sal) as avgsal
		from
			emp e
		group by
			e.deptno) t
join
	salgrade s
on
	t.avgsal between s.losal and s.hisal;
+--------+-------------+-------+
| deptno | avgsal      | grade |
+--------+-------------+-------+
|     30 | 1566.666667 |     3 |
|     10 | 2916.666667 |     4 |
|     20 | 2175.000000 |     4 |
+--------+-------------+-------+

### 3.2 取得部门中所有人的平均的薪水等级

第一步：求出每个人的薪水等级
select 
	e.deptno,e.ename,s.grade
from
	emp e
join
	salgrade s
on
	e.sal between s.losal and s.hisal
order by
	e.deptno;
+--------+--------+-------+
| deptno | ename  | grade |
+--------+--------+-------+
|     10 | CLARK  |     4 |
|     10 | MILLER |     2 |
|     10 | KING   |     5 |
|     20 | ADAMS  |     1 |
|     20 | SMITH  |     1 |
|     20 | FORD   |     4 |
|     20 | SCOTT  |     4 |
|     20 | JONES  |     4 |
|     30 | BLAKE  |     4 |
|     30 | JAMES  |     1 |
|     30 | ALLEN  |     3 |
|     30 | WARD   |     2 |
|     30 | TURNER |     3 |
|     30 | MARTIN |     2 |
+--------+--------+-------+
将以上查询结果当成临时表t(deptno,ename,grade)
select 
	t.deptno,avg(t.grade) as avgGrade
from
	(select 
		e.deptno,e.ename,s.grade
	from
		emp e
	join
		salgrade s
	on
		e.sal between s.losal and s.hisal) t
group by
	t.deptno;
+--------+----------+
| deptno | avgGrade |
+--------+----------+
|     10 |   3.6667 |
|     20 |   2.8000 |
|     30 |   2.5000 |
+--------+----------+

## 4.不准用组函数（MAX），取得最高薪水（给出两种解决方案）

select sal from emp order by sal desc limit 1;
+---------+
| sal     |
+---------+
| 5000.00 |
+---------+

a
+---------+
| sal     |
+---------+
|  800.00 |
| 1600.00 |
| 1250.00 |
| 2975.00 |
| 1250.00 |
| 2850.00 |
| 2450.00 |
| 3000.00 |
| 5000.00 |
| 1500.00 |
| 1100.00 |
|  950.00 |
| 3000.00 |
| 1300.00 |
+---------+

b
+---------+
| sal     |
+---------+
|  800.00 |
| 1600.00 |
| 1250.00 |
| 2975.00 |
| 1250.00 |
| 2850.00 |
| 2450.00 |
| 3000.00 |
| 5000.00 |
| 1500.00 |
| 1100.00 |
|  950.00 |
| 3000.00 |
| 1300.00 |
+---------+

select 
	distinct a.sal
from
	emp a
join
	emp b
on
	a.sal < b.sal;

select sal from emp where sal not in(select 
					distinct a.sal
				from
					emp a
				join
					emp b
				on
					a.sal < b.sal);
select sal from emp where sal not in(select 
					distinct a.sal
				from
					emp a
				join
					emp b
				on
					a.sal > b.sal);

## 5.取得平均薪水最高的部门的部门编号

第一步：求出部门平均薪水
select
	e.deptno,avg(e.sal) as avgsal
from
	emp e
group by
	e.deptno;
+--------+-------------+
| deptno | avgsal      |
+--------+-------------+
|     10 | 2916.666667 |
|     20 | 2175.000000 |
|     30 | 1566.666667 |
+--------+-------------+
第二步：将以上查询结果当成临时表t(deptno,avgsal)
select max(t.avgsal) as maxAvgSal from (select
						e.deptno,avg(e.sal) as avgsal
					from
						emp e
					group by
						e.deptno) t;
+-------------+
| maxAvgSal   |
+-------------+
| 2916.666667 |
+-------------+

select
	e.deptno,avg(e.sal) as avgsal
from
	emp e
group by
	e.deptno
having 
	avgsal = (select max(t.avgsal) as maxAvgSal from (select
						e.deptno,avg(e.sal) as avgsal
					from
						emp e
					group by
						e.deptno) t);
+--------+-------------+
| deptno | avgsal      |
+--------+-------------+
|     10 | 2916.666667 |
+--------+-------------+

## 6.取得平均薪水最高的部门的部门名称

select
	e.deptno,d.dname,avg(e.sal) as avgsal
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
group by
	e.deptno,d.dname
having 
	avgsal = (select max(t.avgsal) as maxAvgSal from (select
						e.deptno,avg(e.sal) as avgsal
					from
						emp e
					group by
						e.deptno) t);

## 7.求平均薪水的等级最低的部门的部门名称

第一步：部门的平均薪水
select 
	e.deptno,d.dname,avg(e.sal) as avgsal
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
group by
	e.deptno,d.dname;
+--------+------------+-------------+
| deptno | dname      | avgsal      |
+--------+------------+-------------+
|     10 | ACCOUNTING | 2916.666667 |
|     20 | RESEARCH   | 2175.000000 |
|     30 | SALES      | 1566.666667 |
+--------+------------+-------------+
第二步：将以上结果当成临时表t(deptno,avgsal)与salgrade表进行表连接：t.avgsal between s.losal and s.hisal;
select 
	t.deptno,t.dname,s.grade
from	
	(select 
			e.deptno,d.dname,avg(e.sal) as avgsal
		from
			emp e
		join
			dept d
		on
			e.deptno = d.deptno
		group by
			e.deptno,d.dname)t
join
	salgrade s
on
	t.avgsal between s.losal and s.hisal;
+--------+------------+-------+
| deptno | dname      | grade |
+--------+------------+-------+
|     30 | SALES      |     3 |
|     10 | ACCOUNTING |     4 |
|     20 | RESEARCH   |     4 |
+--------+------------+-------+

第三步：将以上查询结果当成一张临时表t
select min(t.grade) as minGrade from (select 
					t.deptno,t.dname,s.grade
				from	
					(select 
							e.deptno,d.dname,avg(e.sal) as avgsal
						from
							emp e
						join
							dept d
						on
							e.deptno = d.deptno
						group by
							e.deptno,d.dname)t
				join
					salgrade s
				on
					t.avgsal between s.losal and s.hisal)t;
+----------+
| minGrade |
+----------+
|        3 |
+----------+

select 
	t.deptno,t.dname,s.grade
from	
	(select 
			e.deptno,d.dname,avg(e.sal) as avgsal
		from
			emp e
		join
			dept d
		on
			e.deptno = d.deptno
		group by
			e.deptno,d.dname)t
join
	salgrade s
on
	t.avgsal between s.losal and s.hisal
where
	s.grade = (select min(t.grade) as minGrade from (select 
					t.deptno,t.dname,s.grade
				from	
					(select 
							e.deptno,d.dname,avg(e.sal) as avgsal
						from
							emp e
						join
							dept d
						on
							e.deptno = d.deptno
						group by
							e.deptno,d.dname)t
				join
					salgrade s
				on
					t.avgsal between s.losal and s.hisal)t);
+--------+-------+-------+
| deptno | dname | grade |
+--------+-------+-------+
|     30 | SALES |     3 |
+--------+-------+-------+

## 8.取得比普通员工（员工代码没有在mgr上出现的）的最高薪水还要高的经理人姓名

第一步：找出普通员工(员工代码没有出现在mgr上的)
	1.1 先找出mgr有哪些人
	select distinct mgr from emp;
		+------+
		| mgr  |
		+------+
		| 7902 |
		| 7698 |
		| 7839 |
		| 7566 |
		| NULL |
		| 7788 |
		| 7782 |
		+------+
select * from emp where empno in(select distinct mgr from emp);
+-------+-------+-----------+------+------------+---------+------+--------+
| EMPNO | ENAME | JOB       | MGR  | HIREDATE   | SAL     | COMM | DEPTNO |
+-------+-------+-----------+------+------------+---------+------+--------+
|  7566 | JONES | MANAGER   | 7839 | 1981-04-02 | 2975.00 | NULL |     20 |
|  7698 | BLAKE | MANAGER   | 7839 | 1981-05-01 | 2850.00 | NULL |     30 |
|  7782 | CLARK | MANAGER   | 7839 | 1981-06-09 | 2450.00 | NULL |     10 |
|  7788 | SCOTT | ANALYST   | 7566 | 1987-04-19 | 3000.00 | NULL |     20 |
|  7839 | KING  | PRESIDENT | NULL | 1981-11-17 | 5000.00 | NULL |     10 |
|  7902 | FORD  | ANALYST   | 7566 | 1981-12-03 | 3000.00 | NULL |     20 |
+-------+-------+-----------+------+------------+---------+------+--------+
select max(sal) as maxsal from emp where empno not in(select distinct mgr from emp where mgr is not null);
+---------+
| maxsal  |
+---------+
| 1600.00 |
+---------+

not in不会自动忽略空值
in会自动忽略空值


select ename from emp where sal > (select max(sal) as maxsal from emp where empno not in(select distinct mgr from emp where mgr is not null));
+-------+
| ename |
+-------+
| JONES |
| BLAKE |
| CLARK |
| SCOTT |
| KING  |
| FORD  |
+-------+

## 9.取得薪水最高的前五名员工

select * from emp order by sal desc limit 0,5;
+-------+-------+-----------+------+------------+---------+------+--------+
| EMPNO | ENAME | JOB       | MGR  | HIREDATE   | SAL     | COMM | DEPTNO |
+-------+-------+-----------+------+------------+---------+------+--------+
|  7839 | KING  | PRESIDENT | NULL | 1981-11-17 | 5000.00 | NULL |     10 |
|  7788 | SCOTT | ANALYST   | 7566 | 1987-04-19 | 3000.00 | NULL |     20 |
|  7902 | FORD  | ANALYST   | 7566 | 1981-12-03 | 3000.00 | NULL |     20 |
|  7566 | JONES | MANAGER   | 7839 | 1981-04-02 | 2975.00 | NULL |     20 |
|  7698 | BLAKE | MANAGER   | 7839 | 1981-05-01 | 2850.00 | NULL |     30 |
+-------+-------+-----------+------+------------+---------+------+--------+

## 10.取得薪水最高的第六到第十名员工

select * from emp order by sal desc limit 5,5;
+-------+--------+----------+------+------------+---------+---------+--------+
| EMPNO | ENAME  | JOB      | MGR  | HIREDATE   | SAL     | COMM    | DEPTNO |
+-------+--------+----------+------+------------+---------+---------+--------+
|  7782 | CLARK  | MANAGER  | 7839 | 1981-06-09 | 2450.00 |    NULL |     10 |
|  7499 | ALLEN  | SALESMAN | 7698 | 1981-02-20 | 1600.00 |  300.00 |     30 |
|  7844 | TURNER | SALESMAN | 7698 | 1981-09-08 | 1500.00 |    0.00 |     30 |
|  7934 | MILLER | CLERK    | 7782 | 1982-01-23 | 1300.00 |    NULL |     10 |
|  7654 | MARTIN | SALESMAN | 7698 | 1981-09-28 | 1250.00 | 1400.00 |     30 |
+-------+--------+----------+------+------------+---------+---------+--------+

## 11.取得最后入职的5名员工

select * from emp order by hiredate desc limit 5;
+-------+--------+---------+------+------------+---------+------+--------+
| EMPNO | ENAME  | JOB     | MGR  | HIREDATE   | SAL     | COMM | DEPTNO |
+-------+--------+---------+------+------------+---------+------+--------+
|  7876 | ADAMS  | CLERK   | 7788 | 1987-05-23 | 1100.00 | NULL |     20 |
|  7788 | SCOTT  | ANALYST | 7566 | 1987-04-19 | 3000.00 | NULL |     20 |
|  7934 | MILLER | CLERK   | 7782 | 1982-01-23 | 1300.00 | NULL |     10 |
|  7902 | FORD   | ANALYST | 7566 | 1981-12-03 | 3000.00 | NULL |     20 |
|  7900 | JAMES  | CLERK   | 7698 | 1981-12-03 |  950.00 | NULL |     30 |
+-------+--------+---------+------+------------+---------+------+--------+

## 12.取得每个薪水等级有多少员工

第一步：查询出每个员工的薪水等级
select 
	e.ename,s.grade 
from 
	emp e
join
	salgrade s
on
	e.sal between s.losal and s.hisal
order by
	s.grade;
+--------+-------+
| ename  | grade |
+--------+-------+
| JAMES  |     1 |
| SMITH  |     1 |
| ADAMS  |     1 |
| MILLER |     2 |
| WARD   |     2 |
| MARTIN |     2 |
| ALLEN  |     3 |
| TURNER |     3 |
| BLAKE  |     4 |
| FORD   |     4 |
| CLARK  |     4 |
| SCOTT  |     4 |
| JONES  |     4 |
| KING   |     5 |
+--------+-------+

将以上查询结果当成临时表t(ename,grade)
select
	t.grade,count(t.ename) as totalEmp
from
	(select 
		e.ename,s.grade 
	from 
		emp e
	join
		salgrade s
	on
		e.sal between s.losal and s.hisal) t
group by
	t.grade;
+-------+----------+
| grade | totalEmp |
+-------+----------+
|     1 |        3 |
|     2 |        3 |
|     3 |        2 |
|     4 |        5 |
|     5 |        1 |
+-------+----------+

## 13.有3个表S(学生表)，C（课程表），SC（学生选课表）

S（SNO，SNAME）代表（学号，姓名）
C（CNO，CNAME，CTEACHER）代表（课号，课名，教师）
SC（SNO，CNO，SCGRADE）代表（学号，课号，成绩）
问题：
1、找出没选过“黎明”老师的所有学生姓名。
2、列出2门以上（含2门）不及格学生姓名及平均成绩。
3、即学过1号课程又学过2号课所有学生的姓名。

create table s(
	sno int(4) primary key auto_increment,
	sname varchar(32)
);

insert into s(sname) values('zhangsan');
insert into s(sname) values('lisi');
insert into s(sname) values('wangwu');
insert into s(sname) values('zhaoliu');

create table c(
	cno int(4) primary key auto_increment,
	cname varchar(32),
	cteacher varchar(32)
);
insert into c(cname,cteacher) values('Java','吴老师');
insert into c(cname,cteacher) values('C++','王老师');
insert into c(cname,cteacher) values('C##','张老师');
insert into c(cname,cteacher) values('MySQL','郭老师');
insert into c(cname,cteacher) values('Oracle','黎明');


create table sc(
	sno int(4),
	cno int(4),
	scgrade double(3,1),
	constraint sc_sno_cno_pk primary key(sno,cno),
	constraint sc_sno_fk foreign key(sno) references s(sno),
	constraint sc_cno_fk foreign key(cno) references c(cno)
);

insert into sc(sno,cno,scgrade) values(1,1,30);
insert into sc(sno,cno,scgrade) values(1,2,50);
insert into sc(sno,cno,scgrade) values(1,3,80);
insert into sc(sno,cno,scgrade) values(1,4,90);
insert into sc(sno,cno,scgrade) values(1,5,70);
insert into sc(sno,cno,scgrade) values(2,2,80);
insert into sc(sno,cno,scgrade) values(2,3,50);
insert into sc(sno,cno,scgrade) values(2,4,70);
insert into sc(sno,cno,scgrade) values(2,5,80);
insert into sc(sno,cno,scgrade) values(3,1,60);
insert into sc(sno,cno,scgrade) values(3,2,70);
insert into sc(sno,cno,scgrade) values(3,3,80);
insert into sc(sno,cno,scgrade) values(4,3,50);
insert into sc(sno,cno,scgrade) values(4,4,80);


/*
1、找出没选过“黎明”老师的所有学生姓名。
2、列出2门以上（含2门）不及格学生姓名及平均成绩。
3、即学过1号课程又学过2号课所有学生的姓名。                          
*/

--先找出选过黎明老师的学生编号 -> 黎明老师的授课的编号
select cno from c where cteacher = '黎明';

select sno from sc where cno = (select cno from c where cteacher = '黎明');

select * from s where sno not in(select sno from sc where cno = (select cno from c where cteacher = '黎明'));

--列出2门以上（含2门）不及格学生姓名及平均成绩
t1
select 
       sc.sno,s.sname,count(*) as studentNum
from 
     sc 
join
    s
on
     sc.sno = s.sno
where 
      scgrade < 60
group by
      sc.sno,s.sname
having
      studentNum >= 2;

t2
select 
       sc.sno,avg(sc.scgrade) as avgscgrade
from
       sc
group by
      sc.sno;
      

select 
       t1.sname,t2.avgscgrade
from
       (select 
               sc.sno,s.sname,count(*) as studentNum
        from 
             sc 
        join
            s
        on
             sc.sno = s.sno
        where 
              scgrade < 60
        group by
              sc.sno,s.sname
        having
              studentNum >= 2) t1
join
       (select 
               sc.sno,avg(sc.scgrade) as avgscgrade
        from
               sc
        group by
              sc.sno) t2
on
       t1.sno = t2.sno;

--即学过1号课程又学过2号课所有学生的姓名
select sno from sc where cno = 1;
select sno from sc where cno = 2;

select 
       s.sname
from 
       sc 
join
       s
on
       sc.sno = s.sno
where 
      cno = 1 and sc.sno in(select sno from sc where cno = 2);

## 14.列出所有员工及领导的名字

select
	e.ename,
	b.ename as leadername
from
	emp e
left join
	emp b
on
	e.mgr = b.empno;
+--------+------------+
| ename  | leadername |
+--------+------------+
| SMITH  | FORD       |
| ALLEN  | BLAKE      |
| WARD   | BLAKE      |
| JONES  | KING       |
| MARTIN | BLAKE      |
| BLAKE  | KING       |
| CLARK  | KING       |
| SCOTT  | JONES      |
| KING   | NULL       |
| TURNER | BLAKE      |
| ADAMS  | SCOTT      |
| JAMES  | BLAKE      |
| FORD   | JONES      |
| MILLER | CLARK      |
+--------+------------+

## 15.列出受雇日期早于其直接上级的所有员工编号、姓名、部门名称

select 
	d.dname,
	e.empno,
	e.ename
from
	emp e
join
	emp b
on
	e.mgr = b.empno
join
	dept d
on
	e.deptno = d.deptno
where
	e.hiredate < b.hiredate;
+------------+-------+-------+
| dname      | empno | ename |
+------------+-------+-------+
| ACCOUNTING |  7782 | CLARK |
| RESEARCH   |  7369 | SMITH |
| RESEARCH   |  7566 | JONES |
| SALES      |  7499 | ALLEN |
| SALES      |  7521 | WARD  |
| SALES      |  7698 | BLAKE |
+------------+-------+-------+

## 16.列出部门名称和这些部门的员工信息，同时列出那些没有员工的部门

select 
	d.dname,
	e.*
from
	emp e
right join
	dept d
on
	e.deptno = d.deptno;
+------------+-------+--------+-----------+------+------------+---------+---------+--------+
| dname      | EMPNO | ENAME  | JOB       | MGR  | HIREDATE   | SAL     | COMM    | DEPTNO |
+------------+-------+--------+-----------+------+------------+---------+---------+--------+
| ACCOUNTING |  7782 | CLARK  | MANAGER   | 7839 | 1981-06-09 | 2450.00 |    NULL |     10 |
| ACCOUNTING |  7839 | KING   | PRESIDENT | NULL | 1981-11-17 | 5000.00 |    NULL |     10 |
| ACCOUNTING |  7934 | MILLER | CLERK     | 7782 | 1982-01-23 | 1300.00 |    NULL |     10 |
| RESEARCH   |  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |
| RESEARCH   |  7566 | JONES  | MANAGER   | 7839 | 1981-04-02 | 2975.00 |    NULL |     20 |
| RESEARCH   |  7788 | SCOTT  | ANALYST   | 7566 | 1987-04-19 | 3000.00 |    NULL |     20 |
| RESEARCH   |  7876 | ADAMS  | CLERK     | 7788 | 1987-05-23 | 1100.00 |    NULL |     20 |
| RESEARCH   |  7902 | FORD   | ANALYST   | 7566 | 1981-12-03 | 3000.00 |    NULL |     20 |
| SALES      |  7499 | ALLEN  | SALESMAN  | 7698 | 1981-02-20 | 1600.00 |  300.00 |     30 |
| SALES      |  7521 | WARD   | SALESMAN  | 7698 | 1981-02-22 | 1250.00 |  500.00 |     30 |
| SALES      |  7654 | MARTIN | SALESMAN  | 7698 | 1981-09-28 | 1250.00 | 1400.00 |     30 |
| SALES      |  7698 | BLAKE  | MANAGER   | 7839 | 1981-05-01 | 2850.00 |    NULL |     30 |
| SALES      |  7844 | TURNER | SALESMAN  | 7698 | 1981-09-08 | 1500.00 |    0.00 |     30 |
| SALES      |  7900 | JAMES  | CLERK     | 7698 | 1981-12-03 |  950.00 |    NULL |     30 |
| OPERATIONS |  NULL | NULL   | NULL      | NULL | NULL       |    NULL |    NULL |   NULL |
+------------+-------+--------+-----------+------+------------+---------+---------+--------+

## 17.列出至少有5个员工的所有部门

第一步：先求出每个部门的员工数量
select 
	e.deptno,count(e.ename) as totalEmp
from
	emp e
group by
	e.deptno;
+--------+----------+
| deptno | totalEmp |
+--------+----------+
|     10 |        3 |
|     20 |        5 |
|     30 |        6 |
+--------+----------+

select 
	e.deptno,count(e.ename) as totalEmp
from
	emp e
group by
	e.deptno
having
	totalEmp >= 5;
+--------+----------+
| deptno | totalEmp |
+--------+----------+
|     20 |        5 |
|     30 |        6 |
+--------+----------+

## 18.列出薪水比“SMITH”多的所有员工信息

select sal from emp where ename = 'SMITH';
+--------+
| sal    |
+--------+
| 800.00 |
+--------+
select * from emp where sal > (select sal from emp where ename = 'SMITH');
+-------+--------+-----------+------+------------+---------+---------+--------+
| EMPNO | ENAME  | JOB       | MGR  | HIREDATE   | SAL     | COMM    | DEPTNO |
+-------+--------+-----------+------+------------+---------+---------+--------+
|  7499 | ALLEN  | SALESMAN  | 7698 | 1981-02-20 | 1600.00 |  300.00 |     30 |
|  7521 | WARD   | SALESMAN  | 7698 | 1981-02-22 | 1250.00 |  500.00 |     30 |
|  7566 | JONES  | MANAGER   | 7839 | 1981-04-02 | 2975.00 |    NULL |     20 |
|  7654 | MARTIN | SALESMAN  | 7698 | 1981-09-28 | 1250.00 | 1400.00 |     30 |
|  7698 | BLAKE  | MANAGER   | 7839 | 1981-05-01 | 2850.00 |    NULL |     30 |
|  7782 | CLARK  | MANAGER   | 7839 | 1981-06-09 | 2450.00 |    NULL |     10 |
|  7788 | SCOTT  | ANALYST   | 7566 | 1987-04-19 | 3000.00 |    NULL |     20 |
|  7839 | KING   | PRESIDENT | NULL | 1981-11-17 | 5000.00 |    NULL |     10 |
|  7844 | TURNER | SALESMAN  | 7698 | 1981-09-08 | 1500.00 |    0.00 |     30 |
|  7876 | ADAMS  | CLERK     | 7788 | 1987-05-23 | 1100.00 |    NULL |     20 |
|  7900 | JAMES  | CLERK     | 7698 | 1981-12-03 |  950.00 |    NULL |     30 |
|  7902 | FORD   | ANALYST   | 7566 | 1981-12-03 | 3000.00 |    NULL |     20 |
|  7934 | MILLER | CLERK     | 7782 | 1982-01-23 | 1300.00 |    NULL |     10 |
+-------+--------+-----------+------+------------+---------+---------+--------+

## 19.列出所有“CLERK”（办事员）的姓名及其部门名称，部门人数

select 
	d.deptno,d.dname,e.ename
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
where
	e.job = 'CLERK';
t1
+--------+------------+--------+
| deptno | dname      | ename  |
+--------+------------+--------+
|     10 | ACCOUNTING | MILLER | 3
|     20 | RESEARCH   | SMITH  | 5
|     20 | RESEARCH   | ADAMS  | 5
|     30 | SALES      | JAMES  | 6
+--------+------------+--------+

求出每个部门的员工数量
select
	e.deptno,count(e.ename) as totalEmp
from
	emp e
group by
	e.deptno;
t2
+--------+----------+
| deptno | totalEmp |
+--------+----------+
|     10 |        3 |
|     20 |        5 |
|     30 |        6 |
+--------+----------+


select 
	t1.deptno,t1.dname,t1.ename,t2.totalEmp
from
	(select 
		d.deptno,d.dname,e.ename
	from
		emp e
	join
		dept d
	on
		e.deptno = d.deptno
	where
		e.job = 'CLERK') t1
join
	(select
		e.deptno,count(e.ename) as totalEmp
	from
		emp e
	group by
		e.deptno) t2
on
	t1.deptno = t2.deptno;

+--------+------------+--------+----------+
| deptno | dname      | ename  | totalEmp |
+--------+------------+--------+----------+
|     10 | ACCOUNTING | MILLER |        3 |
|     20 | RESEARCH   | SMITH  |        5 |
|     20 | RESEARCH   | ADAMS  |        5 |
|     30 | SALES      | JAMES  |        6 |
+--------+------------+--------+----------+

## 20.列出最低薪水大于1500的各种工作及从事此工作的全部雇员人数

第一步：先求出每种工作岗位的最低薪水
select 
	e.job,min(e.sal) as minsal
from
	emp e
group by
	e.job;
+-----------+---------+
| job       | minsal  |
+-----------+---------+
| ANALYST   | 3000.00 |
| CLERK     |  800.00 |
| MANAGER   | 2450.00 |
| PRESIDENT | 5000.00 |
| SALESMAN  | 1250.00 |
+-----------+---------+

select 
	e.job,min(e.sal) as minsal,count(e.ename) as totalEmp
from
	emp e
group by
	e.job
having
	minsal > 1500;
+-----------+---------+
| job       | minsal  |
+-----------+---------+
| ANALYST   | 3000.00 |
| MANAGER   | 2450.00 |
| PRESIDENT | 5000.00 |
+-----------+---------+
+-----------+---------+----------+
| job       | minsal  | totalEmp |
+-----------+---------+----------+
| ANALYST   | 3000.00 |        2 |
| MANAGER   | 2450.00 |        3 |
| PRESIDENT | 5000.00 |        1 |
+-----------+---------+----------+

## 21.列出在部门“SALES”<销售部>工作的员工的姓名，假定不知道销售部门的部门编号

select deptno from dept where dname = 'SALES';
+--------+
| deptno |
+--------+
|     30 |
+--------+


select ename from emp where deptno = (select deptno from dept where dname = 'SALES');
+--------+
| ename  |
+--------+
| ALLEN  |
| WARD   |
| MARTIN |
| BLAKE  |
| TURNER |
| JAMES  |
+--------+

## 22.列出薪金高于公司平均薪金的所有员工，所在部门、上级领导、雇员的工资等级

第一步：求出公司的平均薪水
select avg(sal) as avgsal from emp;
+-------------+
| avgsal      |
+-------------+
| 2073.214286 |
+-------------+

select 
	d.dname,
	e.ename,
	b.ename as leadername,
	s.grade
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
left join
	emp b
on
	e.mgr = b.empno
join
	salgrade s
on
	e.sal between s.losal and s.hisal
where
	e.sal > (select avg(sal) as avgsal from emp);
+------------+-------+------------+-------+
| dname      | ename | leadername | grade |
+------------+-------+------------+-------+
| RESEARCH   | JONES | KING       |     4 |
| SALES      | BLAKE | KING       |     4 |
| ACCOUNTING | CLARK | KING       |     4 |
| RESEARCH   | SCOTT | JONES      |     4 |
| ACCOUNTING | KING  | NULL       |     5 |
| RESEARCH   | FORD  | JONES      |     4 |
+------------+-------+------------+-------+

## 23.列出与“SCOTT”从事相同工作的所有员工及部门名称

查询出SCOTT的工作岗位
select job from emp where ename = 'SCOTT';
+---------+
| job     |
+---------+
| ANALYST |
+---------+

select 
	d.dname,
	e.*
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
where
	e.job = (select job from emp where ename = 'SCOTT');
+----------+-------+-------+---------+------+------------+---------+------+--------+
| dname    | EMPNO | ENAME | JOB     | MGR  | HIREDATE   | SAL     | COMM | DEPTNO |
+----------+-------+-------+---------+------+------------+---------+------+--------+
| RESEARCH |  7788 | SCOTT | ANALYST | 7566 | 1987-04-19 | 3000.00 | NULL |     20 |
| RESEARCH |  7902 | FORD  | ANALYST | 7566 | 1981-12-03 | 3000.00 | NULL |     20 |
+----------+-------+-------+---------+------+------------+---------+------+--------+

## 24.列出薪金等于部门30中员工的薪金的其它员工的姓名和薪金

select distinct sal from emp where deptno = 30;
+---------+
| sal     |
+---------+
| 1600.00 |
| 1250.00 |
| 2850.00 |
| 1500.00 |
|  950.00 |
+---------+

select ename,sal from emp where sal in(select distinct sal from emp where deptno = 30) and deptno <> 30;

## 25.列出薪金高于在部门30工作的所有员工的薪金的员工姓名和薪金、部门名称

第一步：先找出部门30的最高薪水
select max(sal) as maxsal from emp where deptno = 30;
+---------+
| maxsal  |
+---------+
| 2850.00 |
+---------+

select 
	d.dname,
	e.ename,
	e.sal
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
where
	e.sal > (select max(sal) as maxsal from emp where deptno = 30);
+------------+-------+---------+
| dname      | ename | sal     |
+------------+-------+---------+
| ACCOUNTING | KING  | 5000.00 |
| RESEARCH   | JONES | 2975.00 |
| RESEARCH   | SCOTT | 3000.00 |
| RESEARCH   | FORD  | 3000.00 |
+------------+-------+---------+

## 26.列出在每个部门工作的员工数量、平均工资和平均服务期限

to_days(日期类型) -> 天数
获取数据库的系统当前时间的函数是:now()

select ename,(to_days(now()) - to_days(hiredate))/365 as serveryear from emp;
select avg((to_days(now()) - to_days(hiredate))/365) as avgserveryear from emp;

select	
	e.deptno,
	count(e.ename) as totalEmp,
	avg(e.sal) as avgsal,
	avg((to_days(now()) - to_days(hiredate))/365) as avgserveryear
from
	emp e
group by
	e.deptno;
+--------+----------+-------------+---------------+
| deptno | totalEmp | avgsal      | avgserveryear |
+--------+----------+-------------+---------------+
|     10 |        3 | 2916.666667 |   34.90503333 |
|     20 |        5 | 2175.000000 |   32.93206000 |
|     30 |        6 | 1566.666667 |   35.20365000 |
+--------+----------+-------------+---------------+

## 27.列出所有员工的姓名、部门名称和工资

select
	d.dname,
	e.ename,
	e.sal
from
	emp e
right join
	dept d
on
	e.deptno = d.deptno;
+------------+--------+---------+
| dname      | ename  | sal     |
+------------+--------+---------+
| ACCOUNTING | CLARK  | 2450.00 |
| ACCOUNTING | KING   | 5000.00 |
| ACCOUNTING | MILLER | 1300.00 |
| RESEARCH   | SMITH  |  800.00 |
| RESEARCH   | JONES  | 2975.00 |
| RESEARCH   | SCOTT  | 3000.00 |
| RESEARCH   | ADAMS  | 1100.00 |
| RESEARCH   | FORD   | 3000.00 |
| SALES      | ALLEN  | 1600.00 |
| SALES      | WARD   | 1250.00 |
| SALES      | MARTIN | 1250.00 |
| SALES      | BLAKE  | 2850.00 |
| SALES      | TURNER | 1500.00 |
| SALES      | JAMES  |  950.00 |
| OPERATIONS | NULL   |    NULL |
+------------+--------+---------+

## 28.列出所有部门的详细信息和人数

select 
	d.deptno,d.dname,d.loc,count(e.ename) as totalEmp
from
	emp e
right join
	dept d
on
	e.deptno = d.deptno
group by
	d.deptno,d.dname,d.loc;
+--------+------------+----------+----------+
| deptno | dname      | loc      | totalEmp |
+--------+------------+----------+----------+
|     10 | ACCOUNTING | NEW YORK |        3 |
|     20 | RESEARCH   | DALLAS   |        5 |
|     30 | SALES      | CHICAGO  |        6 |
|     40 | OPERATIONS | BOSTON   |        0 |
+--------+------------+----------+----------+

## 29.列出各种工作的最低工资及从事此工作的雇员姓名

select 
	e.job,min(e.sal) as minsal
from
	emp e
group by 
	e.job;
+-----------+---------+
| job       | minsal  |
+-----------+---------+
| ANALYST   | 3000.00 |
| CLERK     |  800.00 |
| MANAGER   | 2450.00 |
| PRESIDENT | 5000.00 |
| SALESMAN  | 1250.00 |
+-----------+---------+

将以上查询结果当成临时表t(job,minsal)
select 
	e.ename
from
	emp e
join
	(select 
		e.job,min(e.sal) as minsal
	from
		emp e
	group by 
		e.job) t
on
	e.job = t.job
where
	e.sal = t.minsal;

+--------+
| ename  |
+--------+
| SMITH  |
| WARD   |
| MARTIN |
| CLARK  |
| SCOTT  |
| KING   |
| FORD   |
+--------+

## 30.列出各个部门MANAGER的最低薪金

select 
	e.deptno,min(e.sal) as minsal
from
	emp e
where
	e.job = 'MANAGER'
group by
	e.deptno;
+--------+---------+
| deptno | minsal  |
+--------+---------+
|     10 | 2450.00 |
|     20 | 2975.00 |
|     30 | 2850.00 |
+--------+---------+

## 31.列出所有员工的年工资，按年薪从低到高排序

select ename,(sal+ifnull(comm,0))*12 as yearsal from emp order by yearsal asc;
+--------+----------+
| ename  | yearsal  |
+--------+----------+
| SMITH  |  9600.00 |
| JAMES  | 11400.00 |
| ADAMS  | 13200.00 |
| MILLER | 15600.00 |
| TURNER | 18000.00 |
| WARD   | 21000.00 |
| ALLEN  | 22800.00 |
| CLARK  | 29400.00 |
| MARTIN | 31800.00 |
| BLAKE  | 34200.00 |
| JONES  | 35700.00 |
| FORD   | 36000.00 |
| SCOTT  | 36000.00 |
| KING   | 60000.00 |
+--------+----------+

## 32.求出员工领导的薪水超过3000的员工名称和领导名称

select 
	e.ename,
	b.ename as leadername
from
	emp e
join
	emp b
on
	e.mgr = b.empno
where
	b.sal > 3000;
+-------+------------+
| ename | leadername |
+-------+------------+
| JONES | KING       |
| BLAKE | KING       |
| CLARK | KING       |
+-------+------------+

## 33.求部门名称中带“S”字符的部门员工的工资合计、部门人数

select
	d.dname,
	sum(e.sal) as sumsal,
	count(e.ename) as totalEmp
from
	emp e
join
	dept d
on
	e.deptno = d.deptno
where
	d.dname like '%s%'
group by
	d.dname;
+----------+----------+----------+
| dname    | sumsal   | totalEmp |
+----------+----------+----------+
| RESEARCH | 10875.00 |        5 |
| SALES    |  9400.00 |        6 |
+----------+----------+----------+

## 34.给任职日期超过30年的员工加薪10%

update emp_bak1 set sal = sal * 1.1 where (to_days(now()) - to_days(hiredate))/365 > 30;