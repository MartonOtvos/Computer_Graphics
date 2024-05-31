//
// Created by Marci on 5/30/2024.
//

#ifndef GRAPHICS_STAR_H
#define GRAPHICS_STAR_H


#include "framework.h"
#include "ProceduralCircleLimitTexture.h"

using namespace std;

class Star {
    unsigned int shaderProgram;
    unsigned int vao;
    unsigned int vbo[2];
    unsigned int textureID;
    vector<vec2> vertices;
    vector<vec2> uvs;
    float schlank = 40;
    float phi = 0;
    float theta = 0;
    vec2 pos = vec2(0.4f,0.0f);
    ProceduralCircleLimitTexture* textureGenerator;
    int resolution = 300;


public:
    Star(unsigned int shader);

    void AlterTextureSamplingMode(unsigned int mode);
    void AlterTextureResolution(int d);
    void AlterSchlank(int d);
    void Draw();
    void Animate(float dt);
};


#endif //GRAPHICS_STAR_H
