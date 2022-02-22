# LOAM 梳理

本篇文章对 LOAM 框架进行宏观的解析，暂不涉及内部具体的实现原理。





## 整个流程

整个 LOAM 框架分为三个主要部分，分别为 **Registration**（**特征提取**）、**Odometry**（**特征匹配**）和 **Mapping**（**建图**），分别存储于相应的 cpp 文件中。首先将输入点云进行特征提取，利用提取的特征进行特征匹配，最后将点云置于地图中，具体流程见下图。

![](data/LOAM 梳理-总流程图.png)

## 主要思路

### Registration（特征提取）

特征提取流程主要如下：

1. 输入点云预处理（去除 NAN 点及距离过近的点）

2. 调整角度，将输入点云调整至 $(-\pi,\pi)$ 区间内

3. 把每个点存储到对应的扫描线上，并利用强度信息记录下来

4. 计算每个点的去率，记录索引（点对应的索引，后续对曲率排序是对索引排序）、近邻（该点是否为近邻点）、标签（该点属于什么类型的点）

5. 特征提取

   遍历每条扫描线，每条扫描线上分 6 个区域，每个区域内按曲率大小进行排序：

    1. 从大到小遍历提取角点

       曲率最大的 2 个特征点（**cornerPointsSharp**，不包含近邻点，标签为 2）、曲率较大的前 20 个特征点（**subCornerPointsLessSharp**，不包含近邻点，标签为 1），并标记近邻点

    2. 从小到大遍历提取表面点

       曲率最小的 4 个特征点（**subSurfPointsFlat**，不包含近邻点，标签为 -1），并标记近邻点、除去曲率较大的前 20 个特征点，剩余的点再降采样后的点（**subSurfPointsLessFlat**）

6. 发布信息

### Odometry（特征匹配）



### Mapping（建图）



## 消息传递

理解不同部分之间的消息传递有助于理解整个 LOAM 框架。

![](data/LOAM 梳理-LOAM消息传递.png)

### Registration（特征提取）

- **输入：**
  - **laserCloudIn**：输入点云

- **输出：**
  - **pubLaserCloud**：全部点云
  - **pubCornerPointsSharp**：每个区域角点特征（2 个）× 6 个区域 × 线数
  - **pubCornerPointsLessSharp**：每个区域角点特征（20 个）× 6 个区域 × 线数
  - **pubSurfPointsFlat**：每个区域平面特征（4 个）× 6 个区域 × 线数
  - **pubSurfPointsLessFlat**：每个区域角点特征（（全部点云 - 角点特征（20 个））/ 降采样）× 6 个区域 × 线数
  - **pubRemovePoints**

### Odometry（特征匹配）

- **输入：**
  - **subLaserCloudFullRes**：全部点云
  - **subCornerPointsSharp**：每个区域角点特征（2 个）× 6 个区域 × 线数
  - **subCornerPointsLessSharp**：每个区域角点特征（20 个）× 6 个区域 × 线数
  - **subSurfPointsFlat**：每个区域平面特征（4 个）× 6 个区域 × 线数
  - **subSurfPointsLessFlat**：每个区域角点特征（（全部点云 - 角点特征（20 个））/ 降采样）× 6 个区域 × 线数

- **输出：**
  - **pubLaserCloudFullRes**：全部点云
  - **pubLaserCloudCornerLast**：每个区域角点特征（20 个）× 6 个区域 × 线数
  - **pubLaserCloudSurfLast**：每个区域角点特征（（全部点云 - 角点特征（20 个））/ 降采样）× 6 个区域 × 线数
  - **pubLaserOdometry**：odom 坐标系
  - **pubLaserPath**

### Mapping（建图）

- **输入：**
  - **subLaserCloudFullRes**：全部点云
  - **subLaserCloudCornerLast**：每个区域角点特征（20 个）× 6 个区域 × 线数
  - **subLaserCloudSurfLast**：每个区域角点特征（（全部点云 - 角点特征（20 个））/ 降采样）× 6 个区域 × 线数
  - **subLaserOdometry**：odom 坐标系

- **输出：**
  - **pubLaserCloudFullRes**：转换到 map 坐标系下的全部点云
  - **pubLaserCloudSurround**
  - **pubLaserCloudMap**
  - **pubOdomAftMappedHighFrec**
  - **pubOdomAftMapped**：map 坐标系
  - **pubLaserAfterMappedPath**

## 位姿传递

