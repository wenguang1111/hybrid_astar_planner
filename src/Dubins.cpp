#include "include/Dubins.h"
#include "tool/fp_datatype.h"
#include "tool/recorder.h"
#include <cmath>

// Find the shortest Dubin's path from the start to end
DubinsPath Dubins::getShortestPath() {
    vector<DubinsPath> paths;
    DubinsPath shortest_path;
    uint_10_6 cost, shortest_cost;
    shortest_cost = std::numeric_limits<uint_10_6>::max();

    paths = calcPaths();
    for (const auto &path : paths) {
        cost = 0;
        cost = 0;
        for (auto p : path) {
            if (p.first == direction_t::straight) {
                cost += p.second;
            } else {
                cost += p.second * radius;
            }
        }

#ifdef USE_RECORDER
        Recorder::getInstance()->saveData<double>(
            "Dubins::getShortestPath()::cost", cost);
#endif
        if (cost < shortest_cost) {
            shortest_path = path;
            shortest_cost = cost;
        }
    }

    return shortest_path;
}

// Construct the x, y, yaw path given a starting pose, Dubin's path and radius
// Arguments:
//      s: initial pose x, y, yaw
//      path: Dubin's path to construct
//      radius: turning radius of vehicle
// Returns:
//      vector of pose x, y, yaw
vector<Pose> Dubins::generatePath(Pose s, DubinsPath path, double radius) {
    vector<int_6_9> r_x, r_y;
    vector<int_4_11> r_yaw;
    Pose cur;
    Point center;
    int_3_12 yaw, ang, ang_start, ang_end;
    int_2_13 step;
    int tick;
    vector<Pose> ret;

    cur = s;
#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::generatePath()::cur[0]",
                                              cur[0]);
    Recorder::getInstance()->saveData<double>("Dubins::generatePath()::cur[0]",
                                              cur[1]);
    Recorder::getInstance()->saveData<double>("Dubins::generatePath()::cur[0]",
                                              cur[2]);
#endif
    yaw = s[2];
    for (auto p : path) {
        if (p.first == direction_t::straight) {
            if (p.second > 0) {
                tick = 1;
            } else {
                tick = -1;
            }
            for (int i = 0; i < p.second; i += tick) {
                r_x.push_back(cur[0] + cos(yaw) * i);
                r_y.push_back(cur[1] + sin(yaw) * i);
                r_yaw.push_back(yaw);
#ifdef USE_RECORDER
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_x[i]", cur[0] + cos(yaw) * i);
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_y[i]", cur[1] + sin(yaw) * i);
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_yaw[i]", yaw);
#endif
            }
            r_x.push_back(cur[0] + cos(yaw) * p.second);
            r_y.push_back(cur[1] + sin(yaw) * p.second);
            r_yaw.push_back(yaw);
#ifdef USE_RECORDER
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_x[i]", cur[0] + cos(yaw) * p.second);
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_y[i]", cur[1] + sin(yaw) * p.second);
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_yaw[i]", yaw);
#endif
        } else {
            center = calcTurnCenter(cur, p.first, radius);
            ang_start = atan2(static_cast<double>(cur[1] - center[1]),
                              static_cast<double>(cur[0] - center[0]));

#ifdef USE_RECORDER
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::ang_start", ang_start);
#endif
            if (p.first == direction_t::left) {
                ang_end = ang_start + p.second;
            } else {
                ang_end = ang_start - p.second;
            }
            if (ang_start < ang_end) {
                step = (1 / radius);
            } else {
                step = (-1 / radius);
            }
#ifdef USE_RECORDER
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::ang_end", ang_end);
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::step", step);
#endif
            ang = ang_start;
            for (int i = 0; i < (ang_end - ang_start) / step; i += 1) {
                r_x.push_back(center[0] + cos(ang) * radius);
                r_y.push_back(center[1] + sin(ang) * radius);
                r_yaw.push_back(yaw);
#ifdef USE_RECORDER
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_x[i]",
                    center[0] + cos(ang) * radius);
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_y[i]",
                    center[1] + sin(ang) * radius);
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::r_yaw[i]", yaw);
#endif
                yaw += step;
                ang += step;
#ifdef USE_RECORDER
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::yaw", yaw);
                Recorder::getInstance()->saveData<double>(
                    "Dubins::generatePath()::ang", ang);
#endif
            }

            r_x.push_back(center[0] + cos(ang_end) * radius);
            r_y.push_back(center[1] + sin(ang_end) * radius);
