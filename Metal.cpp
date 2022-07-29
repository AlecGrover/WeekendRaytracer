//
// Created by alecg on 7/27/2022.
//

#include "Metal.h"

Metal::Metal(const Color &albedo, double perturbation) : albedo(albedo), perturbation(perturbation < 1 ? perturbation : 1) { }

bool Metal::scatter(const Ray &incident, const hit &hit_record, Color &attenuation, Ray &scatter) const {

    Vector3 reflection= Vector3::reflect(unit_vector(incident.get_direction()), hit_record.normal);
    scatter= Ray(hit_record.hit_location, reflection + perturbation * random_polar_vector(1));
    attenuation= albedo;
    return (dot(scatter.get_direction(), hit_record.normal)) > 0;
}
