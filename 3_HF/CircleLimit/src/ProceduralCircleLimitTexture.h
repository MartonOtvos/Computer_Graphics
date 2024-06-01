//
// Created by Marci on 5/30/2024.
//

#ifndef GRAPHICS_PROCEDURALCIRCLELIMITTEXTURE_H
#define GRAPHICS_PROCEDURALCIRCLELIMITTEXTURE_H
#include "framework.h"

using namespace std;

class ProceduralCircleLimitTexture {
    vector<vec4> circles;
    int circleCount(vec2 coords);

public:
    ProceduralCircleLimitTexture();
    vector<vec4> renderToTexture(int resolution);
};


#endif //GRAPHICS_PROCEDURALCIRCLELIMITTEXTURE_H
