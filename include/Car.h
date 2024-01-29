#ifndef HYBRID_ASTAR_PLANNER_CAR_H
#define HYBRID_ASTAR_PLANNER_CAR_H

#include "utils.h"

#include <tuple>
#include <vector>

using namespace std;
class Car {
  public:
    Car();
    Car(vector<double> dimensions, Pose pose_);
    void setPose(Pose p);
    vector<uint_6_10> getOutline();

  private:
    double length;
    double width;
    Pose pose; // x, y, yaw
};

#endif // HYBRID_ASTAR_PLANNER_CAR_H
