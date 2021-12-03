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

## 4.4 ROS节点名称重名

> 场景:ROS 中创建的节点是有名称的，C++初始化节点时通过API:`ros::init(argc,argv,"xxxx");`来定义节点名称，在Python中初始化节点则通过 `rospy.init_node("yyyy")` 来定义节点名称。在ROS的网络拓扑中，是不可以出现重名的节点的，因为假设可以重名存在，那么调用时会产生混淆，这也就意味着，不可以启动重名节点或者同一个节点启动多次，的确，在ROS中如果启动重名节点的话，之前已经存在的节点会被直接关闭，但是如果有这种需求的话，怎么优化呢？

在ROS中给出的解决策略是使用命名空间或名称重映射。

------

命名空间就是为名称添加前缀，名称重映射是为名称起别名。这两种策略都可以解决节点重名问题，两种策略的实现途径有多种:

- rosrun 命令
- launch 文件
- 编码实现

以上三种途径都可以通过命名空间或名称重映射的方式，来避免节点重名，本节将对三者的使用逐一演示，三者要实现的需求类似。

#### 案例

启动两个 turtlesim_node 节点，当然如果直接打开两个终端，直接启动，那么第一次启动的节点会关闭，并给出提示:

```shell
[ WARN] [1578812836.351049332]: Shutdown request received.
[ WARN] [1578812836.351207362]: Reason given for shutdown: [new node registered with same name]
```

因为两个节点不能重名，接下来将会介绍解决重名问题的多种方案。

### 4.4.1 rosrun设置命名空间与重映射

#### 1.rosrun设置命名空间

##### 1.1设置命名空间演示

语法: rosrun 包名 节点名 __ns:=新名称

```shell
rosrun turtlesim turtlesim_node __ns:=/xxx
rosrun turtlesim turtlesim_node __ns:=/yyy
```

两个节点都可以正常运行

##### 1.2运行结果

`rosnode list`查看节点信息,显示结果:

```shell
/xxx/turtlesim
/yyy/turtlesim
```

#### 2.rosrun名称重映射

##### 2.1为节点起别名

语法: rosrun 包名 节点名 __name:=新名称

```shell
rosrun turtlesim  turtlesim_node __name:=t1 
# 或者
rosrun turtlesim   turtlesim_node /turtlesim:=t1(不适用于python)

rosrun turtlesim  turtlesim_node __name:=t2 
# 或者
rosrun turtlesim   turtlesim_node /turtlesim:=t2(不适用于python)
```

两个节点都可以运行

##### 2.2运行结果

`rosnode list`查看节点信息,显示结果:

```shell
/t1
/t2
```

#### 3.rosrun命名空间与名称重映射叠加

##### 3.1设置命名空间同时名称重映射

语法: rosrun 包名 节点名 __ns:=新名称 __name:=新名称

```shell
rosrun turtlesim turtlesim_node __ns:=/xxx __name:=tn
```

##### 3.2运行结果

`rosnode list`查看节点信息,显示结果:

```shell
/xxx/tn
```

> 使用环境变量也可以设置命名空间,启动节点前在终端键入如下命令:
>
> export ROS_NAMESPACE=xxxx

### 4.4.2 launch文件设置命名空间与重映射

介绍 launch 文件的使用语法时，在 node 标签中有两个属性: name 和 ns，二者分别是用于实现名称重映射与命名空间设置的。使用launch文件设置命名空间与名称重映射也比较简单。

#### 1.launch文件

```xml
<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="t1" />
    <node pkg="turtlesim" type="turtlesim_node" name="t2" />
    <node pkg="turtlesim" type="turtlesim_node" name="t1" ns="hello"/>
</launch>
```

在 node 标签中，name 属性是必须的，ns 可选。

#### 2.运行

`rosnode list`查看节点信息,显示结果:

```shell
/t1
/t2
/t1/hello
```

### 4.4.3 编码设置命名空间与重映射

如果自定义节点实现，那么可以更灵活的设置命名空间与重映射实现。

------

