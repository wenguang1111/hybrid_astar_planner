#ifndef HYBRID_ASTAR_PLANNER_UTILS_H
#define HYBRID_ASTAR_PLANNER_UTILS_H

#include "tool/fp_datatype.h"
#include "tool/recorder.h"
#include <cmath>
#include <vector>

using namespace std;

typedef vector<int_6_9> Point; //* exsist x and y

typedef vector<int_6_9> Pose; //* x,y,yaw; range analysis for x, y
typedef vector<double> Pose_ret;

enum direction_t { left = 'l', straight = 's', right = 'r' };

inline Point calcTurnCenter(Pose point, char dir, double radius) { //* radius
    uint_6_10 x, y;
    int_4_11 ang;
    Point turn_center;

    ang = point[2];

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::ang",
                                              ang);
#endif

    if (dir == direction_t::left)
        ang += M_PI_2;
    else if (dir == direction_t::right)
        ang -= M_PI_2;

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::ang",
                                              ang);
#endif

    x = point[0] + cos(ang) * radius;
    y = point[1] + sin(ang) * radius;

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::x", x);
    Recorder::getInstance()->saveData<double>("Utils::calcTurnCenter()::y", y);
#endif

    turn_center.push_back(x);
    turn_center.push_back(y);
    return turn_center;
}

inline uint_6_10 distance(Pose p1, Pose p2) {

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>(
        "Utils::distance()::ans",
        sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2)));
#endif

    // return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
    return sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) +
                (p2[1] - p1[1]) * (p2[1] - p1[1]));
}

#endif // HYBRID_ASTAR_PLANNER_UTILS_H
