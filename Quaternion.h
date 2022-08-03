//
// This is a custom Quaternion class for use in rotations primarily for the camera.
// Of note, there is a floating point error located somewhere within this which will cause
// some values intended to be zero to instead result in a value of 2.22045e-16. I believe
// this is likely caused by the degree to radian conversion, however I am ultimately unsure.
// I have spent a great deal of time researching and trialing solutions, but given that the
// scene is static, and I will not need to worry about a compounding rounding error, I have
// elected that the most prudent course of action is to simply leave it in place.
//
// HOWEVER: THIS MUST BE CLEAR. DO NOT USE THIS CLASS IN ANY GAMEPLAY SYSTEMS, THE FLOATING
//          POINT ERROR WILL ALMOST CERTAINLY COMPOUND OVER TIME. USE AN ESTABLISHED LIBRARY.
//
// Created by alecg on 8/2/2022.
//

#ifndef RAYTRACER_QUATERNION_H
#define RAYTRACER_QUATERNION_H

#include "Vector3.h"
#include "util.h"

class Quaternion {
public:
    double x;
    double y;
    double z;
    double w;
public:
    Quaternion();
    Quaternion(double x, double y, double z, double w);
    Quaternion(Vector3 v, double w);

    Vector3 get_vector() const;

    void normalize();
    double norm();
    double length() const;
    double squared_length() const;
    Quaternion inverse();
    void unit_normalize();

    // Returns the Quaternion with the VECTOR component inverted, the w component remains unchanged
    Quaternion operator-() const;

};

// This headache of a formula was kindly provided by confuted at https://www.cprogramming.com/tutorial/3d/quaternions.html
inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    auto out= Quaternion(
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
            q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
            );
    return out;
}

inline Quaternion operator*(const Quaternion& q, const double& c) {
    return {q.x * c, q.y * c, q.z * c, q.w * c};
}

inline Quaternion operator*(const double& c, const Quaternion& q) {
    return q * c;
}

inline Quaternion operator/(const Quaternion& q, const double& c) {
    auto inverse_c = 1.0 /c;
    return q * inverse_c;
}

inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
    return { q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w };
}

#endif //RAYTRACER_QUATERNION_H