#### 1.C++ 实现:重映射

##### 1.1名称别名设置

核心代码:`ros::init(argc,argv,"zhangsan",ros::init_options::AnonymousName);`

##### 1.2执行

会在名称后面添加时间戳。

#### 2.C++ 实现:命名空间

##### 2.1命名空间设置

核心代码

```cpp
  std::map<std::string, std::string> map;
  map["__ns"] = "xxxx";
  ros::init(map,"wangqiang");
```

##### 2.2执行

节点名称设置了命名空间。

------

#### 3.Python 实现:重映射

##### 3.1名称别名设置

核心代码:`rospy.init_node("lisi",anonymous=True)`

##### 3.2执行

会在节点名称后缀时间戳。

## 4.5 ROS话题名称设置

在ROS中节点名称可能出现重名的情况，同理话题名称也可能重名。

> 在 ROS 中节点终端，不同的节点之间通信都依赖于话题，话题名称也可能出现重复的情况，这种情况下，系统虽然不会抛出异常，但是可能导致订阅的消息非预期的，从而导致节点运行异常。这种情况下需要将两个节点的话题名称由相同修改为不同。
>
> 又或者，两个节点是可以通信的，两个节点之间使用了相同的消息类型，但是由于，话题名称不同，导致通信失败。这种情况下需要将两个节点的话题名称由不同修改为相同。

在实际应用中，按照逻辑，有些时候可能需要将相同的话题名称设置为不同，也有可能将不同的话题名设置为相同。在ROS中给出的解决策略与节点名称重命类似，也是使用名称重映射或为名称添加前缀。根据前缀不同，有全局、相对、和私有三种类型之分。

- 全局(参数名称直接参考ROS系统，与节点命名空间平级)
- 相对(参数名称参考的是节点的命名空间，与节点名称平级)
- 私有(参数名称参考节点名称，是节点名称的子级)

------

名称重映射是为名称起别名，为名称添加前缀，该实现比节点重名更复杂些，不单是使用命名空间作为前缀、还可以使用节点名称最为前缀。两种策略的实现途径有多种:

- rosrun 命令
- launch 文件
- 编码实现

本节将对三者的使用逐一演示，三者要实现的需求类似。

#### 案例

在ROS中提供了一个比较好用的键盘控制功能包: ros-noetic-teleop-twist-keyboard，该功能包，可以控制机器人的运动，作用类似于乌龟的键盘控制节点，可以使用 sudo apt install ros-noetic-teleop-twist-keyboard 来安装该功能包，然后执行: rosrun teleop_twist_keyboard teleop_twist_keyboard.py，在启动乌龟显示节点，不过此时前者不能控制乌龟运动，因为，二者使用的话题名称不同，前者使用的是 `cmd_vel`话题，后者使用的是 `/turtle1/cmd_vel`话题。需要将话题名称修改为一致，才能使用，如何实现？

### 4.5.1 rosrun设置话题重映射

**rosrun名称重映射语法: rorun 包名 节点名 话题名:=新话题名称**

实现teleop_twist_keyboard与乌龟显示节点通信方案由两种：

##### 1.方案1

将 teleop_twist_keyboard 节点的话题设置为`/turtle1/cmd_vel`

启动键盘控制节点:`rosrun teleop_twist_keyboard teleop_twist_keyboard.py /cmd_vel:=/turtle1/cmd_vel`

启动乌龟显示节点: `rosrun turtlesim turtlesim_node`

二者可以实现正常通信

##### 2.方案2

将乌龟显示节点的话题设置为 `/cmd_vel`

启动键盘控制节点:`rosrun teleop_twist_keyboard teleop_twist_keyboard.py`

启动乌龟显示节点: `rosrun turtlesim turtlesim_node /turtle1/cmd_vel:=/cmd_vel`

二者可以实现正常通信

### 4.5.2 launch文件设置话题重映射

**launch 文件设置话题重映射语法:**

```xml
<node pkg="xxx" type="xxx" name="xxx">
    <remap from="原话题" to="新话题" />
</node>
```

