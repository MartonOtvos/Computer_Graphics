//
// Created by Marci on 5/26/2024.
//

#include "Line.h"

Line::Line(vec2 p1, vec2 p2) {
    v = normalize(p1-p2);
    p = p1;
    vec3 n = vec3(-v.y,v.x,0);
    implicit.x = -n.x;
    implicit.y = n.y;
    implicit.z = dot(-n, p);
    printf("Line added:\n");
    printf("        Implicit: %.2f x + %.2f y + %.2f = 0\n",implicit.x,implicit.y,implicit.z);
    printf("        Parametric: r(t) = (%.2f, %.2f) + (%.2f, %.2f)t\n",p.x,p.y,v.x,v.y);

}

vec2 Line::Intersect(Line l) {
    //float t = (-implicit.x * l.p.x - implicit.y * l.p.y - implicit.z) / (implicit.y * l.v.y + implicit.x * l.v.x);
    //vec2 result = vec2(l.p.x + (l.v.x * t),l.p.y + (l.v.y * t));


    //Parametric
    float t = (-p.y * l.v.x + l.p.y * l.v.x + l.v.y * p.x - l.v.y * l.p.x) / (v.y * l.v.x - v.x * l.v.y);
    vec2 result = vec2(p.x + (v.x * t),p.y + (v.y * t));


    return result;
}

void Line::Move(vec2 coords) {
    p = coords;
    vec3 n = vec3(-v.y,v.x,0);
    implicit.z = dot(-n, p);
}

bool Line::IsClose(vec2 coords) {

    vec3 w = vec3(coords.x,coords.y,0) - p;
    float distance = length(w - (dot(w,v) * v));
    if(distance < 0.05) return true;
    return false;
}

vec4 Line::generateEnds() {
    return {p.x + v.x*1000,p.y+v.y*1000,p.x + v.x*-1000,p.y+v.y*-1000};
}
