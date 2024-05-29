//
// Created by Marci on 5/29/2024.
//

#ifndef GRAPHICS_CATMULLROMSPLINE_H
#define GRAPHICS_CATMULLROMSPLINE_H


#include "ParametricCurve.h"

class CatmullRomSpline : public ParametricCurve{
    vec2 r(float t) override;
    vec2 H(vec2 p0, vec2 v0, float t0, vec2 p1, vec2 v1, float t1, float t);
public:
    explicit CatmullRomSpline(unsigned int shader);

};


#endif //GRAPHICS_CATMULLROMSPLINE_H
