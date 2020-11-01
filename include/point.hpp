#ifndef ASTAR_POINT_HPP_
#define ASTAR_POINT_HPP_
#include "base.hpp"

namespace astar {
class Point {
public:
    int x;
    int y;

public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& p) = default;
    ~Point() = default;

    bool operator==(const Point& p) const;
    Point& operator+=(const Point& p);
};

inline bool Point::operator==(const Point& p) const
{
    return (this->x == p.x && this->y == p.y);
}

Point& Point::operator+=(const Point& p)
{
    if ((p.x > 0 && INT32_MAX - p.x < x) || (p.y > 0 && INT32_MAX - p.y < y) || (p.x < 0 && INT32_MIN - p.x > x) ||
        (p.y < 0 && INT32_MIN - p.y > y)) {
        ALOG() << "add point is out of range.";
        return *this;
    }
    x += p.x;
    y += p.y;
    return *this;
}

Point operator+(const Point& aPoint, const Point& bPoint)
{
    if ((aPoint.x > 0 && INT32_MAX - aPoint.x < bPoint.x) || (aPoint.y > 0 && INT32_MAX - aPoint.y < bPoint.y) ||
        (aPoint.x < 0 && INT32_MIN - aPoint.x > bPoint.x) || (aPoint.y < 0 && INT32_MIN - aPoint.y > bPoint.y)) {
        ALOG() << "add point is out of range.";
        return {0, 0};
    }
    return {aPoint.x + bPoint.x, aPoint.y + bPoint.y};
}

}  // namespace astar

#endif  // ASTAR_POINT_HPP_