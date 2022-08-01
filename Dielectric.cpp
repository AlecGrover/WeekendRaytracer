//
// Created by alecg on 7/29/2022.
//

#include "Dielectric.h"


Dielectric::Dielectric(Color tint, double index_of_refraction)
: tint(tint),
index(fabs(index_of_refraction) > 0.001 ? index_of_refraction : copysign(0.001, index_of_refraction)) {};

bool Dielectric::scatter(const Ray &incident, const hit &hit_record, Color &attenuation, Ray &scatter) const {
    attenuation= tint;

    double refraction_ratio= hit_record.front_face ? (1.0 / index) : index;
    Vector3 u_direction= unit_vector(incident.get_direction());

    double cos_t= fmin(dot(-u_direction, hit_record.normal), 1.0);
    double sin_t= sqrt(1.0 - cos_t * cos_t);

    bool total_refraction= refraction_ratio * sin_t > 1.0;
    Vector3 direction= total_refraction || schlick_reflectance(cos_t, refraction_ratio) > random_normalized_double() ?
            Vector3::reflect(u_direction, hit_record.normal) :
            Vector3::refract(u_direction, hit_record.normal, refraction_ratio);
    scatter= Ray(hit_record.hit_location, direction);
    return true;
}
