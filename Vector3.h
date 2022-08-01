//
// Created by alecg on 7/10/2022.
// [Summary]: Basic Vector3 class for use in the One Weekend Raytracer project. Based on the work of Peter Shirley at
//            https://raytracing.github.io/books/RayTracingInOneWeekend.html. Extended and modified for my own
//            implementation. - alecg
//
#pragma once

#include <iostream>

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#pragma region Vector3
class Vector3 {
public:
    Vector3();
    Vector3(double new_x, double new_y, double new_z);

    double x() const;
    double y() const;
    double z() const;

    inline double r() const { return x(); }
    inline double g() const { return y(); }
    inline double b() const { return z(); }


    Vector3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vector3& operator+=(const Vector3 &v2);
    Vector3& operator*=(double c);
    Vector3& operator/=(double c);

    Vector3 ElementwiseMultiply(Vector3 v2);
    double Dot(Vector3 v2) const;

    double length() const;

    double length_squared() const;

    bool b_near_zero() const;

    static Vector3 reflect(const Vector3& v, const Vector3& normal);

public:
    double e[3];

    static Vector3 refract(const Vector3 &v, const Vector3 &normal, double eta_over_eta_prime);
};

using Point3= Vector3;
using Color= Vector3;


inline std::ostream& operator<<(std::ostream &os, const Vector3 &v) {
    return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3 &v0, const Vector3 &v1) {
    return {v0.x() + v1.x(), v0.y() + v1.y(), v0.z() + v1.z()};
}

inline Vector3 operator-(const Vector3 &v0, const Vector3 &v1) {
    return {v0.x() - v1.x(), v0.y() - v1.y(), v0.z() - v1.z()};
}

inline Vector3 operator*(const Vector3 &v0, const Vector3 &v1) {
    return {v0.x() * v1.x(), v0.y() * v1.y(), v0.z() * v1.z()};
}

inline Vector3 operator/(const Vector3 &v0, const Vector3 &v1) {
    return {v0.x() / v1.x(), v0.y() / v1.y(), v0.z() / v1.z()};
}


inline Vector3 operator*(const Vector3 &v, double c) {
    return {v.x() * c, v.y() * c, v.z() * c};
}

inline Vector3 operator*(double c, const Vector3 &v) {
    return v * c;
}

inline Vector3 operator/(const Vector3 &v, double c) {
    return (1/c) * v;
}


inline double dot(const Vector3 &v0, const Vector3 &v1) {
    return v0.x() * v1.x() + v0.y() * v1.y() + v0.z() * v1.z();
}

inline Vector3 cross(const Vector3 &v0, const Vector3 &v1) {
    return { v0.y() * v1.z() - v0.z() * v1.y(),
             v0.z() * v1.x() - v0.x() * v1.z(),
             v0.x() * v1.y() - v0.y() * v1.x() };
}

inline Vector3 unit_vector(Vector3 v) {
    return v / v.length();
}

#endif //RAYTRACER_VECTOR3_H
#pragma endregion Vector3