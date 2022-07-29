//
// Created by alecg on 7/27/2022.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "util.h"
#include "Shape.h"

struct hit;

class Material {

public:
    virtual bool scatter(const Ray& incident, const hit& hit_record, Color& attenuation, Ray& scatter) const = 0;

};


#endif //RAYTRACER_MATERIAL_H
