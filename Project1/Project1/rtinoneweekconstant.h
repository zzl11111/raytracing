#pragma once
#ifndef RTINONEWEEKCONSTANT_H
#define RTINONEWEEKCONSTANT_H
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include "ray.h"
//define the constant and the function we will use
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
inline double degree_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
	if (x < min)return min;
	if (x > max) return max;
	return x;

}
#endif