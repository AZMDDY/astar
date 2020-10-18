#ifndef ASTAR_POINT_HPP_
#define ASTAR_POINT_HPP_

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
    x += p.x;
    y += p.y;
    return *this;
}

Point operator+(const Point& aPoint, const Point& bPoint)
{
    return {aPoint.x + bPoint.x, aPoint.y + bPoint.y};
}

}  // namespace astar

#endif  // ASTAR_POINT_HPP_