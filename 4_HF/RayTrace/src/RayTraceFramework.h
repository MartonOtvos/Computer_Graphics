//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_RAYTRACEFRAMEWORK_H
#define GRAPHICS_RAYTRACEFRAMEWORK_H

#include "framework.h"

struct Material{
    float n, k, shine;
    vec3 ka, kd, ks;
    bool reflective, refractive, rough;
    Material(float _n, float _k,float _shine, vec3 _ka, vec3 _kd, vec3 _ks, bool _reflective, bool _refractive, bool _rough) {
        n = _n;
        k = _k;
        shine = _shine;
        ka = _ka;
        kd = _kd;
        ks = _ks;
        reflective = _reflective;
        refractive = _refractive;
        rough = _rough;
    }
};

struct Hit{
    float t;
    vec3 position, normal;
    Material* material;
    Hit() { t = -1; }
};

struct Ray{
    vec3 start, direction;
    bool out;
    Ray(vec3 _start, vec3 dir, bool _out) : start(_start), direction(dir), out(_out) {}
};

struct DirectionalLight{
    vec3 direction;
    vec3 Le;
    DirectionalLight(vec3 dir, vec3 _Le) : direction(normalize(dir)), Le(_Le) {}
};

class Intersectable{
protected:
    Material* material;
public:
    explicit Intersectable(Material* mat) : material(mat) {}
    virtual Hit Intersect(const Ray& ray) = 0;
};

struct Random{
    static float rnd() { return (float)rand() / RAND_MAX;}
};

const float epsilon = 0.0001f;


#endif //GRAPHICS_RAYTRACEFRAMEWORK_H
