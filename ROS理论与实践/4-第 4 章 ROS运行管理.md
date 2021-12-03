# ROS理论与实践

# 第 4 章 ROS运行管理

ROS是多进程(节点)的分布式框架，一个完整的ROS系统实现：

> 可能包含多台主机；
> 每台主机上又有多个工作空间(workspace)；
> 每个的工作空间中又包含多个功能包(package)；
> 每个功能包又包含多个节点(Node)，不同的节点都有自己的节点名称；
> 每个节点可能还会设置一个或多个话题(topic)...

![img](http://www.autolabor.com.cn/book/ROSTutorials/assets/%E6%96%87%E4%BB%B6%E7%B3%BB%E7%BB%9F.jpg)

在多级层深的ROS系统中，其实现与维护可能会出现一些问题，比如，如何关联不同的功能包，繁多的ROS节点应该如何启动？功能包、节点、话题、参数重名时应该如何处理？不同主机上的节点如何通信？

本章主要内容介绍在ROS中上述问题的解决策略(见本章目录)，预期达成学习目标也与上述问题对应：

- 掌握元功能包使用语法；
- 掌握launch文件的使用语法；
- 理解什么是ROS工作空间覆盖，以及存在什么安全隐患；
- 掌握节点名称重名时的处理方式；
- 掌握话题名称重名时的处理方式；
- 掌握参数名称重名时的处理方式；
- 能够实现ROS分布式通信。

## 4.1 ROS元功能包

> **场景:**完成ROS中一个系统性的功能，可能涉及到多个功能包，比如实现了机器人导航模块，该模块下有地图、定位、路径规划...等不同的子级功能包。那么调用者安装该模块时，需要逐一的安装每一个功能包吗？

显而易见的，逐一安装功能包的效率低下，在ROS中，提供了一种方式可以将不同的功能包打包成一个功能包，当安装某个功能模块时，直接调用打包后的功能包即可，该包又称之为元功能包(metapackage)。

------

#### 概念

MetaPackage是Linux的一个文件管理系统的概念。是ROS中的一个虚包，里面没有实质性的内容，但是它依赖了其他的软件包，通过这种方法可以把其他包组合起来，我们可以认为它是一本书的目录索引，告诉我们这个包集合中有哪些子包，并且该去哪里下载。

例如：

- sudo apt install ros-noetic-desktop-full 命令安装ros时就使用了元功能包，该元功能包依赖于ROS中的其他一些功能包，安装该包时会一并安装依赖。

还有一些常见的MetaPackage：navigation moveit! turtlebot3 ....

#### 作用

方便用户的安装，我们只需要这一个包就可以把其他相关的软件包组织到一起安装了。

#### 实现

**首先:**新建一个功能包（元功能包是一个虚包，不需要依赖其他包，如 rospy、roscpp、std_msgs）

**然后:**修改**package.xml** ,内容如下:

```xml
 <exec_depend>被集成的功能包</exec_depend>
 .....
 <export>
   <metapackage />
 </export>
```

**最后:**修改 CMakeLists.txt,内容如下：（整个文件只有如下 4 行）（第二行 demo 需替换成元功能包包名）

```cmake
cmake_minimum_required(VERSION 3.0.2)
project(demo)
find_package(catkin REQUIRED)
catkin_metapackage()
```

PS:CMakeLists.txt 中不可以有换行。

------

**另请参考:**

- http://wiki.ros.org/catkin/package.xml#Metapackages

## 4.2 ROS节点运行管理launch文件

关于 launch 文件的使用我们已经不陌生了，在第一章内容中，就曾经介绍到:

> 一个程序中可能需要启动多个节点，比如:ROS 内置的小乌龟案例，如果要控制乌龟运动，要启动多个窗口，分别启动 roscore、乌龟界面节点、键盘控制节点。如果每次都调用 rosrun 逐一启动，显然效率低下，如何优化?

采用的优化策略便是使用roslaunch 命令集合 launch 文件启动管理节点，并且在后续教程中，也多次使用到了 launch 文件。

------

#### **概念**

launch 文件是一个 XML 格式的文件，可以启动本地和远程的多个节点，还可以在参数服务器中设置参数。

#### **作用**

简化节点的配置与启动，提高ROS程序的启动效率。

#### **使用**

以 turtlesim 为例演示

**0.创建功能包**，加入功能包依赖 turtlesim ，还可加入 roscpp、rospy、std_msgs 等功能包

##### 1.新建launch文件

在功能包下添加 launch目录, 目录下新建 xxxx.launch 文件，编辑 launch 文件

```xml
<launch>
    <node pkg="turtlesim" type="turtlesim_node"     name="myTurtle" output="screen" />
    <node pkg="turtlesim" type="turtle_teleop_key"  name="myTurtleContro" output="screen" />
</launch>
```

##### 2.调用 launch 文件

```shell
roslaunch 包名 xxx.launch
```

**注意:**roslaunch 命令执行launch文件时，首先会判断是否启动了 roscore,如果启动了，则不再启动，否则，会自动调用 roscore

**PS:**本节主要介绍launch文件的使用语法，launch 文件中的标签，以及不同标签的一些常用属性。

------

**另请参考:**

- http://wiki.ros.org/roslaunch/XML

### 4.2.1 launch文件标签之launch

`<launch>`标签是所有 launch 文件的根标签，充当其他标签的容器

#### 1.属性

- `deprecated = "弃用声明"`

    告知用户当前 launch 文件已经弃用

#### 2.子级标签

所有其它标签都是launch的子级

### 4.2.2 launch文件标签之node

`<node>`标签用于指定 ROS 节点，是最常见的标签，需要注意的是: roslaunch 命令不能保证按照 node 的声明顺序来启动节点(节点的启动是多进程的)

#### 1.属性

- pkg="包名"

    节点所属的包

- type="nodeType"

    节点类型(与之相同名称的可执行文件)

- name="nodeName"

    节点名称(在 ROS 网络拓扑中节点的名称)

- args="xxx xxx xxx" (可选)

    将参数传递给节点

- machine="机器名"

    在指定机器上启动节点

- respawn="true | false" (可选)

    如果节点退出，是否自动重启

- respawn_delay=" N" (可选)

    如果 respawn 为 true, 那么延迟 N 秒后启动节点

- required="true | false" (可选)

    该节点是否必须，如果为 true,那么如果该节点退出，将杀死整个 roslaunch

- ns="xxx" (可选)

    在指定命名空间 xxx 中启动节点，加入 ns 后，节点名称变为 `/ns/节点名`，即添加了命名空间前缀

- clear_params="true | false" (可选)

    在启动前，删除节点的私有空间的所有参数，慎用

- output="log | screen" (可选)

    日志发送目标，可以设置为 log 日志文件，或 screen 屏幕,默认是 log

#### 2.子级标签

- env 环境变量设置
- remap 重映射节点名称
- rosparam 参数设置
- param 参数设置

### 4.2.3 launch文件标签之include

`include`标签用于将另一个 xml 格式的 launch 文件导入到当前文件

#### 1.属性

- file="$(find 包名)/xxx/xxx.launch"

    要包含的文件路径

- ns="xxx" (可选)

    在指定命名空间导入文件

#### 2.子级标签

- env 环境变量设置
- arg 将参数传递给被包含的文件

### 4.2.4 launch文件标签之remap

用于话题重命名

#### 1.属性

- from="xxx"

    原始话题名称

- to="yyy"

    目标名称

#### 2.子级标签

- 无

**示例：**默认键盘控制乌龟运动，修改之后，话题改变，turtlesim 内部使用键盘控制乌龟不再可行

```xml
<launch>
    <node pkg="turtlesim" type="turtlesim_node"     name="myTurtle" output="screen" >
		<ramp from="/turtle/cmd_vel" to="cmd/vel"/>
    </node>
    <node pkg="turtlesim" type="turtle_teleop_key"  name="myTurtleContro" output="screen" />
</launch>
```

### 4.2.5 launch文件标签之param

`<param>`标签主要用于在参数服务器上设置参数，参数源可以在标签中通过 value 指定，也可以通过外部文件加载，在`<node>`标签中时，相当于私有命名空间。

#### 1.属性

- name="命名空间/参数名"

    参数名称，可以包含命名空间

- value="xxx" (可选)

    定义参数值，如果此处省略，必须指定外部文件作为参数源

- type="str | int | double | bool | yaml" (可选)

    指定参数类型，如果未指定，roslaunch 会尝试确定参数类型，规则如下:

    - 如果包含 '.' 的数字解析未浮点型，否则为整型
    - "true" 和 "false" 是 bool 值(不区分大小写)
    - 其他是字符串

#### 2.子级标签

- 无

**示例：**

```xml
<launch>
    <!-- 格式1：launch 下，node 外 -->
    <param name="param_A" type="int" value="100" />
    <node pkg="turtlesim" type="turtlesim_node"     name="myTurtle" output="screen" >
		<ramp from="/turtle/cmd_vel" to="cmd/vel"/>
	    <!-- 格式2：node 下 -->
    	<param name="param_B" type="double" value="3.14" />
    </node>
    <node pkg="turtlesim" type="turtle_teleop_key"  name="myTurtleContro" output="screen" />
</launch>
```

查看参数：

```shell
rosparam list

/param_A
/myTurtle/param_B	# 加入了命名空间
...
```

### 4.2.6 launch文件标签之rosparam

`<rosparam>`标签可以从 YAML 文件导入参数，或将参数导出到 YAML 文件，也可以用来删除参数，`<rosparam>`标签在`<node>`标签中时被视为私有。

#### 1.属性

- command="load | dump | delete" (可选，默认 load)

    加载、导出或删除参数

- file="$(find xxxxx)/xxx/yyy...."

    加载或导出到的 yaml 文件

- param="参数名称"

- ns="命名空间" (可选)

#### 2.子级标签

- 无

**示例：**

```xml
<launch>
    <!-- 格式1：launch 下，node 外 -->
    <rosparam command="load" file="$(find launch01_basic)/launch/params.ymal" />
    <node pkg="turtlesim" type="turtlesim_node"     name="myTurtle" output="screen" >
		<ramp from="/turtle/cmd_vel" to="cmd/vel"/>
	    <!-- 格式2：node 下 -->
    	<rosparam command="load" file="$(find launch01_basic)/launch/params.ymal" />
    </node>
    <node pkg="turtlesim" type="turtle_teleop_key"  name="myTurtleContro" output="screen" />

	<!-- 删除操作 -->
	<rosparam command="delete" param="bg_B" />
</launch>
```

与 `param` 一样，两种方式加载参数会使命名空间不一致。

导出参数操作，新建一个 launch 文件，在里面写入如下代码：

```xml
<launch>
	<rosparam command="dump" file="$(find launch01_basic)/launch/params_out.ymal" />
</launch>
```

### 4.2.7 launch文件标签之group

`<group>`标签可以对节点分组，具有 ns 属性，可以让节点归属某个命名空间

#### 1.属性

- ns="名称空间" (可选)

- clear_params="true | false" (可选)

    启动前，是否删除组名称空间的所有参数(慎用....此功能危险)

#### 2.子级标签

- 除了launch 标签外的其他标签

```xml
<launch>
    <group ns="namespace_group">
	    <node pkg="turtlesim" type="turtlesim_node"     name="myTurtle" output="screen" />
    	<node pkg="turtlesim" type="turtle_teleop_key"  name="myTurtleContro" output="screen" />
    </group>
</launch>
```

查看参数：

```shell
rosparam list

/namespace_group/myTurtle	# 加入了命名空间
/namespace_group/myTurtleContro
...
```

### 4.2.8 launch文件标签之arg

`<arg>`标签是用于动态传参，类似于函数的参数，可以增强launch文件的灵活性

#### 1.属性

- name="参数名称"

- default="默认值" (可选)

- value="数值" (可选)

    不可以与 default 并存

- doc="描述"

    参数说明

#### 2.子级标签

- 无

#### 3.示例

- launch文件传参语法实现,hello.lcaunch

    ```xml
    <launch>
        <arg name="xxx" />
        <param name="param" value="$(arg xxx)" />
    </launch>
    ```

- 命令行调用launch传参

    ```shell
    roslaunch hello.launch xxx:=值
    ```

## 4.3 ROS工作空间覆盖

所谓工作空间覆盖，是指不同工作空间中，存在重名的功能包的情形。

> ROS 开发中，会自定义工作空间且自定义工作空间可以同时存在多个，可能会出现一种情况: 虽然特定工作空间内的功能包不能重名，但是自定义工作空间的功能包与内置的功能包可以重名或者不同的自定义的工作空间中也可以出现重名的功能包，那么调用该名称功能包时，会调用哪一个呢？比如：自定义工作空间A存在功能包 turtlesim，自定义工作空间B也存在功能包 turtlesim，当然系统内置空间也存在turtlesim，如果调用turtlesim包，会调用哪个工作空间中的呢？

------

#### **实现**

0.新建工作空间A与工作空间B，两个工作空间中都创建功能包: turtlesim。

1.在 ~/.bashrc 文件下**追加**当前工作空间的 bash 格式如下:

```shell
source /home/用户/路径/工作空间A/devel/setup.bash
source /home/用户/路径/工作空间B/devel/setup.bash
```

2.新开命令行:`source .bashrc`加载环境变量

3.查看ROS环境环境变量`echo $ROS_PACKAGE_PATH`

结果:自定义工作空间B:自定义空间A:系统内置空间

4.调用命令:`roscd turtlesim`会进入自定义工作空间B

#### **原因**

ROS 会解析 .bashrc 文件，并生成 ROS_PACKAGE_PATH ROS包路径，该变量中按照 .bashrc 中配置设置工作空间优先级，在设置时需要遵循一定的原则:ROS_PACKAGE_PATH 中的值，和 .bashrc 的配置顺序相反--->后配置的优先级更高，如果更改自定义空间A与自定义空间B的source顺序，那么调用时，将进入工作空间A。

#### **结论**

功能包重名时，会按照 ROS_PACKAGE_PATH 查找，配置在前的会优先执行。

#### **隐患**

存在安全隐患，比如当前工作空间B优先级更高，意味着当程序调用 turtlesim 时，不会调用工作空间A也不会调用系统内置的 turtlesim，如果工作空间A在实现时有其他功能包依赖于自身的 turtlesim，而按照ROS工作空间覆盖的涉及原则，那么实际执行时将会调用工作空间B的turtlesim，从而导致执行异常，出现安全隐患。

------

BUG 说明:

> 当在 .bashrc 文件中 source 多个工作空间后，可能出现的情况，在 ROS PACKAGE PATH 中只包含两个工作空间，可以删除自定义工作空间的 build 与 devel 目录，重新 catkin_make，然后重新载入 .bashrc 文件，问题解决。

