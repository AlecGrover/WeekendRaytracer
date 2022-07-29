//
// Created by alecg on 7/27/2022.
//

#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "util.h"
#include "Material.h"

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);
    bool scatter(const Ray& incident, const hit& hit_record, Color& attenuation, Ray& scatter) const override;

public:
    Color albedo;
};


#endif //RAYTRACER_LAMBERTIAN_H
