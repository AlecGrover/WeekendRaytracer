//
// Created by alecg on 7/29/2022.
//

#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H


#include "Material.h"
#include "Color.h"

class Dielectric : public Material {

public:
    Dielectric(Color tint, double index_of_refraction);
    virtual bool scatter(const Ray& incident, const hit& hit_record, Color& attenuation, Ray& scatter) const override;

public:
    Color tint;
    double index;

private:
    static double schlick_reflectance(double cosine, double refractive_index) {
        auto reflectance= (1 - refractive_index) / (1 + refractive_index);
        reflectance *= reflectance;
        return reflectance + (1 - reflectance) * pow((1 - cosine), 5);
    }
};



#endif //RAYTRACER_DIELECTRIC_H
