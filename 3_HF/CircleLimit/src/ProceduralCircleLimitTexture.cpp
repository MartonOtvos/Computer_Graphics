//
// Created by Marci on 5/30/2024.
//

#include "ProceduralCircleLimitTexture.h"

vec2 pointOnCircle(float r, int phi){
    vec2 p;
    float rad = (float) phi * (M_PI / 180.0f);
    p.x = r * cosf(rad);
    p.y = r * sinf(rad);
    return p;
}

vec4 constructCircle(vec2 p){
    float op1 = 1/length(p);
    vec2 p1 = op1 * normalize(p);
    float r = length(p1-p)/2;
    vec2 c = normalize(p) * (r + length(p));

    return {c.x,c.y,r,0};
}

ProceduralCircleLimitTexture::ProceduralCircleLimitTexture() {
    for(int i = 0; i < 360; i+=40){
        float dH = 0.5f;
        float dP = sinh(dH) / (1 + cosh(dH));
        vec2 p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));

        dH = 1.5f;
        dP = sinh(dH) / (1 + cosh(dH));
        p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));

        dH = 2.5f;
        dP = sinh(dH) / (1 + cosh(dH));
        p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));

        dH = 3.5f;
        dP = sinh(dH) / (1 + cosh(dH));
        p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));

        dH = 4.5f;
        dP = sinh(dH) / (1 + cosh(dH));
        p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));

        dH = 5.5f;
        dP = sinh(dH) / (1 + cosh(dH));
        p = pointOnCircle(dP,i);
        circles.push_back(constructCircle(p));
    }
}



vector<vec4> ProceduralCircleLimitTexture::renderToTexture(int resolution) {
    vector<vec4> image;

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            float normi = ((2 *  (float) i + 1) / (float) resolution) - 1;
            float normj = ((2 * (float) j + 1) / (float) resolution) - 1;

            if(powf(normi,2) + powf(normj,2) - 1 >= 0){
                image.emplace_back(0,0,0,1);
            }else if(circleCount(vec2(normj,normi)) % 2 == 0){
                image.emplace_back(1,1,0,1);
            }else image.emplace_back(0,0,1,1);
        }
    }

    return image;
}

bool isInCircle(vec2 coords, vec4 circle){
    vec2 p = coords;
    vec2 c = vec2(circle.x,circle.y);
    float r = circle.z;
    float dist = powf(p.x -c.x,2) + powf(p.y -c.y,2) - powf(r,2);
    if(dist < 0) return true;
    return false;
}


int ProceduralCircleLimitTexture::circleCount(vec2 coords) {
    int count = 0;
    for(auto circle : circles){
        if(isInCircle(coords, circle)) count++;
    }
    return count;
}


