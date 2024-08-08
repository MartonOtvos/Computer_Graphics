//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_CYLINDER_H
#define GRAPHICS_CYLINDER_H
#include "RayTraceFramework.h"

class Cylinder : public Intersectable{
    vec3 v;
    vec3 p;
    float R, size;
public:
    Cylinder(Material* material, vec3 dir, vec3 p0, float r, float size);
    Hit Intersect(const Ray& ray) override;

};


#endif //GRAPHICS_CYLINDER_H
