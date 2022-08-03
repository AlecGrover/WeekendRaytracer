//
// Created by alecg on 7/10/2022.
// [Summary]: Implementations for the Vector3.h header file. See that file for further information. - alecg
//

#include "Vector3.h"
#include "Quaternion.h"
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

Vector3 Vector3::refract(const Vector3& v, const Vector3& normal, double eta_over_eta_prime) {
    auto cos_t= fmin(dot(-v, normal), 1.0);
    Vector3 perpendicular= eta_over_eta_prime * (v + cos_t * normal);
    Vector3 parallel= -sqrt(fabs(1.0 - perpendicular.length_squared())) * normal;
    return perpendicular + parallel;
}

void Vector3::normalize() {
    auto magnitude= length();
    e[0] /= magnitude;
    e[1] /= magnitude;
    e[2] /= magnitude;
}

// The quaternion rotation algorithm is based on the work of Harold Serrano at:
// https://www.haroldserrano.com/blog/developing-a-math-engine-in-c-implementing-quaternions
Vector3 Vector3::rotate_around_axis(Vector3 axis, double degrees) {
    Quaternion p((*this), 0);

    axis.normalize();

    Quaternion q(axis, degrees);
    q.unit_normalize();

    Quaternion q_inverse= q.inverse();

    Quaternion rotated= q * p * q_inverse;



    return rotated.get_vector();
}