实现teleop_twist_keyboard与乌龟显示节点通信方案由两种：

##### 1.方案1

将 teleop_twist_keyboard 节点的话题设置为`/turtle1/cmd_vel`

```xml
<launch>

    <node pkg="turtlesim" type="turtlesim_node" name="t1" />
    <node pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py" name="key">
        <remap from="/cmd_vel" to="/turtle1/cmd_vel" />
    </node>

</launch>
```

二者可以实现正常通信

##### 2.方案2

将乌龟显示节点的话题设置为 `/cmd_vel`

```xml
<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="t1">
        <remap from="/turtle1/cmd_vel" to="/cmd_vel" />
    </node>
    <node pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py" name="key" />

</launch>
```

二者可以实现正常通信

### 4.5.3 编码设置话题名称

话题的名称与节点的命名空间、节点的名称是有一定关系的，话题名称大致可以分为三种类型:

- 全局(话题参考ROS系统，与节点命名空间平级)
- 相对(话题参考的是节点的命名空间，与节点名称平级)
- 私有(话题参考节点名称，是节点名称的子级)

结合编码演示具体关系。

------

#### 1.C++ 实现

演示准备:

1.初始化节点设置一个节点名称

```cpp
ros::init(argc,argv,"hello")
```

2.设置不同类型的话题

3.启动节点时，传递一个 __ns:= xxx

4.节点启动后，使用 rostopic 查看话题信息

##### 1.1全局名称

**格式:**以`/`开头的名称，和节点名称无关

**比如:**/xxx/yyy/zzz

**示例1:**`ros::Publisher pub = nh.advertise<std_msgs::String>("/chatter",1000);`

**结果1:**`/chatter`

**示例2:**`ros::Publisher pub = nh.advertise<std_msgs::String>("/chatter/money",1000);`

**结果2:**`/chatter/money`

##### 1.2相对名称

**格式:**非`/`开头的名称,参考命名空间(与节点名称平级)来确定话题名称

**示例1:**`ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);`

**结果1:**`xxx/chatter`

**示例2:**`ros::Publisher pub = nh.advertise<std_msgs::String>("chatter/money",1000);`

**结果2:**`xxx/chatter/money`

##### 1.3私有名称

**格式:**以`~`开头的名称

**示例1:**

```cpp
ros::NodeHandle nh("~");
ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
```

**结果1:**`/xxx/hello/chatter`

**示例2:**

```cpp
ros::NodeHandle nh("~");
ros::Publisher pub = nh.advertise<std_msgs::String>("chatter/money",1000);
```

**结果2:**`/xxx/hello/chatter/money`

*PS:当使用*`~`*,而话题名称有时*`/`*开头时，那么话题名称是绝对的*

**示例3:**

```cpp
ros::NodeHandle nh("~");
ros::Publisher pub = nh.advertise<std_msgs::String>("/chatter/money",1000);
```

**结果3:**`/chatter/money`

------

#### 2.Python 实现

演示准备:

1.初始化节点设置一个节点名称

```python
rospy.init_node("hello")
```

2.设置不同类型的话题

3.启动节点时，传递一个 __ns:= xxx

4.节点启动后，使用 rostopic 查看话题信息

##### 2.1全局名称

**格式:**以`/`开头的名称，和节点名称无关

**示例1:**`pub = rospy.Publisher("/chatter",String,queue_size=1000)`

**结果1:**`/chatter`

**示例2:**`pub = rospy.Publisher("/chatter/money",String,queue_size=1000)`

**结果2:**`/chatter/money`

##### 2.2相对名称

**格式:**非`/`开头的名称,参考命名空间(与节点名称平级)来确定话题名称

**示例1:**`pub = rospy.Publisher("chatter",String,queue_size=1000)`

**结果1:**`xxx/chatter`

**示例2:**`pub = rospy.Publisher("chatter/money",String,queue_size=1000)`

**结果2:**`xxx/chatter/money`

##### 2.3私有名称

**格式:**以`~`开头的名称

