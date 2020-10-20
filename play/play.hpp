#ifndef ASTAR_PLAY_HPP_
#define ASTAR_PLAY_HPP_
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
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
#endif  // ASTAR_PLAY_HPP_