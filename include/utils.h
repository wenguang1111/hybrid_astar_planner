#ifndef HYBRID_ASTAR_PLANNER_UTILS_H
#define HYBRID_ASTAR_PLANNER_UTILS_H

#include "tool/fp_datatype.h"
#include <cmath>
#include <vector>

using namespace std;

typedef vector<uint_6_10> Point; //* range analysis for position
typedef vector<double> Pose;     //* x,y,yaw; range analysis for x, y

enum direction_t { left = 'l', straight = 's', right = 'r' };

inline Point calcTurnCenter(Pose point, char dir, double radius) { //* radius
    uint_6_10 x, y;
    int_2_13 ang;
    Point turn_center;

    ang = point[2];
    if (dir == direction_t::left)
        ang += M_PI_2;
    else if (dir == direction_t::right)
        ang -= M_PI_2;

    x = point[0] + cos(ang) * radius;
    y = point[1] + sin(ang) * radius;
    turn_center.push_back(x);
    turn_center.push_back(y);
    return turn_center;
}

inline uint_6_10 distance(Point p1, Point p2) {
    return cnl::sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) +
                     (p2[1] - p1[1]) * (p2[1] - p1[1]));
}

#endif // HYBRID_ASTAR_PLANNER_UTILS_H
