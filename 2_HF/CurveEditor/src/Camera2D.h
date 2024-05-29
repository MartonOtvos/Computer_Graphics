//
// Created by Marci on 5/28/2024.
//

#ifndef GRAPHICS_CAMERA2D_H
#define GRAPHICS_CAMERA2D_H
#include "framework.h"

class Camera2D {
    vec2 size;
    vec2 center;
public:
    Camera2D(vec2 size, vec2 center);
    mat4 View();
    mat4 Projection();
    mat4 InverseView();
    mat4 InverseProjection();

    void Zoom(float d);
    void Pan(float d);

};


#endif //GRAPHICS_CAMERA2D_H
