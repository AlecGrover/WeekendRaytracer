//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_QUADRATICHELPER_H
#define RAYTRACER_QUADRATICHELPER_H

#include <cmath>

inline double get_closest_t(double a, double b, double c) {
    auto discriminant= b * b - 4 * a * c;
    if (discriminant < 0) return -1;
    auto root = std::sqrt(discriminant);
    auto a2 = 2 * a;
    double sub = (-b - root) / a2;
    double add = (-b + root) / a2;

    return std::fmin(sub, add);
}

#endif //RAYTRACER_QUADRATICHELPER_H
