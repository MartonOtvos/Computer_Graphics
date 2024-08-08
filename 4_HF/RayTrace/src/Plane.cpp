//
// Created by Marci on 6/1/2024.
//

#include "Plane.h"

Plane::Plane(Material *material1, Material *material2, vec3 normal, vec3 p0) : Intersectable(material1), secondMaterial(material2) {
    this->normal = normal;
    this->p0 = p0;
}

Hit Plane::Intersect(const Ray &ray) {
    Hit hit;

    float denom = dot(normal,ray.direction);
    if(denom == 0){
        return Hit();
    }
    float t = (dot(p0,normal) - dot(ray.start,normal)) / denom;
    if(t > 0){
        hit.t = t;
        hit.position = ray.start + ray.direction * t;
        hit.normal = normal;



        if (fabs(hit.position.x) <= 10 && fabs(hit.position.z) <= 10) {
            int localX = ((int)floor(hit.position.x) % 2 + 2) % 2;
            int localZ = ((int)floor(hit.position.z) % 2 + 2) % 2;

            if(localX == localZ){
                hit.material = secondMaterial;
            }else{
                hit.material = material;
            }
           return hit;
        }
    }
    return Hit();
}