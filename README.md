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
  + MoveCast(): 计算在从start到end的代价；
  + PointVaild(): 判断点在地图中是否可用(不是障碍物，没有越界)；
  + InOpenZone(): 判断点是否在`openZone`中；
  + MigratePoint(): 计算一个点附近所有的可用点的优先级，并纳管到`openZone`;
  + LoadMap(): 加载地图；
  + FindPath(): 生成路径；
  + PointCost: 由于每个点都需要存它到起点的代价和预计到终端的代价之和，所以定义了一个内部类，对于路径的回溯，需要定义父节点，在类中使用了智能指针(shared_ptr)去存父节点，在使用时，直接构造(make_shared)父节点；
  + openZone：存放待考察的点，由于是根据代价优先级来取下一个考察点，所有使用了优先队列；
  + closeZone: 存放已经考察了的点，在这里仅仅需要点的信息，所以用映射或者数组就可以标记（二维坐标可以用一个数来表示，(i, j) -> (j * row + i)），并提供`O(1)`的查找；
  + MoveType: 定义了在地图上移动的类型，D4: 可以向上下左右4个方向移动，D8: 可以向8个方向移动；

## 演示

+ play/play.*: 利用ASCII控制字符在终端动态显示路径查找结果；
+ test/test.cpp: 在地图上生成随机障碍、起点和终点进行路径查找测试，并在终端动态显示结果；

play:
![](https://raw.githubusercontent.com/AZMDDY/imgs/master/tutieshi_640x288_16s.gif)


test:
![](https://raw.githubusercontent.com/AZMDDY/imgs/master/20201020233447.png)
