//
// Created by Marci on 5/28/2024.
//

#include "LagrangeCurve.h"

vec2 LagrangeCurve::r(float t) {
    vec2 r = vec2(0,0);
    for(size_t i = 0; i < cps.size(); i++){
        r = r + cps.at(i) *L(i,t);
    }
    return r;
}

float LagrangeCurve::L(size_t i, float t) {
    float Li = 1;
    for(size_t j = 0; j < ts.size(); j++){
        if(i != j) Li *= (t - ts.at(j)) / (ts.at(i) - ts.at(j));
    }
    return Li;
}

LagrangeCurve::LagrangeCurve(unsigned int shader) : ParametricCurve(shader) {

}
