//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_CONE_H
#define GRAPHICS_CONE_H
#include "RayTraceFramework.h"


class Cone : public Intersectable {
    vec3 v;
    vec3 p;
    float size;
    float alpha;
public:
    Cone(Material *material, vec3 dir, vec3 p0, float size, float a);
    Hit Intersect(const Ray& ray) override;

};


#endif //GRAPHICS_CONE_H
