//
// Created by Marci on 5/26/2024.
//

#ifndef GRAPHICS_LINE_H
#define GRAPHICS_LINE_H

#include "framework.h"

class Line {
    vec3 implicit;
    vec3 p;
    vec3 v;
public:
    Line(vec2 p1, vec2 p2);
    vec2 Intersect(Line l);
    void Move(vec2 coords);
    bool IsClose(vec2 coords);
    vec4 generateEnds();
};


#endif //GRAPHICS_LINE_H