**示例1:**`pub = rospy.Publisher("~chatter",String,queue_size=1000)`

**结果1:**`/xxx/hello/chatter`

**示例2:**`pub = rospy.Publisher("~chatter/money",String,queue_size=1000)`

**结果2:**`/xxx/hello/chatter/money`

### 4.6 ROS参数名称设置

在ROS中节点名称话题名称可能出现重名的情况，同理参数名称也可能重名。

> 当参数名称重名时，那么就会产生覆盖，如何避免这种情况？

关于参数重名的处理，没有重映射实现，为了尽量的避免参数重名，都是使用为参数名添加前缀的方式，实现类似于话题名称，有全局、相对、和私有三种类型之分。

- 全局(参数名称直接参考ROS系统，与节点命名空间平级)
- 相对(参数名称参考的是节点的命名空间，与节点名称平级)
- 私有(参数名称参考节点名称，是节点名称的子级)

------

设置参数的方式也有三种:

- rosrun 命令
- launch 文件
- 编码实现

三种设置方式前面都已经有所涉及，但是之前没有涉及命名问题，本节将对三者命名的设置逐一演示。

#### 案例

启动节点时，为参数服务器添加参数(需要注意参数名称设置)。

### 4.6.1 rosrun设置参数

rosrun 在启动节点时，也可以设置参数:

**语法:** rosrun 包名 节点名称 _参数名:=参数值

#### 1.设置参数

启动乌龟显示节点，并设置参数 A = 100

```shell
rosrun turtlesim turtlesim_node _A:=100
```

#### 2.运行

`rosparam list`查看节点信息,显示结果:

```shell
/turtlesim/A
/turtlesim/background_b
/turtlesim/background_g
/turtlesim/background_r
```

结果显示，参数A前缀节点名称，也就是说rosrun执行设置参数参数名使用的是私有模式

### 4.6.2 launch文件设置参数

通过 launch 文件设置参数的方式前面已经介绍过了，可以在 node 标签外，或 node 标签中通过 param 或 rosparam 来设置参数。在 node 标签外设置的参数是全局性质的，参考的是 / ，在 node 标签中设置的参数是私有性质的，参考的是 /命名空间/节点名称。

#### 1.设置参数

以 param 标签为例，设置参数

```xml
<launch>
    <param name="p1" value="100" />
    <node pkg="turtlesim" type="turtlesim_node" name="t1">
        <param name="p2" value="100" />
    </node>
</launch>
```

#### 2.运行

`rosparam list`查看节点信息,显示结果:

```
/p1
/t1/p1
```

运行结果与预期一致。

### 4.6.3 编码设置参数

编码的方式可以更方便的设置:全局、相对与私有参数。

------

#### 1.C++实现

在 C++ 中，可以使用 ros::param 或者 ros::NodeHandle 来设置参数。

##### 1.1ros::param设置参数

设置参数调用API是ros::param::set，该函数中，参数1传入参数名称，参数2是传入参数值，参数1中参数名称设置时，如果以 / 开头，那么就是全局参数，如果以 ~ 开头，那么就是私有参数，既不以 / 也不以 ~ 开头，那么就是相对参数。代码示例:

```cpp
ros::param::set("/set_A",100); //全局,和命名空间以及节点名称无关
ros::param::set("set_B",100); //相对,参考命名空间
ros::param::set("~set_C",100); //私有,参考命名空间与节点名称
```

运行时，假设设置的 namespace 为 xxx，节点名称为 yyy，使用 rosparam list 查看:

```shell
/set_A
/xxx/set_B
/xxx/yyy/set_C
```

##### 1.2ros::NodeHandle设置参数

设置参数时，首先需要创建 NodeHandle 对象，然后调用该对象的 setParam 函数，该函数参数1为参数名，参数2为要设置的参数值，如果参数名以 / 开头，那么就是全局参数，如果参数名不以 / 开头，那么，该参数是相对参数还是私有参数与NodeHandle 对象有关，如果NodeHandle 对象创建时如果是调用的默认的无参构造，那么该参数是相对参数，如果NodeHandle 对象创建时是使用:

