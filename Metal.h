//
// Created by alecg on 7/27/2022.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H


#include "Material.h"
#include "Vector3.h"

class Metal : public Material {

public:
    Metal(const Color& albedo, double perturbation);

    virtual bool scatter(const Ray& incident, const hit& hit_record, Color& attenuation, Ray& scatter) const override;

public:
    Color albedo;
    double perturbation;

};


#endif //RAYTRACER_METAL_H