#ifdef USE_RECORDER
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_x[i]",
                center[0] + cos(ang_end) * radius);

            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_y[i]",
                center[1] + sin(ang_end) * radius);
#endif

            if (p.first == direction_t::left) {
                yaw = cur[2] + p.second;
            } else {
                yaw = cur[2] - p.second;
            }

            r_yaw.push_back(yaw);
#ifdef USE_RECORDER
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::yaw", yaw);
            Recorder::getInstance()->saveData<double>(
                "Dubins::generatePath()::r_yaw[i]", yaw);
#endif
        }
        cur.clear();
        cur.push_back(r_x.back());
        cur.push_back(r_y.back());
        cur.push_back(yaw);
#ifdef USE_RECORDER
        Recorder::getInstance()->saveData<double>(
            "Dubins::generatePath()::cur[0]", r_x.back());
        Recorder::getInstance()->saveData<double>(
            "Dubins::generatePath()::cur[0]", r_y.back());
        Recorder::getInstance()->saveData<double>(
            "Dubins::generatePath()::cur[0]", yaw);
#endif
    }
    for (size_t i = 0; i < r_x.size(); i++) {
        Pose p({r_x[i], r_y[i], r_yaw[i]});
        ret.push_back(p);
    }
    return ret;
}

// Mod theta (radians) to range [0, 2 PI)
int_3_12 Dubins::mod2Pi(int_3_12 theta) {
    return theta - 2.0 * M_PI * floor(theta / 2.0 / M_PI);
}

// Calculate the delta in x, y, yaw between the start and end
Pose Dubins::calcEnd() {
    int_6_9 ex, ey, lex, ley;
    int_3_12 yaw, leyaw;
    Pose dend;

    ex = end[0] - start[0];
    ey = end[1] - start[1];
    yaw = start[2];

    lex = (cos(yaw) * ex + sin(yaw) * ey) / radius;
    ley = (-sin(yaw) * ex + cos(yaw) * ey) / radius;
    leyaw = end[2] - start[2];

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::ex", ex);
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::ey", ey);
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::yaw", yaw);
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::lex", lex);
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::ley", ley);
    Recorder::getInstance()->saveData<double>("Dubins::calcEnd()::leyaw",
                                              leyaw);
#endif

    dend.push_back(lex);
    dend.push_back(ley);
    dend.push_back(leyaw);
    return dend;
}

// Compute Dubin's path for L(eft), S(traight), L(eft) sequence
DubinsPath Dubins::calcLSL(Pose e) {
    int_6_9 x, y, u;
    int_3_12 yaw, t, v;
    DubinsPath dp;

    yaw = e[2];
    x = e[0] - sin(yaw);
    y = e[1] - 1 + cos(yaw);
    // u = sqrt(pow(x, 2) + pow(y, 2));
    u = sqrt(x * x + y * y);
    t = mod2Pi(atan2(static_cast<double>(y), static_cast<double>(x)));
    v = mod2Pi(yaw - t);

    DubinsPoint first(direction_t::left, t);
    DubinsPoint second(direction_t::straight, u * radius);
    DubinsPoint third(direction_t::left, v);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::yaw", yaw);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::x", x);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::y", y);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::u", u);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::t", t);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSL()::v", v);
#endif

    dp.push_back(first);
    dp.push_back(second);
    dp.push_back(third);
    return dp;
}

// Compute Dubin's path for R(ight), S(traight), R(ight) sequence
DubinsPath Dubins::calcRSR(Pose e) {
    Pose e_prime(e);
    DubinsPath path;

    e_prime[1] = -e[1];
    e_prime[2] = mod2Pi(-e[2]);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcRSR()::e_prime[1]",
                                              e_prime[1]);
    Recorder::getInstance()->saveData<double>("Dubins::calcRSR()::e_prime[2]",
                                              e_prime[2]);
#endif

    path = calcLSL(e_prime);
    path[0].first = direction_t::right;
    path[2].first = direction_t::right;
    return path;
}

// Compute Dubin's path for L(eft), S(traight), R(ight) sequence
DubinsPath Dubins::calcLSR(Pose e) {
    int_6_9 x, y, u1_square, u;
    int_3_12 yaw, t, v, theta, t1;
    DubinsPoint first, second, third;
    DubinsPath dp;

    yaw = e[2];
    x = e[0] + sin(yaw);
    y = e[1] - 1 - cos(yaw);
    u1_square = x * x + y * y; // TODO:

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::yaw", yaw);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::x", x);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::y", y);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::u1_square",
                                              u1_square);
