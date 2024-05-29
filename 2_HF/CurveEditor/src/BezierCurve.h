//
// Created by Marci on 5/29/2024.
//

#ifndef GRAPHICS_BEZIERCURVE_H
#define GRAPHICS_BEZIERCURVE_H


#include "ParametricCurve.h"

class BezierCurve : public ParametricCurve {
    vec2 r(float t) override;
    float B(unsigned int, float t);
public:
    explicit BezierCurve(unsigned int shader);
};


#endif //GRAPHICS_BEZIERCURVE_H
