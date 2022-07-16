//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "Vector3.h"

class Ray {
public:
    Ray();
    Ray(const Point3& origin, const Vector3& direction);

    Point3 get_origin() const;
    Vector3 get_direction() const;

    void set_origin(Point3 new_origin);
    void set_direction(Vector3 new_direction);

    Point3 at(double t) const;

protected:
    Point3 origin;
    Vector3 direction;
};


#endif //RAYTRACER_RAY_H
