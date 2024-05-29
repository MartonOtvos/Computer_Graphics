//
// Created by Marci on 5/29/2024.
//

#include "CatmullRomSpline.h"

vec2 CatmullRomSpline::r(float t) {

    for(unsigned int i = 0; i < cps.size() - 1; i++){
        if(ts.at(i) <= t && t <= ts.at(i+1)){

            vec2 r0 = cps.at(i);
            vec2 r1 = cps.at(i+1);
            float t0 = ts.at(i);
            float t1 = ts.at(i+1);

            vec2 vP = vec2(0,0);
            if(i > 0){
                vP = (r0 - cps.at(i-1)) / (t0 - ts.at(i-1));
            }

            vec2 vC = (r1 - r0) / (t1 - t0);

            vec2 vN = vec2(0,0);
            if(i < cps.size()-2){
                vN = (cps.at(i+2) - r1) / (ts.at(i+2) - t1);
            }

            vec2 v0 = (vP + vC) * (1 - tension) * 0.5f;
            vec2 v1 = (vC + vN) * (1 - tension) * 0.5f;


            return H(r0,v0,t0,r1,v1,t1,t);
        }

    }
    return cps.at(0);


}

vec2 CatmullRomSpline::H(vec2 p0, vec2 v0, float t0, vec2 p1, vec2 v1, float t1, float t) {
    vec2 a0 = p0;
    vec2 a1 = v0;
    vec2 a2 = ((3 * (p1 - p0)) / pow(t1 - t0, 2)) - (((v1 + 2 * v0)) / (t1 - t0));
    vec2 a3 = ((2 * (p0 - p1)) / pow(t1 - t0, 3)) + (((v1 + v0)) / pow(t1 - t0, 2));
    return a3 * pow(t - t0, 3) + a2 * pow(t - t0, 2) + a1 * (t - t0) + a0;
}


CatmullRomSpline::CatmullRomSpline(unsigned int shader) : ParametricCurve(shader) {}
