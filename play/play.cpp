#include "play.hpp"

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