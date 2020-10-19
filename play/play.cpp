#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "base.hpp"
#include "point.hpp"
#include "map.hpp"
#include "astar.hpp"

using namespace std::chrono_literals;

const std::string whiteBlock = "\033[37m[ ]\033[0m";
const std::string redBlock = "\033[31m[■]\033[0m";
const std::string yellowBlock = "\033[33m[■]\033[0m";
const std::string blueBlock = "\033[34m[■]\033[0m";
const std::string greenBlock = "\033[32m[■]\033[0m";
const std::string blackBlock = "\033[30m[■]\033[0m";
const std::string backLine = "\33[A";

// 0 whiteBlock: space
// 1 blackBlock: barrier
// 2 redBlock: start
// 3 blueBlock: end
// 4 yellowBlock: path
const std::vector<std::string> blockColor = {whiteBlock, blackBlock, redBlock, blueBlock, yellowBlock};

void DefPoint(astar::Map& maze, const astar::Point& start, const astar::Point& end)
{
    maze.Assign(start, 2);
    maze.Assign(end, 3);
}

void PrintMaze(astar::Map& maze)
{
    for (int i = 0; i < maze.Height(); i++) {
        for (int j = 0; j < maze.Width(); j++) {
            if ((uint32_t)maze.At(j, i) < blockColor.size()) {
                std::cout << blockColor[maze.At(j, i)];
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ClearScreen(uint32_t row)
{
    for (uint32_t i = 0; i < row; i++) {
        std::cout << backLine;
    }
}

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

    astar::AStar aStar(astar::D8);
    aStar.LoadMap(maze);

    astar::Point start = {0, 0};
    astar::Point end = {11, 11};
    DefPoint(maze, start, end);
    auto path = aStar.FindPath(start, end);

    // display the maze
    uint32_t count = 0;
    PrintMaze(maze);
    if (path.empty()) {
        std::cout << "path not found" << std::endl;
        return 0;
    }
    while (count < path.size()) {
        std::this_thread::sleep_for(1s);
        ClearScreen(maze.Height() + 1);
        maze.Assign(path[count], 4);
        PrintMaze(maze);
        ClearScreen(1);
        std::cout << "(" << path[count].x << ", " << path[count].y << ")" << std::endl;
        count++;
    }
    ClearScreen(maze.Height() + 2);
    PrintMaze(maze);
    uint32_t i = 0;
    for (; i < (path.size() - 1); i++) {
        std::cout << "(" << path[i].x << ", " << path[i].y << ") -> ";
    }
    std::cout << "(" << path[i].x << ", " << path[i].y << ")" << std::endl;
    return 0;
}