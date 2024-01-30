/*
How to compile this file:
clang++ -isystem /home/wenguang/installed/cnl/include -std=c++20 CNL_Test.cpp -o
CNL_Test
*/
#include "cnl/all.h"
#include <cmath>
#include <iostream>
// using cnl::power;
// using cnl::scaled_integer;

int main() {
    cnl::scaled_integer<uint16_t, cnl::power<-10>> a;
    a = 32.512;

    auto b = cnl::scaled_integer<uint16_t, cnl::power<-5>>{0};
    b = 23.52;

    std::vector<cnl::scaled_integer<uint16_t, cnl::power<-10>>> c;
    c.push_back(5.45 * 2.123);
    c.push_back(b);
    std::cout << c[0] << " represented by " << to_rep(c[0]) << std::endl;

    std::cout << (double)a;
}