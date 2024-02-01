#ifndef HYBRID_ASTAR_PLANNER_DUBINS_H
#define HYBRID_ASTAR_PLANNER_DUBINS_H

#include "tool/fp_datatype.h"
#include "utils.h"

#include <utility>
#include <vector>

using namespace std;

typedef pair<char, int_6_9> DubinsPoint;
typedef vector<DubinsPoint> DubinsPath;

class Dubins {
  public:
    Dubins(Pose start_pose, Pose end_pose, double radius_)
        : start(move(start_pose)), end(move(end_pose)), radius(radius_) {}
    vector<DubinsPoint> getShortestPath();
    static vector<Pose> generatePath(Pose s, vector<DubinsPoint> path,
                                     double radius);
    static int_3_12 mod2Pi(int_3_12 theta);

  private:
    Pose start, end;
    int_6_9 radius;
    Pose calcEnd();
    vector<DubinsPoint> calcLSL(Pose e);
    vector<DubinsPoint> calcRSR(Pose e);
    vector<DubinsPoint> calcLSR(Pose e);

    vector<DubinsPoint> calcRSL(Pose e);
    vector<DubinsPoint> calcLRL(Pose e);
    vector<DubinsPoint> calcRLR(Pose e);
    vector<DubinsPath> calcPaths();
};

#endif // HYBRID_ASTAR_PLANNER_DUBINS_H
