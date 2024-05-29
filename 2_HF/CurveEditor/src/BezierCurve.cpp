//
// Created by Marci on 5/29/2024.
//

#include "BezierCurve.h"

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

vec2 BezierCurve::r(float t) {
    vec2 r = vec2(0,0);
    for(size_t i = 0; i < cps.size(); i++){
        r = r + cps.at(i) * B(i, t);
    }
    return r;
}

float BezierCurve::B(unsigned int i, float t) {
    int n = cps.size()-1;
    float binom = 1;
    for(int j = 1; j <= i; j++) binom *= (float)(n-j+1)/j;
    return binom * pow(t,i) * pow((1-t),(n-i));
}



BezierCurve::BezierCurve(unsigned int shader) : ParametricCurve(shader) {}
