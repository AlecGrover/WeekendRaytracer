// This class features a system to define the rotation of an object in 3D space and perform Quaternion rotation with
// an Euler vector input. I think it works..
// Created by alecg on 8/2/2022.
//

#ifndef RAYTRACER_ROTATION_H
#define RAYTRACER_ROTATION_H


#include "Vector3.h"

class Rotation {

public:
    Rotation();
    void rotate(Vector3 rotation);

public:
    Vector3 right;
    Vector3 forward;
    Vector3 up;


};


#endif //RAYTRACER_ROTATION_H
