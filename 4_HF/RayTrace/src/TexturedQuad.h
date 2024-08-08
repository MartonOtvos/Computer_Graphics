//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_TEXTUREDQUAD_H
#define GRAPHICS_TEXTUREDQUAD_H
#include "Scene.h"

class TexturedQuad {
    vec2 vertices[4];
    vec2 uvs[4];
    unsigned int shaderProgram;
    unsigned int vao, textureID;
    unsigned int vbo[2];
    Scene* scene;
public:
    explicit TexturedQuad(unsigned int shader);
    void Draw(vector<vec4> image);
};


#endif //GRAPHICS_TEXTUREDQUAD_H
