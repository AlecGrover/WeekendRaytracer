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

inline bool get_valid_t_simplified(const double a, const double half_b, const double c, const double t_min,
                                   const double t_max, double& t_out) {
    auto discriminant= half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto root= std::sqrt(discriminant);
    double sub= (-half_b - root) / a;
    if (sub >= t_min && sub <= t_max) {
        t_out= sub;
        return true;
    }

    double add=  (-half_b + root) / a;
    if (add >= t_min && add <= t_max) {
        t_out= add;
        return true;
    }

    return false;
}

#endif //RAYTRACER_QUADRATICHELPER_H
