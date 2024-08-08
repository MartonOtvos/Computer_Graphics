//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_PLANE_H
#define GRAPHICS_PLANE_H
#include "RayTraceFramework.h"

class Plane : public Intersectable {
    Material* secondMaterial;
    vec3 normal;
    vec3 p0;
public:
    Plane(Material* material1, Material* material2, vec3 normal, vec3 p0);
    Hit Intersect(const Ray &ray) override;
};


#endif //GRAPHICS_PLANE_H
