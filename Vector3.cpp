//
// Created by alecg on 7/10/2022.
// [Summary]: Implementations for the Vector3.h header file. See that file for further information. - alecg
//

#include "Vector3.h"
#include <cmath>

#pragma region Vector3



#pragma endregion Vector3

Vector3::Vector3() : e{0, 0, 0} { }
Vector3::Vector3(double new_x, double new_y, double new_z) : e{new_x, new_y, new_z} { }

double Vector3::x() const {
    return e[0];
}

double Vector3::y() const {
    return e[1];
}

double Vector3::z() const {
    return e[2];
}

Vector3 Vector3::operator-() const {
    return Vector3(-e[0], -e[1], -e[2]);
}

double Vector3::operator[](int i) const {
    return e[i];
}

double &Vector3::operator[](int i) {
    return e[i];
}

Vector3 &Vector3::operator+=(const Vector3 &v2) {
    e[0] += v2.x();
    e[1] += v2.y();
    e[2] += v2.z();
    return *this;
}

Vector3 &Vector3::operator*=(const double c) {
    e[0] *= c;
    e[1] *= c;
    e[2] *= c;
    return *this;
}

Vector3 &Vector3::operator/=(const double c) {
    e[0] /= c;
    e[1] /= c;
    e[2] /= c;
    return *this;
}

Vector3 Vector3::ElementwiseMultiply(const Vector3 v2) {
    e[0] *= v2.x();
    e[1] *= v2.y();
    e[2] *= v2.z();
    return *this;
}

double Vector3::Dot(const Vector3 v2) const {
    double sum= 0;
    sum += x() * v2.x();
    sum += y() * v2.y();
    sum += z() * v2.z();
    return sum;
}

double Vector3::length() const {
    return std::sqrt(length_squared());
}

double Vector3::length_squared() const {
    return this->Dot(*this);
}

bool Vector3::b_near_zero() const {
    const auto effective_epsilon = 1e-8;
    return(fabs(e[0]) < effective_epsilon
        && fabs(e[1]) < effective_epsilon
        && fabs(e[2]) < effective_epsilon);
}

Vector3 Vector3::reflect(const Vector3 &v, const Vector3 &normal) {
    return v - 2.0 * dot(v, normal) * normal;
}














