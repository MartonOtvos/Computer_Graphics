//
// Created by Marci on 6/1/2024.
//

#include "Cylinder.h"

Cylinder::Cylinder(Material *material, vec3 dir, vec3 p0, float r, float size) : Intersectable(material) {
    v = normalize(dir);
    p = p0;
    R = r;
    this->size = size;
}


Hit Cylinder::Intersect(const Ray &ray) {

    vec3 s = ray.start;
    vec3 d = ray.direction;
    vec3 m = s - p;
    float a = dot((d - dot(d,v) * v),(d - dot(d,v) * v));
    float b = 2.0f * dot((m - dot(m,v) * v), d - dot(d,v) * v);
    float c = dot(m - dot(m,v) * v,m - dot(m,v) * v) - powf(R,2);

    float disc = powf(b,2) - 4.0f * a * c;

    if(disc < 0) return Hit();
    disc = sqrtf(disc);

    float t1 = (-1.0f * b + disc) / (2.0f * a);
    float t2 = (-1.0f * b - disc) / (2.0f * a);

    if(t1 > 0 || t2 > 0){
        float t = (t1 < t2 && t1 > 0) ? t1 : t2;
        Hit hit;
        hit.t = t;
        hit.position = s + d * t;
        hit.material = material;
        vec3 normal = hit.position - p - (dot(hit.position-p,v) * v);
        hit.normal = normalize(normal);
        if(dot(hit.position - p,v) >= 0 && dot(hit.position - p,v) < size) return hit;
    }

    vec3 topPoint = p + v * size;
    float denom = dot(topPoint - p, ray.direction);
    if (denom != 0) {
        float t = dot(topPoint - ray.start, topPoint - p) / denom;
        if (t > 0) {
            vec3 hitPoint = ray.start + ray.direction * t;
            vec3 distToTop = hitPoint - topPoint;
            if (dot(distToTop, distToTop) <= R * R) {
                Hit hit;
                hit.t = t;
                hit.position = hitPoint;
                hit.normal = v; // The normal of the top plane is the same as the cylinder axis direction
                hit.material = material;
                return hit;
            }
        }
    }

    vec3 bottomPoint = p;
    float denom2 = dot(bottomPoint - ray.start, v);
    if (denom2 != 0) {
        float t = dot(bottomPoint - ray.start, v) / denom2;
        if (t > 0) {
            vec3 hitPoint = ray.start + ray.direction * t;
            vec3 distToBottom = hitPoint - bottomPoint;
            if (dot(distToBottom, distToBottom) <= R * R) {
                Hit hit;
                hit.t = t;
                hit.position = hitPoint;
                hit.normal = -v; // The normal of the bottom plane is opposite to the cylinder axis direction
                hit.material = material;
                return hit;
            }
        }
    }




    return Hit();
}

