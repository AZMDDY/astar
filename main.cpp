#include <iostream>
#include "base.hpp"
#include "point.hpp"
#include "map.hpp"
#include "astar.hpp"
int main(int argc, char** argv)
{
    astar::AStar as(astar::D8);

    astar::Map maze({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                     {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                     {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});
    maze.Print();
    as.LoadMap(maze);
    auto path = as.FindPath({0, 0}, {3, 3});
    for (auto& point : path) {
        maze.Assign(point, 8);
    }
    maze.Print();
    return 0;
}