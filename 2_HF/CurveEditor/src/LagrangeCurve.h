//
// Created by Marci on 5/28/2024.
//

#ifndef GRAPHICS_LAGRANGECURVE_H
#define GRAPHICS_LAGRANGECURVE_H


#include "ParametricCurve.h"

class LagrangeCurve : public ParametricCurve {

    vec2 r(float t) override;
    float L(size_t i, float t);
public:
    explicit LagrangeCurve(unsigned int shader);
};


#endif //GRAPHICS_LAGRANGECURVE_H
