//
// Created by Marci on 6/1/2024.
//

#include "Cone.h"

Cone::Cone(Material *material, vec3 dir, vec3 p0, float size, float a) : Intersectable(material) {
    v = normalize(dir);
    p = p0;
    this->size = size;
    alpha = a;

}

Hit Cone::Intersect(const Ray &ray) {
    vec3 d = ray.direction;
    vec3 s = ray.start;
    float cosAlpha2 = cosf(alpha) * cosf(alpha);
    vec3 n = v;



    vec3 sp = s - p;

    // Correct calculation of quadratic coefficients
    float a = (dot(d, n) * dot(d, n)) - (dot(d, d) * cosAlpha2);
    float b = 2.0f * ((dot(sp, n) * dot(d, n)) - (dot(sp, d) * cosAlpha2));
    float c = (dot(sp, n) * dot(sp, n)) - (dot(sp, sp) * cosAlpha2);

    float disc = b * b - 4.0f * a * c;

    if (disc < 0) return Hit();  // No intersection
    disc = sqrtf(disc);
    float t1 = (-b + disc) / (2.0f * a);
    float t2 = (-b - disc) / (2.0f * a);

    float t = -1;
    if(t1 > 0 && t2 > 0) t = std::min(t1,t2);
    if(t1 < 0 && t2 > 0) t = t2;
    if(t1 > 0 && t2 < 0) t = t1;
    if (t < 0) return Hit();  // Both t1 and t2 are negative

    Hit hit;
    hit.t = t;
    hit.position = s + d * t;

    // Calculate the normal at the intersection point
    vec3 r = hit.position;
    vec3 rp = r - p;
    if(dot(r - p,n) > size || dot(r - p,n) < 0) return Hit();
    float rpDotN = dot(rp, n);

    vec3 normal = rpDotN * n * 2 - 2 * rp * cosAlpha2;
    hit.normal = normalize(normal);
    hit.material = material;

    return hit;
}
