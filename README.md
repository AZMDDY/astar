# A* 算法

A*（念做：A Star）算法是一种很常用的路径查找和图形遍历算法。它有较好的性能和准确度。

在本项目中的`include`文件夹下是C++的仅头文件实现，`play`文件夹中是一个演示程序。

## A* 算法介绍

+ [https://zhuanlan.zhihu.com/p/54510444](https://zhuanlan.zhihu.com/p/54510444)
+ [https://blog.csdn.net/b2b160/article/details/4057781](https://blog.csdn.net/b2b160/article/details/4057781)


## 项目介绍

+ base.hpp: 定义了一个日志宏，用于调试；
+ point.hpp: 对点进行封装，提供接口；
+ map.hpp: 对地图进行封装，提供一些地图的接口；
+ astar.hpp: A*算法的核心文件，AStar类提供两个接口用于加载地图和生成路径；

## 演示

+ play.cpp: 利用ASCII控制字符在终端显示地图；

![](https://raw.githubusercontent.com/AZMDDY/imgs/master/tutieshi_640x288_16s.gif)
