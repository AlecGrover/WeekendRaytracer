//
// Created by alecg on 7/27/2022.
//

#include "Lambertian.h"

Lambertian::Lambertian(const Color &albedo) : albedo(albedo) { }

bool Lambertian::scatter(const Ray &incident, const hit& hit_record, Color &attenuation, Ray &scatter) const {

    auto direction= hit_record.normal + random_polar_vector(1);
    if (direction.b_near_zero()) direction= hit_record.normal;
    scatter= Ray(hit_record.hit_location, direction);
    attenuation= albedo;
    return true;

}
