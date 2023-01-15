#pragma once
#include <math>
#include "pcg_extras.hpp"
#include "pcg_random.hpp"
#include <random>
#include <cmath>

struct Point{
    double x;
    double y;

    Point();

    Point(double t_x, double t_y) {
        x=t_x;
        y=t_y;
    }

}