#include "include/Car.h"
#include "cnl/scaled_integer.h"
#include "tool/fp_datatype.h"
#include "tool/recorder.h"
#include <cmath>

using namespace std;

Car::Car() {}

Car::Car(vector<uint_3_13> dimensions, Pose pose_) : pose(pose_) {
    length = dimensions[0];
    width = dimensions[1];
}

// Set the pose of the car
void Car::setPose(Pose p) { pose = p; }

// Compute the outline of the car given its current pose
vector<Point> Car::getOutline() {
    int_6_9 x, y;
    int_2_13 yaw;
    int_6_9 tail_x, tail_y, head_x, head_y;
    vector<int_6_9> tail_l, tail_r;
    vector<int_6_9> head_r, head_l;

    x = pose[0];
    y = pose[1];
    yaw = pose[2];
#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Car::getOutline()::x", x);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::y", y);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::yaw", yaw);
#endif
    tail_x = x - cos(yaw) * length / 4.0;
    tail_y = y - sin(yaw) * length / 4.0;
    tail_l.push_back(tail_x + cos(yaw + M_PI_2) * width / 2.0);
    tail_l.push_back(tail_y + sin(yaw + M_PI_2) * width / 2.0);
    tail_r.push_back(tail_x + cos(yaw - M_PI_2) * width / 2.0);
    tail_r.push_back(tail_y + sin(yaw - M_PI_2) * width / 2.0);
#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_x",
                                              tail_x);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_y",
                                              tail_y);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_l[i]",
                                              tail_x + cos(yaw + M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_l[i]",
                                              tail_y + sin(yaw + M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_r[i]",
                                              tail_x + cos(yaw - M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::tail_r[i]",
                                              tail_y + sin(yaw - M_PI_2) *
                                                           width / 2.0);
#endif
    head_x = x + cos(yaw) * length * 3.0 / 4.0;
    head_y = y + sin(yaw) * length * 3.0 / 4.0;
    head_l.push_back(head_x + cos(yaw + M_PI_2) * width / 2.0);
    head_l.push_back(head_y + sin(yaw + M_PI_2) * width / 2.0);
    head_r.push_back(head_x + cos(yaw - M_PI_2) * width / 2.0);
    head_r.push_back(head_y + sin(yaw - M_PI_2) * width / 2.0);
#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_x",
                                              head_x);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_y",
                                              head_y);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_l[i]",
                                              head_x + cos(yaw + M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_l[i]",
                                              head_y + sin(yaw + M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_r[i]",
                                              head_x + cos(yaw - M_PI_2) *
                                                           width / 2.0);
    Recorder::getInstance()->saveData<double>("Car::getOutline()::head_r[i]",
                                              head_y + sin(yaw - M_PI_2) *
                                                           width / 2.0);
#endif
    vector<Point> outline;
    outline.push_back(tail_l);
    outline.push_back(tail_r);
    outline.push_back(head_r);
    outline.push_back(head_l);
    outline.push_back(tail_l);
    return outline;
}
