#ifndef HYBRID_ASTAR_PLANNER_CAR_H
#define HYBRID_ASTAR_PLANNER_CAR_H

#include "utils.h"

#include <tuple>
#include <vector>

using namespace std;
class Car {
  public:
    Car();
    Car(vector<uint_3_13> dimensions, Pose pose_);
    void setPose(Pose p);
    vector<Point> getOutline();

  private:
    uint_3_13 length;
    uint_3_13 width;
    Pose pose; // x, y, yaw
};

#endif // HYBRID_ASTAR_PLANNER_CAR_H