#endif

    if (u1_square <= 4.0) {
        return dp;
    }
    t1 = mod2Pi(atan2(static_cast<double>(y), static_cast<double>(x)));
    u = sqrt(static_cast<double>(u1_square - 4));
    theta = mod2Pi(atan(2 / static_cast<double>(u)));
    t = mod2Pi(t1 + theta);
    v = mod2Pi(t - yaw);
    first = make_pair(direction_t::left, t);
    second = make_pair(direction_t::straight, u * radius);
    third = make_pair(direction_t::right, v);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::t1", t1);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::u", u);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::theta",
                                              theta);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::t", t);
    Recorder::getInstance()->saveData<double>("Dubins::calcLSR()::v", v);
#endif

    dp.push_back(first);
    dp.push_back(second);
    dp.push_back(third);

    return dp;
}

// Compute Dubin's path for R(ight), S(traight), L(eft) sequence
DubinsPath Dubins::calcRSL(Pose e) {
    Pose e_prime(e);
    DubinsPath path;

    e_prime[1] = -e[1];
    e_prime[2] = mod2Pi(-e[2]);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcRSL()::e_prime[1]",
                                              e_prime[1]);
    Recorder::getInstance()->saveData<double>("Dubins::calcRSL()::e_prime[2]",
                                              e_prime[2]);
#endif

    path = calcLSR(e_prime);
    if (path.empty()) {
        return path;
    }
    path[0].first = direction_t::right;
    path[2].first = direction_t::left;
    return path;
}

// Compute Dubin's path for L(eft), R(ight), L(eft) sequence
DubinsPath Dubins::calcLRL(Pose e) {
    int_6_9 x, y, u1;
    int_3_12 yaw, t1, theta, t, v, u;
    DubinsPoint first, second, third;
    DubinsPath dp;

    yaw = e[2];
    x = e[0] - sin(yaw);
    y = e[1] - 1 + cos(yaw);
    u1 = sqrt(x * x + y * y);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::yaw", yaw);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::x", x);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::y", y);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::u1", u1);
#endif

    if (u1 > 4.0) {
        return dp;
    }
    t1 = atan2(static_cast<double>(y), static_cast<double>(x));
    theta = acos(static_cast<double>(u1) / 4.0);
    t = mod2Pi(M_PI_2 + t1 + theta);
    u = mod2Pi(M_PI + 2 * theta);
    v = mod2Pi(M_PI_2 - t1 + theta + yaw);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::t1", t1);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::theta",
                                              theta);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::t", t);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::u", u);
    Recorder::getInstance()->saveData<double>("Dubins::calcLRL()::v", v);
#endif

    first = make_pair(direction_t::left, t);
    second = make_pair(direction_t::right, u);
    third = make_pair(direction_t::left, v);

    dp.push_back(first);
    dp.push_back(second);
    dp.push_back(third);

    return dp;
}

// Compute Dubin's path for R(ight), L(eft), R(ight) sequence
DubinsPath Dubins::calcRLR(Pose e) {
    Pose e_prime(e);
    DubinsPath path;

    e_prime[1] = -e[1];
    e_prime[2] = mod2Pi(-e[2]);

#ifdef USE_RECORDER
    Recorder::getInstance()->saveData<double>("Dubins::calcRLR()::e_prime[1]",
                                              e_prime[1]);
    Recorder::getInstance()->saveData<double>("Dubins::calcRLR()::e_prime[2]",
                                              e_prime[2]);
#endif

    path = calcLRL(e_prime);
    if (path.empty()) {
        return path;
    }
    path[0].first = direction_t::right;
    path[1].first = direction_t::left;
    path[2].first = direction_t::right;
    return path;
}

// Compute all possible Dubin's Paths from start to end
vector<DubinsPath> Dubins::calcPaths() {
    DubinsPath lsl, rsr, lsr, rsl, rlr, lrl;
    vector<DubinsPath> all_paths;
    Pose e;

    e = calcEnd();
    lsl = calcLSL(e);
    rsr = calcRSR(e);
    lsr = calcLSR(e);
    rsl = calcRSL(e);
    rlr = calcRLR(e);
    lrl = calcLRL(e);

    all_paths.push_back(lsl);
    all_paths.push_back(rsr);
    if (!lsr.empty())
        all_paths.push_back(lsr);
    if (!rsl.empty())
        all_paths.push_back(rsl);
    if (!rlr.empty())
        all_paths.push_back(rlr);
    if (!lrl.empty())
        all_paths.push_back(lrl);

    return all_paths;
}