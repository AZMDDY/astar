#ifndef ASTAR_MAP_HPP_
#define ASTAR_MAP_HPP_
#include <iostream>
#include <array>
#include <vector>
#include "point.hpp"

namespace astar {

const int block = 1;
const int space = 0;
const int illegal = INT32_MAX;

class Map {
public:
    Map() : m(0), n(0) {}
    Map(const std::vector<std::vector<int>>& map);
    Map(const Map& m) = default;
    ~Map() = default;

    inline int At(int x, int y);
    inline int At(const Point& pos);
    inline bool Assign(int x, int y, int value);
    inline bool Assign(const Point& pos, int value);
    inline int Width();
    inline int Height();
    inline bool Empty();

    void Print();

private:
    std::vector<std::vector<int>> map;
    int m;  // col
    int n;  // row
};

Map::Map(const std::vector<std::vector<int>>& map)
{
    this->map = map;
    n = this->map.size();
    m = (n > 0 ? this->map[0].size() : 0);
}

inline int Map::At(int x, int y)
{
    if (x >= m || y >= n || x < 0 || y < 0) {
        return illegal;
    }
    return map[x][y];
}

inline int Map::At(const Point& pos)
{
    return At(pos.x, pos.y);
}

inline bool Map::Assign(int x, int y, int value)
{
    if (x >= m || y >= n || x < 0 || y < 0) {
        return false;
    }
    map[x][y] = value;
    return true;
}

inline bool Map::Assign(const Point& pos, int value)
{
    return Assign(pos.x, pos.y, value);
}

void Map::Print()
{
    std::cout << "{" << std::endl;
    for (int i = 0; i < (n - 1); i++) {
        std::cout << "{";
        for (int j = 0; j < (m - 1); j++) {
            std::cout << map[i][j] << ", ";
        }
        std::cout << map[i][m - 1] << "}," << std::endl;
    }
    std::cout << "{";
    for (int j = 0; j < (m - 1); j++) {
        std::cout << map[n - 1][j] << ", ";
    }
    if (n > 0 && m > 0) {
        std::cout << map[n - 1][m - 1] << "}\n}" << std::endl;
    }
}

inline int Map::Width()
{
    return m;
}

inline int Map::Height()
{
    return n;
}

inline bool Map::Empty()
{
    return map.empty();
}

}  // namespace astar

#endif  // ASTAR_MAP_HPP_