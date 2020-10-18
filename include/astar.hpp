#ifndef ASTAR_ASTAR_HPP_
#define ASTAR_ASTAR_HPP_
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include "base.hpp"
#include "point.hpp"
#include "map.hpp"

namespace astar {

// move in the map
enum MoveType {
    D4 = 4,  // four direction
    D8 = 8   // eight firection
};

class AStar {
public:
    AStar() : moveType(D4) {}
    AStar(MoveType mt) : moveType(mt) {}
    AStar(const AStar& aStar) = delete;
    AStar(AStar&& aStar) = delete;
    AStar operator=(const AStar& aStar) = delete;
    AStar& operator=(AStar&& aStar) = delete;
    ~AStar() = default;

    void LoadMap(const Map& map);
    std::vector<Point> FindPath(const Point& start, const Point& end);

private:
    class PointCost {
    public:
        Point point;
        int cost;
        std::shared_ptr<PointCost> parent;

        PointCost(const Point& point, int cost, std::shared_ptr<PointCost> parent)
            : point(point), cost(cost), parent(parent) {}
        PointCost(const PointCost& pointCost) = default;
        ~PointCost() = default;
        // the lower the cost, the higher the priority
        bool operator<(const PointCost& p) const { return (this->cost > p.cost); }
    };

    // the cost of moving
    // horCost: the cost of moving horizontally
    // verCost: the cost of moving vertically
    // diaCost: the cost of moving diagonally
    int MoveCast(const Point& start, const Point& end, int horCost = 1, int verCost = 1, int diaCost = 1);

    bool PointVaild(const Point& point);

    bool InOpenZone(std::priority_queue<PointCost> pc, const Point& point)
    {
        while (!pc.empty()) {
            auto tmp = pc.top();
            pc.pop();
            if (point == tmp.point) {
                return true;
            }
        }
        return false;
    }

    void MigratePoint(const PointCost& pc, const Point& start, const Point& end)
    {
        // up, down, left, right, diagonal up right, diagonal down right, diagonal down left, diagonal up left
        static int move[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
        for (int i = 0; i < moveType; i++) {
            auto tmp = pc.point + Point(move[i][0], move[i][1]);
            if (PointVaild(tmp)) {
                if (closeZone.find(tmp.x + tmp.y * map.Width()) != closeZone.end()) {
                    continue;
                }
                if (!InOpenZone(openZone, tmp)) {
                    int cost = pc.cost + MoveCast(pc.point, tmp) + MoveCast(tmp, end);
                    openZone.emplace(tmp, cost, std::make_shared<PointCost>(pc));
                }
            }
        }
    }

private:
    Map map;
    MoveType moveType;
    std::priority_queue<PointCost> openZone;
    std::unordered_map<uint32_t, int> closeZone;
};

void AStar::LoadMap(const Map& map)
{
    this->map = map;
    while (!openZone.empty()) {
        openZone.pop();
    }
    closeZone.clear();
}

std::vector<Point> AStar::FindPath(const Point& start, const Point& end)
{
    if (map.Empty()) {
        ALOG() << "the map is empty!";
        return {};
    }
    if (start == end) {
        return {start};
    }
    if (!(PointVaild(start) && PointVaild(end))) {
        ALOG() << "the start or end point is invaild";
        return {};
    }
    openZone.emplace(start, 0, nullptr);

    std::vector<Point> path;

    while (!openZone.empty()) {
        auto pc = openZone.top();
        openZone.pop();
        if (pc.point == end) {
            path.push_back(pc.point);
            auto parent = pc.parent;
            while (parent != nullptr) {
                path.push_back(parent->point);
                parent = parent->parent;
            }
            break;
        }
        else {
            closeZone[pc.point.x + pc.point.y * map.Width()] = pc.cost;
            MigratePoint(pc, start, end);
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int AStar::MoveCast(const Point& start, const Point& end, int horCost, int verCost, int diaCost)
{
    int dx = std::labs(start.x - end.x);
    int dy = std::labs(start.y - end.y);
    int cost = 0;
    if (moveType == D4) {
        cost = dx * horCost + dy * verCost;
    }
    else if (moveType == D8) {
        if (dx > dy) {
            cost = horCost * (dx - dy) + diaCost * dy;
        }
        else {
            cost = verCost * (dy - dx) + diaCost * dx;
        }
    }
    return cost;
}

bool AStar::PointVaild(const Point& point)
{
    auto val = map.At(point);
    return val != illegal && val != block;
}
}  // namespace astar

#endif  // ASTAR_ASTAR_HPP_