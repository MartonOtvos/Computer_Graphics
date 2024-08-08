//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_RAYTRACEFRAMEWORK_H
#define GRAPHICS_RAYTRACEFRAMEWORK_H

#include "framework.h"

struct Material{
    float shine;
    vec3 ka, kd, ks, n, k;
    bool reflective, refractive, rough;
    Material(vec3 _n, vec3 _k,float _shine, vec3 _ka, vec3 _kd, vec3 _ks, bool _reflective, bool _refractive, bool _rough) {
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
    Ray(vec3 _start, vec3 dir, bool _out) : start(_start), direction(normalize(dir)), out(_out) {}
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


struct smoothSurfaceFunctions{
    static vec3 refract(vec3 dir, vec3 normal, float ns){
        float cosa = -dot(dir, normal);
        float disc = 1 - ( 1 - powf( cosa, 2 ) ) / ns / ns;
        if(disc < 0) return vec3(0,0,0);
        return dir / ns + normal * ( cosa / ns - sqrtf(disc));
    }

    static vec3 reflect(vec3 dir, vec3 normal){
        return dir - normal * dot(normal, dir) * 2.0f;
    }

    static vec3 Fresnel(vec3 dir, vec3 normal, vec3 n, vec3 kappa){
        float cosa = -1* dot(dir,normal);
        vec3 one(1,1,1);
        vec3 F0 = ( (n - one) * (n - one) + kappa * kappa ) / ( (n + one) * (n + one) + kappa * kappa );
        return F0 + (one - F0) * powf(1-cosa, 5);
    }
};

struct Sphere : public Intersectable {
    vec3 center;
    float radius;

    Sphere(const vec3 &_center, float _radius, Material *_material) : Intersectable(_material) {
        center = _center;
        radius = _radius;
        material = _material;
    }

    Hit Intersect(const Ray& ray) override {
        Hit hit;
        vec3 dist = ray.start - center;
        float a = dot(ray.direction, ray.direction);
        float b = dot(dist, ray.direction) * 2.0f;
        float c = dot(dist, dist) - radius * radius;
        float discr = b * b - 4.0f * a * c;
        if (discr < 0) return hit;
        float sqrt_discr = sqrtf(discr);
        float t1 = (-b + sqrt_discr) / 2.0f / a;	// t1 >= t2 for sure
        float t2 = (-b - sqrt_discr) / 2.0f / a;
        if (t1 <= 0) return hit;
        hit.t = (t2 > 0) ? t2 : t1;
        hit.position = ray.start + ray.direction * hit.t;
        hit.normal = (hit.position - center) * (1.0f / radius);
        hit.material = material;
        return hit;
    }
};

const float epsilon = 0.001f;


#endif //GRAPHICS_RAYTRACEFRAMEWORK_H
