// SEE HEADER FILE COMMENT FOR DETAILS AND FOR VITAL ERROR INFORMATION
// Sources:
// https://www.haroldserrano.com/blog/developing-a-math-engine-in-c-implementing-quaternions
// https://www.cprogramming.com/tutorial/3d/quaternions.html
// Created by alecg on 8/2/2022.
//

#include "Quaternion.h"

Quaternion::Quaternion() : x(1),y(0), z(0), w(0) { }

Quaternion::Quaternion(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) { }

Quaternion Quaternion::operator-() const {
    return { -x, -y, -z, w };
}

void Quaternion::normalize() {
    auto sq_length= squared_length();
    if (sq_length - 1 <= DOUBLE_EPSILON && sq_length - 1 > -DOUBLE_EPSILON) return;
    auto magnitude= sqrt(sq_length);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w= 1;
}

Quaternion Quaternion::inverse() {

    double absolute= this->squared_length();
    absolute= 1/absolute;

    return -(*this) * absolute;
}

double Quaternion::length() const {
    return sqrt(squared_length());
}

double Quaternion::squared_length() const {
    return x * x + y * y + z * z + w * w;
}

Quaternion::Quaternion(Vector3 v, double w) : x(v.x()), y(v.y()), z(v.z()), w(w) { }

Vector3 Quaternion::get_vector() const {
    return { x, y, z };
}

void Quaternion::unit_normalize() {
    double angle= deg2rad(w);
    auto vector= get_vector();
    vector.normalize();
    w= cos(angle * 0.5);
    vector*= sin(angle * 0.5);
    x= vector.x();
    y= vector.y();
    z= vector.z();
}

double Quaternion::norm() {
    double w2= w * w;
    double v_dot= get_vector().Dot(get_vector());
    return sqrt(w2 + v_dot);
}

const Quaternion ID_QUATERNION= Quaternion(0, 0, -1, 0);
