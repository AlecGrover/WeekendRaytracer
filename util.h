//
// Created by alecg on 7/18/2022.
//

#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H

#include <limits>
#include <cstdlib>
#include <random>
#include "Ray.h"
#include "Vector3.h"

// Constants
const double MAX_DOUBLE= std::numeric_limits<double>::max();
const double DOUBLE_EPSILON= std::numeric_limits<double>::epsilon();
const double INFINITY_DOUBLE= std::numeric_limits<double>::infinity();
const double PI_DOUBLE= 3.14159265358979323846;
const Vector3 ZERO_VECTOR= Vector3(0, 0, 0);

enum diffuse_renderer {
    NORMALIZED_UNIT_SPHERICAL,
    NORMALIZED_RANDOM_POLAR,
    HEMISPHERICAL
};


// Utility Functions
inline double deg2rad(double degrees) {
    return degrees * PI_DOUBLE / 180.0;
}

inline double random_normalized_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double cpp_random_normalized() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937_64 generator;
    return distribution(generator);
}

inline double random_range(double min, double max) {
    return min + (max - min) * cpp_random_normalized();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline Vector3 random_polar_vector(double radius= 1, Vector3 offset= ZERO_VECTOR) {

    double x_z_angle= random_range(0, 2 * PI_DOUBLE);
    double x_y_angle= random_range(0, 2 * PI_DOUBLE);

    Vector3 vector_out= unit_vector(Vector3(sin(x_z_angle) * cos(x_y_angle),
                                sin(x_z_angle) * sin(x_y_angle),
                                cos(x_z_angle)));
    // Generates two random polar angles, converts them to a random cartesian coordinate, then sets it to a given length
    return vector_out * radius + offset;

}

inline Vector3 random_in_unit_sphere() {
    while(true) {
        auto p = Vector3(random_range(0, 1), random_range(0, 1), random_range(0, 1));
        if (p.length_squared() >= 1) continue;
        return unit_vector(p);
    }
}

inline Vector3 random_in_unit_sphere_normalized() {
    return unit_vector(random_in_unit_sphere());
}

inline Vector3 random_in_hemisphere(const Vector3& normal) {
    Vector3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

#endif //RAYTRACER_UTIL_H
