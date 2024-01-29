#ifndef HYBRID_ASTAR_PLANNER_UTILS_H
#define HYBRID_ASTAR_PLANNER_UTILS_H

#include "tool/fp_datatype.h"
#include "tool/recorder.h"
#include <cmath>
#include <vector>

using namespace std;

typedef vector<uint_6_10> Point; //* range analysis for position
typedef vector<double> Pose;     //* x,y,yaw; range analysis for x, y

enum direction_t { left = 'l', straight = 's', right = 'r' };
enum direction_t { left = 'l', straight = 's', right = 'r' };

inline Point calcTurnCenter(Pose point, char dir, double radius) { //* radius
    uint_6_10 x, y;
    int_2_13 ang;
    Point turn_center;

    ang = point[2];
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::ang",
                                              ang);
    if (dir == direction_t::left)
        ang += M_PI_2;
    else if (dir == direction_t::right)
        ang -= M_PI_2;
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::ang",
                                              ang);

    x = point[0] + cos(ang) * radius;
    y = point[1] + sin(ang) * radius;
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::x", x);
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::y", y);
    turn_center.push_back(x);
    turn_center.push_back(y);
    return turn_center;
}

inline uint_6_10 distance(Point p1, Point p2) {
    Recorder::getInstance()->saveData<double>(
        "Utils::distance()::ans",
        sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2)));
    return cnl::sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) +
                     (p2[1] - p1[1]) * (p2[1] - p1[1]));
}

#endif // HYBRID_ASTAR_PLANNER_UTILS_H