ros::NodeHandle nh("~")，那么该参数就是私有参数。代码示例:

```cpp
ros::NodeHandle nh;
nh.setParam("/nh_A",100); //全局,和命名空间以及节点名称无关

nh.setParam("nh_B",100); //相对,参考命名空间

ros::NodeHandle nh_private("~");
nh_private.setParam("nh_C",100);//私有,参考命名空间与节点名称
```

运行时，假设设置的 namespace 为 xxx，节点名称为 yyy，使用 rosparam list 查看:

```shell
/nh_A
/xxx/nh_B
/xxx/yyy/nh_C
```

------

#### 2.python实现

python 中关于参数设置的语法实现比 C++ 简洁一些，调用的API时 rospy.set_param，该函数中，参数1传入参数名称，参数2是传入参数值，参数1中参数名称设置时，如果以 / 开头，那么就是全局参数，如果以 ~ 开头，那么就是私有参数，既不以 / 也不以 ~ 开头，那么就是相对参数。代码示例:

```python
rospy.set_param("/py_A",100)  #全局,和命名空间以及节点名称无关
rospy.set_param("py_B",100)  #相对,参考命名空间
rospy.set_param("~py_C",100)  #私有,参考命名空间与节点名称
```

运行时，假设设置的 namespace 为 xxx，节点名称为 yyy，使用 rosparam list 查看:

```shell
/py_A
/xxx/py_B
/xxx/yyy/py_C
```

## 4.7 ROS分布式通信

ROS是一个分布式计算环境。一个运行中的ROS系统可以包含分布在多台计算机上多个节点。根据系统的配置方式，任何节点可能随时需要与任何其他节点进行通信。

因此，ROS对网络配置有某些要求：

- 所有端口上的所有机器之间必须有完整的双向连接。
- 每台计算机必须通过所有其他计算机都可以解析的名称来公告自己。

#### **实现**

##### 1.准备

先要保证不同计算机处于同一网络中，最好分别设置固定IP，如果为虚拟机，需要将网络适配器改为桥接模式；

##### 2.配置文件修改

分别修改不同计算机的 /etc/hosts 文件，在该文件中加入对方的IP地址和计算机名:

主机端:

```
从机的IP    从机计算机名
```

从机端:

```
主机的IP    主机计算机名
```

设置完毕，可以通过 ping 命令测试网络通信是否正常。

> IP地址查看名: ifconfig
>
> 计算机名称查看: hostname

##### 3.配置主机IP

配置主机的 IP 地址

~/.bashrc 追加

```shell
export ROS_MASTER_URI=http://主机IP:11311
export ROS_HOSTNAME=主机IP
```

##### 4.配置从机IP

配置从机的 IP 地址，从机可以有多台，每台都做如下设置:

~/.bashrc 追加

```shell
export ROS_MASTER_URI=http://主机IP:11311
export ROS_HOSTNAME=从机IP
```

#### **测试**

1.主机启动 roscore(必须)

2.主机启动订阅节点，从机启动发布节点，测试通信是否正常

3.反向测试，主机启动发布节点，从机启动订阅节点，测试通信是否正常

## 4.8 本章小结

本章主要介绍了ROS的运行管理机制，内容如下:

- 如何通过元功能包关联工作空间下的不同功能包
- 使用 launch 文件来管理维护 ROS 中的节点
- 在 ROS 中重名是经常出现的，重名时会导致什么情况？以及怎么避免重名？
- 如何实现 ROS 分布式通信？

本章的重点是"重名"相关的内容：

- 包名重复，会导致覆盖。
- 节点名称重复，会导致先启动的节点关闭
- 话题名称重复，无语法异常，但是可能导致通信实现出现逻辑问题
- 参数名称重复，会导致参数设置的覆盖

解决重名问题的实现方案有两种:

- 重映射(重新起名字)
- 为命名添加前缀

本章介绍的内容还是偏向语法层面的实现，下一章将开始介绍ROS中内置的一些较为实用的组件。
