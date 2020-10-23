#include <iostream>
#include <random>
#include "point.hpp"
#include "map.hpp"
#include "astar.hpp"
#include "play.hpp"

using namespace astar;

Point MapRandPoint(uint32_t h, uint32_t w)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, h * w);
    auto res = dis(gen);
    int pH = res / w;
    int pW = res - pH * w;
    return {pW, pH};
}

void GenBarrier(Map& map)
{
    uint32_t count = (map.Height() * map.Width()) / 8;
    for (uint32_t i = 0; i < count;) {
        auto point = MapRandPoint(map.Height(), map.Width());
        if (map.At(point) == 0) {
            map.Assign(point, 1);
            i++;
        }
        else {
            continue;
        }
    }
}

void GenStartAndEnd(Map& map, Point& start, Point& end)
{
    if (map.Empty()) {
        return;
    }
    for (uint32_t i = 0; i < 2;) {
        auto point = MapRandPoint(map.Height(), map.Width());
        if (map.At(point) == 0) {
            if (i == 0) {
                map.Assign(point, 2);
                start = point;
            }
            else {
                map.Assign(point, 3);
                end = point;
            }
            i++;
        }
        else {
            continue;
        }
    }
}

int main(int argc, char** argv)
{
    uint32_t mapHeight = 0;
    uint32_t mapWidth = 0;
    std::cout << "map width: ";
    std::cin >> mapWidth;
    std::cout << "map height: ";
    std::cin >> mapHeight;
    Map maze(mapWidth, mapHeight);

    GenBarrier(maze);

    Point start;
    Point end;
    GenStartAndEnd(maze, start, end);

    AStar aStar(D8);
    aStar.LoadMap(maze);

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
    ClearScreen(maze.Height() + 1);
    PrintMaze(maze);
    uint32_t i = 0;
    for (; i < (path.size() - 1); i++) {
        std::cout << "(" << path[i].x << ", " << path[i].y << ") -> ";
    }
    std::cout << "(" << path[i].x << ", " << path[i].y << ")" << std::endl;

    return 0;
}